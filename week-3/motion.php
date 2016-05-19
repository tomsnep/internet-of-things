<?php
    $motion = $_POST['motion'];
    
    $filename1 = 'motion.txt';

    $timestamp = new DateTime();
    $time = $timestamp->format("Y-m-d");


    $file_data1 = $time . "\r\n";
    $file_data1 .= file_get_contents($filename1);
    file_put_contents($filename1, $file_data1);


?>