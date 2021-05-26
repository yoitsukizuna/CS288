<html>
<head>
    <title>Thank you for purchase!</title>
</head>
<body>
<img src="img/thankyou.jpg"alt="thank you image" height="300px"/>
<table align="center" border="1">
<?php
    $cnx = new mysqli('localhost', 'zhaoshu', 'zhaoshu', 'demo');
    if ($cnx->connect_error)
        die('Connection failed: ' . $cnx->connect_error);

    $onclick=$_GET['subject'];

    $query1 = 'SELECT* FROM product WHERE number='.$onclick.' ';
    $query2 = 'SELECT* FROM purchase ';
    $cursor=$cnx->query($query1);
    $row =$cursor ->fetch_assoc();
    $name=$row['product_name'];
    $url=$row['product_url'];
    $price=floatval($row['price']);
    $pur = 'INSERT INTO purchase(product_name,product_url,price) VALUES (\''.$name.'\',\''.$url.'\','.$price.')';
    //(num, product_name, product_url, price, time)
    if($cnx->query($pur)===TRUE){
        echo "Purchase Succsessfully, Thank you!";
    }else{
        echo "Error: ".$pur."<br>".$cnx->error;
    }

?>
</table>
</body>
</html>