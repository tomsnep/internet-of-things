<?php
    $motion = $_POST['motion'];
    
    $filename1 = 'motion.txt';
    $filename2 = 'value.txt';

    $timestamp = new DateTime();
    $time = $timestamp->format("Y-m-d");

    $value = "Reiger gedetecteerd";

    $file_data1 = $time . "\r\n";
    $file_data1 .= file_get_contents($filename1);
    file_put_contents($filename1, $file_data1);


    $file_data2 = $value . "\r\n";
    $file_data2 .= file_get_contents($filename2);
    file_put_contents($filename2, $file_data2);


?>