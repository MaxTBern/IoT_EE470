<?php
// Initialize response variable
$response = "";

// Check if the form has been submitted
if ($_SERVER["REQUEST_METHOD"] == "GET" && isset($_GET['sensor'])) {
    // Get the sensor value from the input
    $sensor_value = urlencode($_GET['sensor']); // URL-encode the input for safe URL transmission

    // Construct the URL with query parameters
    $url = "https://example.com/api?date=" . urlencode(date("Y-m-d H:i:s")) . "&sensor=" . $sensor_value;

    // Initialize cURL session
    $ch = curl_init();

    // Set cURL options
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true); // Return the response as a string
    curl_setopt($ch, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1); // Force HTTP/1.1

    // Execute GET request
    $response = curl_exec($ch);

    // Check for errors
    if ($response === FALSE) {
        $response = "cURL Error: " . curl_error($ch);
    }

    // Close the cURL session
    curl_close($ch);
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Submit Sensor Value</title>
</head>
<body>
    <h2>Submit Sensor Value</h2>
    <form method="get" action="">
        <label for="sensor">Sensor Value:</label>
        <input type="text" id="sensor" name="sensor" required>
        <button type="submit">Submit</button>
    </form>

    <?php
    // Display the response from the GET request if available
    if ($response) {
        echo "<p>Response from GET request: $response</p>";
    }
    ?>
</body>
</html>
