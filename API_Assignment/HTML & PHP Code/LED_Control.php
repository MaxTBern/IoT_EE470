<!DOCTYPE HTML>
<html>
<head>
    <title>LED Control</title>
    <h1 style="color:green;">IoT Course</h1>
</head>
<body>
    <form method="post" action="">
        Click to turn ON: <input type="submit" name="LEDstatus" value="on"> 
        <p></p>
        Click to turn OFF: <input type="submit" name="LEDstatus" value="off">
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        if (isset($_POST["LEDstatus"])) {
            $var1 = $_POST["LEDstatus"]; // Get the value of the submitted button
            echo "<br>";
            echo "Last time you clicked, the status was: $var1";

            $myfile = fopen("ledstatus.txt", "w") or die("Unable to open file!");
            fwrite($myfile, $var1); // Write the status to the file
            fclose($myfile); // Close the file
        }
    }
    ?>
</body>
</html>
