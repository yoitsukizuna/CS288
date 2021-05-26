<html>
<head>
    <title>Make a Comparasion</title>
</head>
<body>
<img src="img/header.jpg"alt="Here is a header image" width="1200px" height="300px"/>
<table align="center" border="1" width="100%">
<?php
    $cnx = new mysqli('localhost', 'zhaoshu', 'zhaoshu', 'demo');
    if ($cnx->connect_error)
        die('Connection failed: ' . $cnx->connect_error);

    $onclick=$_GET['subject'];
    if ($onclick<26)
        $compare=$onclick+25;
    else
        $compare=$onclick-25;
    $query1 = 'SELECT* FROM product WHERE number='.$onclick.' ';
    $query2 = 'SELECT* FROM product WHERE number='.$compare.' ';
    $cursor1=$cnx->query($query1);
    $cursor2=$cnx->query($query2);
    $row1 =$cursor1 ->fetch_assoc();
    $row2 =$cursor2 ->fetch_assoc();
    $price1=number_format(floatval($row1['price'])*1.05,2,'.','');
    $price2=number_format(floatval($row2['price'])*1.05,2,'.','');
    $bg1="background-color: #FFFFFF";
    $bg2="background-color: #FFFFFF";
    if($price1<$price2)
        $bg1="background-color: #75C0FF";
    else
        $bg2="background-color: #75C0FF";
    echo '<tr>';
    echo '<td align="center" style="'.$bg1.'"> <img src ='.$row1['image'].'  height="200px"/></td>';
    echo '<td align="center" style="'.$bg2.'"> <img src ='.$row2['image'].'  height="200px"/></td>';
    echo '</tr>';
    echo '<tr>';
    echo '<td style ="'.$bg1.'">'. $row1['product_name'].'</td>';
    echo '<td style ="'.$bg2.'">'.$row2['product_name'].'</td>';
    echo '</tr>';
    echo '<tr>';
    echo '<td align="center" style="'.$bg1.'">Review: '.$row1['review'].'</td>';
    echo '<td align="center" style="'.$bg2.'">Review: '.$row2['review'].'</td>';
    echo '</tr>';
    echo '<tr>';
    echo '<td align ="center" style="color:red; font-size:30px;'.$bg1.'"><b>Only today: $'.$price1.'</b></td>';
    echo '<td align="center" style="color:red; font-size:30px;'.$bg2.'"><b>Only today: $'.$price2.'</b></td>';
    echo '</tr>';
    echo '<tr>';
    echo '<td align="left" style="'.$bg1.'">Description: '.$row1['description'].'</td>';
    echo '<td align="left" style="'.$bg2.'">Description: '.$row2['description'].'</td>';
    echo '</tr>';
    echo '<tr>';
    echo '<td align="center" width ="45%" style="color:red;font-size:20px"><a href="purchase.php?subject='.$onclick.'">Buy</a></td>';
    echo '<td align="center" width ="45%"style="color:red;font-size:20px"><a href="purchase.php?subject='.$compare.'">Buy</a></td>';
    echo '</tr>';
  
        
    
?>
</table>
</body>
</html>