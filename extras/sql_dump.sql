-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Mar 24, 2023 at 03:22 AM
-- Server version: 10.4.27-MariaDB
-- PHP Version: 8.1.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `insuranceprogram2`
--

-- --------------------------------------------------------

--
-- Table structure for table `carinsurance`
--

CREATE TABLE `carinsurance` (
  `carinsuranceid` int(11) NOT NULL,
  `customerid` int(11) DEFAULT NULL,
  `make` varchar(30) DEFAULT NULL,
  `model` varchar(30) DEFAULT NULL,
  `licensenumber` int(6) DEFAULT NULL,
  `vehicleidnumber` varchar(15) DEFAULT NULL,
  `year` int(4) DEFAULT NULL,
  `annualmiles` int(9) DEFAULT NULL,
  `safetyfeatures` varchar(256) DEFAULT NULL,
  `antitheftdevices` varchar(256) DEFAULT NULL,
  `monthlypayment` float DEFAULT NULL,
  `monthspaid` int(11) DEFAULT NULL,
  `monthlimit` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

--
-- Dumping data for table `carinsurance`
--

INSERT INTO `carinsurance` (`carinsuranceid`, `customerid`, `make`, `model`, `licensenumber`, `vehicleidnumber`, `year`, `annualmiles`, `safetyfeatures`, `antitheftdevices`, `monthlypayment`, `monthspaid`, `monthlimit`) VALUES
(1, 1, 'Kia', 'Sportage', 8972, '27570', 2008, 10000, NULL, NULL, 60, 0, 12),
(3, 5, 'Nissan', '350z', 3761, '78847', 2003, 12000, 'Airbag', 'Kill switch, cameras inside', 34, 0, 12),
(7, 12, 'ISUZU', 'D-Max', 2892, '39888', 2019, 10000, 'Airbag', '', 55, 0, 12),
(8, 14, 'Toyota', 'Corolla', 3889, '23003', 2003, 14000, '', '', 30, 1, 12);

-- --------------------------------------------------------

--
-- Table structure for table `customer`
--

CREATE TABLE `customer` (
  `customerid` int(11) NOT NULL,
  `homeinsuranceid` int(11) DEFAULT NULL,
  `carinsuranceid` int(11) DEFAULT NULL,
  `lifeinsuranceid` int(11) DEFAULT NULL,
  `citizenship` varchar(45) DEFAULT NULL,
  `firstname` varchar(45) NOT NULL,
  `middlename` varchar(45) DEFAULT NULL,
  `lastname` varchar(45) NOT NULL,
  `age` int(11) NOT NULL,
  `phonenumber` varchar(25) DEFAULT NULL,
  `socialsecuritynumber` int(9) NOT NULL,
  `status` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

--
-- Dumping data for table `customer`
--

INSERT INTO `customer` (`customerid`, `homeinsuranceid`, `carinsuranceid`, `lifeinsuranceid`, `citizenship`, `firstname`, `middlename`, `lastname`, `age`, `phonenumber`, `socialsecuritynumber`, `status`) VALUES
(1, 1, 1, 1, 'Belizean', 'John', 'Unknown', 'Doe', 15, '625-4777', 297118881, 1),
(5, 3, 3, 3, 'American', 'Mary', 'Moodle', 'Jane', 22, '345-8372', 29983883, 1),
(12, 4, 7, 4, 'Belizean', 'William', 'James', 'Locario', 20, '389-3483', 198882722, 1),
(14, 5, 8, 5, 'Salvadorian', 'Linsberth', 'Elroy', 'Coc', 56, '873-4443', 128737777, 1),
(15, NULL, NULL, 6, 'Austrian', 'Adolf', 'Lucas', 'Hitler', 27, '6253493', 88888888, 1);

-- --------------------------------------------------------

--
-- Table structure for table `homeinsurance`
--

CREATE TABLE `homeinsurance` (
  `homeinsuranceid` int(11) NOT NULL,
  `customerid` int(11) DEFAULT NULL,
  `address` varchar(45) DEFAULT NULL,
  `maritalstatus` enum('married','widowed','divorced','separated','never married') DEFAULT NULL,
  `homeimprovements` varchar(256) DEFAULT NULL,
  `petowner` tinyint(4) DEFAULT NULL,
  `entrepreneur` tinyint(4) DEFAULT NULL,
  `peopleathome` varchar(256) DEFAULT NULL,
  `monthlypayment` float DEFAULT NULL,
  `monthspaid` int(11) DEFAULT NULL,
  `monthlimit` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

--
-- Dumping data for table `homeinsurance`
--

INSERT INTO `homeinsurance` (`homeinsuranceid`, `customerid`, `address`, `maritalstatus`, `homeimprovements`, `petowner`, `entrepreneur`, `peopleathome`, `monthlypayment`, `monthspaid`, `monthlimit`) VALUES
(1, 1, 'Princess Diana Street', 'never married', NULL, 1, 0, NULL, 50, 0, 12),
(3, 5, '14 crickstock street', 'widowed', 'Added roof', 1, 1, 'Son\nDaughter', 50, 1, 12),
(4, 12, '4 Home Street', 'never married', '', 1, 0, '', 65, 1, 12),
(5, 14, '12 Mary street', 'separated', '', 1, 0, '', 45, 0, 24);

-- --------------------------------------------------------

--
-- Table structure for table `lifeinsurance`
--

CREATE TABLE `lifeinsurance` (
  `lifeinsuranceid` int(11) NOT NULL,
  `customerid` int(11) DEFAULT NULL,
  `salary` float DEFAULT NULL,
  `occupation` varchar(45) DEFAULT NULL,
  `beneficiaries` varchar(128) DEFAULT NULL,
  `feloncharges` tinyint(4) DEFAULT NULL,
  `misdemeanorcharges` tinyint(4) DEFAULT NULL,
  `druguser` tinyint(4) DEFAULT NULL,
  `highriskhobbies` varchar(128) DEFAULT NULL,
  `height` varchar(45) DEFAULT NULL,
  `weight` varchar(45) DEFAULT NULL,
  `physiciandetails` varchar(128) DEFAULT NULL,
  `seriousdiagnoses` varchar(256) DEFAULT NULL,
  `monthlypayment` float DEFAULT NULL,
  `monthspaid` int(11) DEFAULT NULL,
  `monthlimit` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

--
-- Dumping data for table `lifeinsurance`
--

INSERT INTO `lifeinsurance` (`lifeinsuranceid`, `customerid`, `salary`, `occupation`, `beneficiaries`, `feloncharges`, `misdemeanorcharges`, `druguser`, `highriskhobbies`, `height`, `weight`, `physiciandetails`, `seriousdiagnoses`, `monthlypayment`, `monthspaid`, `monthlimit`) VALUES
(1, 1, 45400, 'Manager at InfoTech', NULL, 0, 0, 0, NULL, '5t 6 inches', '170lbs', NULL, NULL, 75.23, 0, 12),
(3, 5, 40000, 'Front Desk Clerk', 'Son - Hubert\nDaughter - Maria', 0, 0, 0, 'inline skating, mountain biking', '5ft 6 inches', '150 lbs', '', '', 45, 0, 12),
(4, 12, 30000, 'Marketer', 'Mother - Rosa Locario', 0, 0, 0, '', '5ft 8in', '170lbs', '', '', 30, 0, 12),
(5, 14, 80000, 'Software Developer', '', 0, 0, 0, 'Sky diving', '6ft 0in', '180lbs', 'Dr. Rubert Palma', 'Diabetes type 1', 80, 0, 12),
(6, 15, 100000, 'Dictator', '', 1, 1, 1, 'Genecide ', '5\'7\'\'', '165', '', 'sociopathy, bipolar, psychopathy', 780, 8, 60);

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `userid` int(11) NOT NULL,
  `userlevelid` int(11) NOT NULL,
  `customerid` int(11) DEFAULT NULL,
  `username` varchar(45) DEFAULT NULL,
  `firstname` varchar(25) DEFAULT NULL,
  `lastname` varchar(45) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `email` varchar(60) DEFAULT NULL,
  `password` varchar(128) DEFAULT NULL,
  `status` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`userid`, `userlevelid`, `customerid`, `username`, `firstname`, `lastname`, `age`, `email`, `password`, `status`) VALUES
(1, 1, NULL, 'TBennett', 'Tadeo', 'Bennett', 18, 'tadeos.bennett@gmail.com', 'password1234', 1),
(2, 2, NULL, 'CBennett', 'Candy', 'Bennett', 48, 'candy.bennett@gmail.com', 'password123', 1),
(3, 3, 1, 'JDoe', 'John', 'Doe', 15, 'johndoe@gmail.com', 'password', 1),
(7, 3, 5, 'MJane', 'Mary', 'Jane', 22, 'maryjane@gmail.com', 'password123', 1),
(14, 3, 12, 'WLocario', 'William', 'Locario', 20, 'williamlocario@gmail.com', 'password123', 1),
(16, 3, 14, 'LCoc', 'Linsberth', 'Coc', 56, 'linsberthcoc@gmail.com', 'password123', 1),
(17, 2, NULL, 'Myourlastname', 'Michael', 'yourlastname', 23, 'michael@gmail.com', 'password', 1),
(18, 3, 15, 'AHitler', 'Adolf', 'Hitler', 27, 'AdolfHitler@gmail.com', 'password123', 1);

-- --------------------------------------------------------

--
-- Table structure for table `userlevel`
--

CREATE TABLE `userlevel` (
  `userlevelid` int(11) NOT NULL,
  `name` varchar(30) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

--
-- Dumping data for table `userlevel`
--

INSERT INTO `userlevel` (`userlevelid`, `name`) VALUES
(1, 'Administrator'),
(2, 'Desk'),
(3, 'Customer');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `carinsurance`
--
ALTER TABLE `carinsurance`
  ADD PRIMARY KEY (`carinsuranceid`),
  ADD KEY `fk_customerid_car` (`customerid`);

--
-- Indexes for table `customer`
--
ALTER TABLE `customer`
  ADD PRIMARY KEY (`customerid`),
  ADD KEY `carinsuranceid` (`carinsuranceid`),
  ADD KEY `homeinsuranceid` (`homeinsuranceid`),
  ADD KEY `lifeinsuranceid` (`lifeinsuranceid`);

--
-- Indexes for table `homeinsurance`
--
ALTER TABLE `homeinsurance`
  ADD PRIMARY KEY (`homeinsuranceid`),
  ADD KEY `fk_customerid_home` (`customerid`);

--
-- Indexes for table `lifeinsurance`
--
ALTER TABLE `lifeinsurance`
  ADD PRIMARY KEY (`lifeinsuranceid`),
  ADD KEY `fk_customerid_life` (`customerid`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`userid`),
  ADD KEY `fk_userlevelid_user` (`userlevelid`);

--
-- Indexes for table `userlevel`
--
ALTER TABLE `userlevel`
  ADD PRIMARY KEY (`userlevelid`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `carinsurance`
--
ALTER TABLE `carinsurance`
  MODIFY `carinsuranceid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `customer`
--
ALTER TABLE `customer`
  MODIFY `customerid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- AUTO_INCREMENT for table `homeinsurance`
--
ALTER TABLE `homeinsurance`
  MODIFY `homeinsuranceid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `lifeinsurance`
--
ALTER TABLE `lifeinsurance`
  MODIFY `lifeinsuranceid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `userid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=19;

--
-- AUTO_INCREMENT for table `userlevel`
--
ALTER TABLE `userlevel`
  MODIFY `userlevelid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `carinsurance`
--
ALTER TABLE `carinsurance`
  ADD CONSTRAINT `fk_customerid_car` FOREIGN KEY (`customerid`) REFERENCES `customer` (`customerid`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Constraints for table `customer`
--
ALTER TABLE `customer`
  ADD CONSTRAINT `carinsuranceid` FOREIGN KEY (`carinsuranceid`) REFERENCES `carinsurance` (`carinsuranceid`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `homeinsuranceid` FOREIGN KEY (`homeinsuranceid`) REFERENCES `homeinsurance` (`homeinsuranceid`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `lifeinsuranceid` FOREIGN KEY (`lifeinsuranceid`) REFERENCES `lifeinsurance` (`lifeinsuranceid`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Constraints for table `homeinsurance`
--
ALTER TABLE `homeinsurance`
  ADD CONSTRAINT `fk_customerid_home` FOREIGN KEY (`customerid`) REFERENCES `customer` (`customerid`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Constraints for table `lifeinsurance`
--
ALTER TABLE `lifeinsurance`
  ADD CONSTRAINT `fk_customerid_life` FOREIGN KEY (`customerid`) REFERENCES `customer` (`customerid`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Constraints for table `user`
--
ALTER TABLE `user`
  ADD CONSTRAINT `fk_userlevelid_user` FOREIGN KEY (`userlevelid`) REFERENCES `userlevel` (`userlevelid`) ON DELETE NO ACTION ON UPDATE NO ACTION;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
