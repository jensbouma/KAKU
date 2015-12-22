<?php
$switch = filter_input(INPUT_GET, 'switch');
$value = filter_input(INPUT_GET, 'value');

$InputTrigger = "L".$switch."V".$value;

CallOutput("L".$switch."V".$value);

function CallOutput($InputTrigger){

//	echo $InputTrigger."<BR>";
		// create curl resource
	    $ch = curl_init();
	    // set url ADD YOUR ARDUINO IP HERE!!!!
	    curl_setopt($ch, CURLOPT_URL, "http://192.168.x.x/!=".$InputTrigger);
	    //return the transfer as a string
	    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	    // Alternatively, lie, and pretend to be a browser
	    curl_setopt($ch, CURLOPT_USERAGENT, 'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)');
	    // $output contains the output string
	    $output = curl_exec($ch);
	    // close curl resource to free up system resources
	    curl_close($ch);
	    // Check if variable is on page
}
?>
