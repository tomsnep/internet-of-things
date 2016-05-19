<?php
    $motion = $_POST['motion'];
    
    $filename = 'motion.txt';
    
    $timestamp = new DateTime();
    $time = $timestamp->format("Y-m-d H:i:s");

    $file_data = $time . ":" . $motion . "\r\n";
    $file_data .= file_get_contents($filename);
    file_put_contents($filename, $file_data);
?>