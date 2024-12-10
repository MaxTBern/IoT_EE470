<?php
// Database connection details
$host = "193.203.166.209"; // Replace with your database host
$username = "u376527350_db_MaxBernstei"; // Replace with your database username
$password = "*******"; // Replace with your database password
$database = "u376527350_MaxBernstein"; // Replace with your database name

// Create a connection
$conn = new mysqli($host, $username, $password, $database);

// Check the connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Fetch data from the table
$sql = "SELECT data, time FROM MQTT_data ORDER BY time DESC";
$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html>
<head>
    <title>Sensor Data Table</title>
    <style>
        table {
            border-collapse: collapse;
            width: 80%;
            margin: auto;
        }
        th, td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: center;
        }
        th {
            background-color: #f4f4f4;
        }
    </style>
</head>
<body>
    <h1>Potentiometer Values</h1><br>
    <h3><a href="https://maxbernsteinprojects.com">Head Home</a></h3>
    <h2 style="text-align: center;">Sensor Data</h2>
    <table>
        <tr>
            <th>Data</th>
            <th>Time</th>
        </tr>
        <?php
        if ($result->num_rows > 0) {
            // Output each row of the data
            while ($row = $result->fetch_assoc()) {
                echo "<tr>";
                echo "<td>" . $row["data"] . "</td>";
                echo "<td>" . $row["time"] . "</td>";
                echo "</tr>";
            }
        } else {
            echo "<tr><td colspan='3'>No data available</td></tr>";
        }
        ?>
    </table>
</body>
</html>

<?php
// Close the connection
$conn->close();
?>
