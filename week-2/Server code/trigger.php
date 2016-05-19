<?php
	// header('Access-Control-Allow-Origin: *');
    $trigger = $_POST['trigger'];
    
    $filename = 'trigger.json';
    
    $file = fopen('trigger.json', 'w');
    fwrite($file, '{"trigger": "' . $trigger . '"}');
    fclose($file);
?>