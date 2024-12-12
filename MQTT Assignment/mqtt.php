<?php
// Database connection details
$host = "193.203.166.209"; // Replace with your database host
$username = "u376527350_db_MaxBernstei"; // Replace with your database username
$password = "&uC;e=J6"; // Replace with your database password
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

// Initialize arrays to hold the data
$dataValues = [];
$timeValues = [];

// Populate the arrays with database values
if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $dataValues[] = $row["data"];
        $timeValues[] = $row["time"];
    }
}

// Close the connection
$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Sensor Data Table and Graph</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
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
        #chart-container {
            width: 80%;
            margin: auto;
            padding: 20px;
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
        foreach ($dataValues as $index => $value) {
            echo "<tr>";
            echo "<td>" . $value . "</td>";
            echo "<td>" . $timeValues[$index] . "</td>";
            echo "</tr>";
        }
        ?>
    </table>

    <div id="chart-container">
        <canvas id="dataChart"></canvas>
    </div>

    <script>
        // Pass PHP data to JavaScript
        const dataValues = <?php echo json_encode($dataValues); ?>;
        const timeValues = <?php echo json_encode($timeValues); ?>;

        // Configure Chart.js
        const ctx = document.getElementById('dataChart').getContext('2d');
        const dataChart = new Chart(ctx, {
            type: 'line', // Type of chart
            data: {
                labels: timeValues.reverse(), // Time values as labels
                datasets: [{
                    label: 'Sensor Data',
                    data: dataValues.reverse(), // Data values
                    borderColor: 'rgba(75, 192, 192, 1)',
                    backgroundColor: 'rgba(75, 192, 192, 0.2)',
                    borderWidth: 2,
                    tension: 0.4 // Smooth line
                }]
            },
            options: {
                responsive: true,
                plugins: {
                    legend: {
                        display: true,
                        position: 'top'
                    }
                },
                scales: {
                    x: {
                        title: {
                            display: true,
                            text: 'Time'
                        }
                    },
                    y: {
                        title: {
                            display: true,
                            text: 'Data'
                        }
                    }
                }
            }
        });
    </script>
</body>
</html>
<?php
// Close the connection
$conn->close();
?>
