<?php
    $switch = $_POST['switch'];
    
    $filename = 'switch.json';
    
    $file = fopen('switch.json', 'w');
    fwrite($file, '{"switch": "' . $switch . '"}');
    fclose($file);
?>