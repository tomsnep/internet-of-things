<?php
    $light = $_POST['trigger'];
    
    $filename = 'trigger.json';
    
    $file = fopen('trigger.json', 'w');
    fwrite($file, '{"trigger": "' . $trigger . '"}');
    fclose($file);
?>