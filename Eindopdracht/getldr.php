<?php
     header("Access-Control-Allow-Origin: *");
     header('Content-type: text/plain');
     
     $ldr = fopen('ldr.txt', 'r');
     
     echo fread($ldr, filesize('ldr.txt'));
?>