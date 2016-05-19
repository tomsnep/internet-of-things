<?php
    $ldr = $_POST['ldr'];
    
    $filename = 'ldr.txt';
    
    $file_data = $ldr . "\r\n";
    $file_data .= file_get_contents($filename);
    file_put_contents($filename, $file_data);
?>