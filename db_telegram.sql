-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Aug 24, 2023 at 03:28 PM
-- Server version: 10.4.28-MariaDB
-- PHP Version: 8.2.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `db_telegram`
--

-- --------------------------------------------------------

--
-- Table structure for table `t-siswa`
--

CREATE TABLE `t-siswa` (
  `id` int(50) NOT NULL,
  `no_rfid` varchar(50) NOT NULL,
  `nama` varchar(50) NOT NULL,
  `alamat` varchar(100) NOT NULL,
  `kelas` varchar(5) NOT NULL,
  `token` varchar(100) NOT NULL,
  `idchat` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `t-siswa`
--

INSERT INTO `t-siswa` (`id`, `no_rfid`, `nama`, `alamat`, `kelas`, `token`, `idchat`) VALUES
(1, '7097A655', 'Agus', 'Jl wijaya 01', '2A', '6623110597:AAEq45Vz5xMMrKso1vHLwa8-Bx1kePdsuuQ', '6211031822'),
(2, '70179655', 'Fitri', 'Jl mawar no 123', '1C', '6341299107:AAEKgjUKv6wM_nt5dQAU679FHMr6zXRKSKk', '6211031822');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `t-siswa`
--
ALTER TABLE `t-siswa`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `t-siswa`
--
ALTER TABLE `t-siswa`
  MODIFY `id` int(50) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
