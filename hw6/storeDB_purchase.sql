-- MariaDB dump 10.19  Distrib 10.5.9-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: demo
-- ------------------------------------------------------
-- Server version	10.5.9-MariaDB-1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `purchase`
--

DROP TABLE IF EXISTS `purchase`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `purchase` (
  `num` smallint(6) NOT NULL AUTO_INCREMENT,
  `product_name` varchar(255) DEFAULT NULL,
  `product_url` varchar(255) DEFAULT NULL,
  `price` decimal(6,2) DEFAULT NULL,
  `time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  PRIMARY KEY (`num`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `purchase`
--

LOCK TABLES `purchase` WRITE;
/*!40000 ALTER TABLE `purchase` DISABLE KEYS */;
INSERT INTO `purchase` VALUES (2,'ASUS VG248QG 24\" Full HD 165Hz HDMI DP DVI FreeSync GSync Compatible LED Gaming Monitor ','https://www.microcenter.com/product/609372/asus-vg248qg-24-full-hd-165hz-hdmi-dp-dvi-freesync-g-sync-compatible-led-gaming-monitor',199.99,'2021-04-29 09:16:00'),(3,'GIGABYTE 34\" LED UltraWide WQHD FreeSync Monitor with HDR (HDMI, DisplayPort) Black G34WQC ','https://www.bestbuy.com/site/gigabyte-34-led-ultrawide-wqhd-freesync-monitor-with-hdr-hdmi-displayport-black/6437138.p?skuId=6437138',0.00,'2021-04-29 09:16:48'),(4,'LG 29” UltraWide Full HD HDR Monitor with FreeSync 29WP500B ','https://www.bestbuy.com/site/lg-29-ultrawide-full-hd-hdr-monitor-with-freesync/6451077.p?skuId=6451077',199.99,'2021-04-29 09:16:57'),(5,'ASUS TUF Gaming VG259QM 24.5\" Full HD 280Hz HDMI DP FreeSync HDR GSync Compatible IPS LED Gaming Monitor ','https://www.microcenter.com/product/623552/asus-tuf-gaming-vg259qm-245-full-hd-280hz-hdmi-dp-freesync-hdr-g-sync-compatible-ips-led-gaming-monitor',319.99,'2021-04-29 09:39:00'),(6,'Acer EK240Y Abi 23.8\" Full HD 60Hz HDMI VGA IPS LED Monitor ','https://www.microcenter.com/product/620538/acer-ek240y-abi-238-full-hd-60hz-hdmi-vga-ips-led-monitor',129.99,'2021-04-29 16:03:31'),(7,'LG 34WL500B 34\" IPS LED UltraWide FHD FreeSync Monitor with HDR (HDMI) Black ','https://www.bestbuy.com/site/lg-34wl500-b-34-ips-led-ultrawide-fhd-freesync-monitor-with-hdr-hdmi-black/6329954.p?skuId=6329954',349.99,'2021-04-29 16:05:50'),(8,'ASUS VG245H 24” FHD 1ms FreeSync Console Gaming Monitor (Dual HDMI, VGA) Black VG245H ','https://www.bestbuy.com/site/asus-vg245h-24-fhd-1ms-freesync-console-gaming-monitor-dual-hdmi-vga-black/5591926.p?skuId=5591926',169.99,'2021-04-29 16:12:05'),(9,'HP X24ih 23.8\" IPS LED FHD FreeSync Premium Monitor (DisplayPort, HDMI) Black X24ih ','https://www.bestbuy.com/site/hp-x24ih-23-8-ips-led-fhd-freesync-premium-monitor-displayport-hdmi-black/6426783.p?skuId=6426783',249.99,'2021-04-29 16:13:21');
/*!40000 ALTER TABLE `purchase` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-04-29 12:15:40
