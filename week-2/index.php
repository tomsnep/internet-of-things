<?php  
$dennis = $_GET['dennis'];
$tijs = $_GET['tijs'];
$tom = $_GET['tom'];

if($dennis == "on") {  
  $file = fopen("dennis.json", "w") or die("can't open file");
  fwrite($file, '{"light": "on"}');
  fclose($file);
} 
else if ($dennis == "off") {  
  $file = fopen("dennis.json", "w") or die("can't open file");
  fwrite($file, '{"light": "off"}');
  fclose($file);
}

if($tijs == "on") {  
  $file = fopen("tijs.json", "w") or die("can't open file");
  fwrite($file, '{"light": "on"}');
  fclose($file);
} 
else if ($tijs == "off") {  
  $file = fopen("tijs.json", "w") or die("can't open file");
  fwrite($file, '{"light": "off"}');
  fclose($file);
}

if($tom == "on") {  
  $file = fopen("tom.json", "w") or die("can't open file");
  fwrite($file, '{"light": "on"}');
  fclose($file);
} 
else if ($tom == "off") {  
  $file = fopen("tom.json", "w") or die("can't open file");
  fwrite($file, '{"light": "off"}');
  fclose($file);
}




// if(!empty($_GET["dennis"]))
//   {
//     $dennis = "Light=";
//     $dennis .= ($_GET["data"]);
//   }

//   if(!empty($_GET["tijs"]))
//   {
//     $tijs = "Light=";
//     $tijs .= ($_GET["data"]);
//   }

//   if(!empty($_GET["tom"]))
//   {
//     $tom = "Light=";
//     $tom .= ($_GET["data"]);
//   }
?>

<html>  
  <head>      
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <title>LED for ESP8266</title>

    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js"></script>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css" rel="stylesheet">

  </head>
  <body>
    <div class="row" style="margin-top: 20px;">
      <div class="col-md-8 col-md-offset-2">
        <h1>dennis</h1>
        <a href="?dennis=on" class="btn btn-success btn-block btn-lg">Turn On</a>
        <br />
        <a href="?dennis=off" class="led btn btn-danger btn-block btn-lg">Turn Off</a>
      </div>

      <div class="row" style="margin-top: 20px;">
      <div class="col-md-8 col-md-offset-2">
        <h1>tijs</h1>
        <a href="?tijs=on" class="btn btn-success btn-block btn-lg">Turn On</a>
        <br />
        <a href="?tijs=off" class="led btn btn-danger btn-block btn-lg">Turn Off</a>
      </div>

      <div class="row" style="margin-top: 20px;">
      <div class="col-md-8 col-md-offset-2">
        <h1>tom</h1>
        <a href="?tom=on" class="btn btn-success btn-block btn-lg">Turn On</a>
        <br />
        <a href="?tom=off" class="led btn btn-danger btn-block btn-lg">Turn Off</a>
      </div>
    </div>
  </body>
</html>  