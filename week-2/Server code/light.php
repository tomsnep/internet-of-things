<?php
    $light = $_POST['light'];
    
    $filename = 'light.json';
    
    $file = fopen('light.json', 'w');
    fwrite($file, '{"light": "' . $light . '"}');
    fclose($file);
?>