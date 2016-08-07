# KAKU/COCO
KAKU control with Adruino

1. The input side is a PHP script running on the Synology NAS to running slow tasks in the background of the NAS to not slowdown homebridge call.
2. The Arduino Code for reading the PHP call and translate this to 433 COCO control.


This code is just for inspiration as this is just a stripped part of my home interfacing with the Arduino.

I use the following Arduino Libraries:

RCSwitch.h
https://code.google.com/p/rc-switch/

NewRemoteTransmitter.h 
https://github.com/koffienl/attiny-kaku/tree/master/libraries/NewRemoteSwitch

The php scripts for the old one use a '?switch=1&output=1' extention
For the New Switch '?switch=008&value=%b' where 101 is the ON trigger, 000 the OFF trigger and all between the dimmer value.

My Homebridge config for this looks like:

"accessories": [
       {
           "accessory": "Http",
           "name": "Gordijn Lamp",
           "on_url": "http://192.168.x.x:portxxx/NEWKAKU.php?switch=008&value=101",
           "on_body": "{\"state\":\"On\"}",
           "off_url": "http://192.168.x.x:portxxx/NEWKAKU.php?switch=008&value=000",
           "off_body": "{\"state\":\"Off\"}",
           "brightness_url": "http://192.168.x.x:portxxx/NEWKAKU.php?switch=008&value=%b",
           "username": "",
           "password": "",
           "sendimmediately": "",
           "http_method": "POST",
           "http_brightness_method": "POST",
           "brightnessHandling": "yes",
           "service": "Light"
       }
   ]
