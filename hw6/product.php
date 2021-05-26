<html>
<head>
    <title>SQL SELECT Statement</title>
</head>
<body>
<img src="img/header.jpg"alt="Here is a header pic" width="1200px" height="300px"/>
<table align="center" border="1">
<?php
    $cnx = new mysqli('localhost', 'zhaoshu', 'zhaoshu', 'demo');
    if ($cnx->connect_error)
        die('Connection failed: ' . $cnx->connect_error);
    $query = 'SELECT * FROM product ';
    $cursor = $cnx->query($query);
    while ($row = $cursor->fetch_assoc()) {
        $onclick = $row['number'];
        echo '<tr>';
        echo '<td align="center"> <img src ='.$row['image'].'  height="200px"/></td>';
        echo '</tr>';
        echo '<tr>';
        echo '<td align="center"><a href="compare.php?subject='.$onclick.'">'. $row['product_name'].'</a></td>';
        echo '</tr>';
        
    }
    
?>
</table>
</body>
</html>