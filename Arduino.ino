// Not Tested Just a Example


// INCLUDE
#include <Ethernet.h>
#include <SPI.h>
#include <RCSwitch.h>
#include <NewRemoteTransmitter.h>

boolean reading = false;
boolean readinglamp = false;
boolean readingvalue = false;
boolean reading2 = false;

// DECLARE VARIABLES
unsigned long currentMillis;
unsigned long previousMillis;      //

// String PushSubject = "INPUT";          // For reading webserver input

// 433MHZ Switch Lights on I/O 6

NewRemoteTransmitter transmitter(99, 6, 260, 1);
RCSwitch mySwitch = RCSwitch();
// Define the OLD Remote Group Switches and the two Switche codes I use
char RCGroup [] = "11100";
char RCOutput1 [] = "01100";
char RCOutput2 []= "11100";

int RCoutputstate = 00;
int RCRetry = 1; // Also in the Switch void

int lamp = 0;
int lampold = 0;
int lampvar = 0;
int value = 0;
int level = 0;
int levelvar = 0;
int setlevel = 0;


// Setting Network Values for manual setup
//byte ip[] = { 192, 168, x, x };   //Manual setup only
//byte gateway[] = { 192, 168, x, x }; //Manual setup only
//byte subnet[] = { 255, 255, 255, 0 }; //Manual setup only

// if need to change the MAC address (Very Rare)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer server = EthernetServer(80); //port 80

char inString[32]; // string for incoming serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?


// SETUP
void setup() {
  // Serialport
  Serial.begin(9600);
//  delay (10);
//  Serial.println("Serial Init");

// STARTUP
  netstart();         // Initialise Ethernet
  Serial.println("Startup complete - Running Code");

// 433MHZ SWITCH
    mySwitch.enableTransmit(6);
}

void netstart()
{
  //Ethernet.begin(mac, ip, gateway, subnet); //for manual setup
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Ethernet Connection Failed");
  } else {
    //Start webserver
    server.begin();
    delay(1000);
    Serial.print("IP ADRESS: ");
    Serial.println(Ethernet.localIP());
  }
}

/// Routine

void loop() {
  CheckForClient();   // listen for incoming clients on webserver, and process url variable request.
}

void Lamp() {
  
    if (level >= 1 && level <= 99) {
    Serial.print("Dimming lamp ");
    Serial.print(lamp);
    Serial.print(" ");
    Serial.print(level);
    Serial.println("%");
      if (level <= 7) {
        setlevel = 1;
      } else {
        if (level >= 13 && level <=19){
          setlevel = 2;
        } else {
        if (level >= 20 && level <=25){
          setlevel = 3;
          } else {
          if (level >= 26 && level <=32){
            setlevel = 4;
          } else {
            if (level >= 33 && level <=39){
              setlevel = 5;
            } else {
              if (level >= 40 && level <=45){
               setlevel = 6;
              } else {
                if (level >= 46 && level <=52){
                setlevel = 7;
                } else {
                  if (level >= 53 && level <=59){
                  setlevel = 8;
                  } else {
                    if (level >= 60 && level <=65){
                    setlevel = 9;
                    } else {
                      if (level >= 66 && level <=72){
                      setlevel = 10;
                      }else {
                        if (level >= 73 && level <=79){
                        setlevel = 11;
                        } else {
                          if (level >= 80 && level <=85){
                          setlevel = 12;
                          } else {
                            if (level >= 86 && level <=92){
                            setlevel = 13;
                            } else {
                              if (level >= 93 && level <=99){
                              setlevel = 14;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
         }
        }
      }
        transmitter.sendDim(lamp, setlevel);
    }else {
       switch (level) {
        case 101:
              Serial.print("Switching on lamp ");
              Serial.println(lamp);
              transmitter.sendUnit(lamp, true);
        break;
        
        case 100:
              if (level == 100) {transmitter.sendDim(lamp, 15);}
              Serial.print("Switching on lamp ");
              Serial.print(lamp);
              Serial.println(" 100%");
         break;

         case 0:
              Serial.print("Switching off lamp ");
              Serial.println(lamp);
              transmitter.sendUnit(lamp, false);
         break;
  }
    }
    
  lamp = 0;
  level = 0;
  setlevel = 0;
  }
  
}

void Switch() {
  while (RCRetry > 0){
    switch (RCoutputstate) {
            case 11:
              mySwitch.switchOn(RCGroup, RCOutput1);
              Serial.println ("oude KAKU 1 Aan");
            break;

            case 10:
              mySwitch.switchOff(RCGroup, RCOutput1);
              Serial.println ("oude KAKU 1 uit");
            break;

            case 21:
              mySwitch.switchOn(RCGroup, RCOutput2);
              Serial.println ("oude KAKU 2 Aan");
            break;

            case 20:
              mySwitch.switchOff(RCGroup, RCOutput2);
              Serial.println ("oude KAKU 2 uit");
            break;
    }
    RCRetry--;
  }
    RCRetry = 1;
    }
}

void CheckForClient() {

  EthernetClient client = server.available();
  if (client) {
    } else {
      Lamp();
      lamp = 0;
      level = 0;
    }
    
  if (client) {
  
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    boolean sentHeader = false;
    
    while (client.connected()) {
      if (client.available()) {

        if (!sentHeader) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          sentHeader = true;
        }

        char c = client.read();

        if (reading && c == ' ') reading = false; 
        if (c == '?') reading = true;//found the ?, begin reading the info

        
        if (reading2 && c == ' ') reading2 = false; 
        if (c == '!') reading2 = true; //found the !, begin reading the info

        
       if (reading2) {
//        Serial.print ("Licht Input");
//        Serial.print(c);
       
       switch (c) {
            case 'L':
//             Serial.print("Lamp");
             c = client.read();
             lampvar = ((c-48) * 100);
             c = client.read();
             lampvar = (lampvar + ((c-48) * 10));
             c = client.read();
             lampvar = (lampvar + (c-48));
//             Serial.print (lampvar);       
             break;
             
            case 'V':
//            Serial.print(" Value ");
             value = 0;
             c = client.read();
             value = (value + ((c-48) * 100));
             c = client.read();
             value = (value + ((c-48) * 10));
             c = client.read();
             if (c == ' '){
             levelvar = (value / 10); 
             } else {
             levelvar = (value + ((c-48) * 1));
             }
//             Serial.println (level);
                   
             if (lamp != 0 && lamp !=lampvar){
//           Serial.println ("New Lamp, 1st one first!");
             //Run Script to turn change old lamp
             Lamp();
             lamp = lampvar;
             level = levelvar;
             Lamp();
             } else {
             lamp = lampvar;
             level = levelvar;
             }
             delay(1); // give the web browser time to receive the data       
             client.stop(); // close the connection:
             break; 
             
       }
    }
                
        if (reading) {
        
//        Serial.print(c);

          switch (c) {
            case 'A':
              RCoutputstate = 11;
              Switch();
              break;
               case 'B':
              RCoutputstate = 10;
              Switch();
              break;   
               case 'C':
              RCoutputstate = 21;
              Switch();
              break;   
               case 'D':
              RCoutputstate = 20;
              Switch();
              break;   
              
          }
        }
        if (c == '\n' && currentLineIsBlank)  break;

          if (c == '\n') {
            currentLineIsBlank = true;
          } else if (c != '\r') {
            currentLineIsBlank = false;
          }
        }
      } 

    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection:
//    Serial.println (" Close");
    delay (70);
  } 
}
