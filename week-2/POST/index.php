<?php
  $ldr = $_POST['ldr'];

  $filename = 'ldr.txt';

  $file_data = $ldr . ' - ';
  $file_data .= file_get_contents($filename);
  file_put_contents($filename, $file_data);
?>