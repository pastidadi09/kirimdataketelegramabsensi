<?php
date_default_timezone_set('Asia/Jakarta'); // Set zona waktu sesuai dengan lokasi Anda
$dbHost = "192.168.116.154";
$dbUser = "root";
$dbPass = "";
$dbName = "db_telegram";
$conn = new mysqli($dbHost, $dbUser, $dbPass, $dbName);

// echo "koneksi berasil";
if ($conn->connect_error) {
    die("connection Failed" . $conn->connect_error);
}


$jam = date('H.i');
$tgl = date("d-m-Y");



$currentTime = strtotime(date('H:i')); // Waktu saat ini dalam format jam:menit

$lateTimeStart = strtotime('19:20');
$lateTimeEnd = strtotime('19:30');
$earlyLeaveStart = strtotime('20:15');
$earlyLeaveEnd = strtotime('22:00');

if ($currentTime >= strtotime('19:00') && $currentTime <= $lateTimeStart) {
    $ket= "Anak-anak masuk lebih cepat.";
} elseif ($currentTime > $lateTimeStart && $currentTime <= $lateTimeEnd) {
    $ket= "Anak-Anak masuk tepat waktu.";
} elseif ($currentTime >= $earlyLeaveStart && $currentTime <= $earlyLeaveEnd) {
    $ket= "Anak-anak terlambat Masuk Sekolah.";
} else {
    $ket= "Anak-anak sudah pulang sekolah.";
}



$data = json_decode(file_get_contents("php://input"), true);
if (!$data || !isset($data["rfid"])) {
    die("data tidak valid");
}



$idkartu = $data["rfid"];
// print($idkartu);



$sql_check = "SELECT * FROM `t-siswa` WHERE no_rfid= '$idkartu'";
// print($sql_check);
$result_check = $conn->query($sql_check);

if ($result_check->num_rows > 0) {

    while ($row = $result_check->fetch_assoc()) {

        $token = $row['token'];
        $chatid = $row['idchat'];
        $message = "Data Absensi Siswa : \n";
        // $message="Nama : ".$row['nama']."\n";
        $message .= "Nama : " . $row['nama'] . "\n";
        // $message="Alamat : ".$row['alamat']."\n";
        $message .= "Alamat : " . $row['alamat'] . "\n";
        $message .= "Kelas : " . $row['kelas'] . "\n";
        $message .= "Tanggal : " . $tgl. "\n";
        $message .= "Jam : " . $jam. "\n";
        $message .= "Keterangan : " . $ket. "\n";


        sendTelegramMessage($token, $chatid, $message);
        echo "1";
    }
} else {
    echo "0";
}

$conn->close();

function sendTelegramMessage($token, $chatid, $message)
{
    $url = "https://api.telegram.org/bot$token/sendMessage?chat_id=$chatid&text=" . urlencode($message);
    file_get_contents($url);
    // echo $url;
}
?>