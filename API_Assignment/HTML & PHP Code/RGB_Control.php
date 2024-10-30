<!DOCTYPE HTML>
<html>
<head>
    <title>RGB Control</title>
    <h1 style="color:green;">IoT Course</h1><br>
    <h5>Move the sliders to change the RGB color!</h5>
</head>
<body>
    <form method="post" action="">
        <label for="slider1">Red (0-255): </label>
        <input type="range" id="slider1" name="slider1" min="0" max="255" value="0" oninput="this.nextElementSibling.value = this.value">
        <output>0</output>
        <p></p>
        
        <label for="slider2">Green (0-255): </label>
        <input type="range" id="slider2" name="slider2" min="0" max="255" value="0" oninput="this.nextElementSibling.value = this.value">
        <output>0</output>
        <p></p>
        
        <label for="slider3">Blue (0-255): </label>
        <input type="range" id="slider3" name="slider3" min="0" max="255" value="0" oninput="this.nextElementSibling.value = this.value">
        <output>0</output>
        <p></p>
        
        Click to submit: <input type="submit" name="submit" value="Submit Values">
        <p></p>
        Click to turn ON: <input type="submit" name="LEDstatus" value="on"> 
        <p></p>
        Click to turn OFF: <input type="submit" name="LEDstatus" value="off">
        <p></p>
        
    </form>

    <?php
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $rgbFile = "rgbstatus.txt";
            $json_content = file_get_contents($rgbFile);
            $data = json_decode($json_content, true);
            
            if (isset($_POST["submit"])) {
                $data["RED"] = isset($_POST["slider1"]) ? $_POST["slider1"] : $data["RED"];
                $data["GREEN"] = isset($_POST["slider2"]) ? $_POST["slider2"] : $data["GREEN"];
                $data["BLUE"] = isset($_POST["slider3"]) ? $_POST["slider3"] : $data["BLUE"];
            } elseif (isset($_POST["LEDstatus"])) {
                // Update STATUS only
                $data["STATUS"] = $_POST["LEDstatus"];
            }
            
            echo "<br>Current RGB status is: " . htmlspecialchars($data["STATUS"]) . "<br>";
            echo "Red Slider Value: " . htmlspecialchars($data["RED"]) . "<br>";
            echo "Green Slider Value: " . htmlspecialchars($data["GREEN"]) . "<br>";
            echo "Blue Slider Value: " . htmlspecialchars($data["BLUE"]) . "<br>";
            
            $rgbFile = "rgbstatus.txt";
            file_put_contents($rgbFile, json_encode($data));
        }
    ?>
</body>
</html>
