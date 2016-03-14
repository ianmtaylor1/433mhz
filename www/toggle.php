<?php
$rfPath = '/var/www/bin/codesend ';
$rfargs = '-p 0 -r 10 -t tristate -l 186 ';
$outletLight = $_GET['outletId'];
$outletStatus = $_GET['outletStatus'];

if ($outletLight == "1" && $outletStatus == "on") {
    $rfCodes = array('0F0FFFFF0101');
} else if ($outletLight == "1" && $outletStatus == "off") {
    $rfCodes = array('0F0FFFFF0110');
} else if ($outletLight == "2" && $outletStatus == "on") {
    $rfCodes = array('0F0FFFFF1001');
} else if ($outletLight == "2" && $outletStatus == "off") {
    $rfCodes = array('0F0FFFFF1010');
} else if ($outletLight == "3" && $outletStatus == "on") {
    $rfCodes = array('0F0FFFF10001');
} else if ($outletLight == "3" && $outletStatus == "off") {
    $rfCodes = array('0F0FFFF10010');
} else if ($outletLight == "4" && $outletStatus == "on") {
    $rfCodes = array('0F0FFF1F0001');
} else if ($outletLight == "4" && $outletStatus == "off") {
    $rfCodes = array('0F0FFF1F0010');
} else if ($outletLight == "5" && $outletStatus == "on") {
    $rfCodes = array('0F0FF1FF0001');
} else if ($outletLight == "5" && $outletStatus == "off") {
    $rfCodes = array('0F0FF1FF0010');
} else if ($outletLight == "6" && $outletStatus == "on") {
    $rfCodes = array('0F0FFFFF0101', '0F0FFFFF1001', '0F0FFFF10001', '0F0FFF1F0001', '0F0FF1FF0001');
} else if ($outletLight == "6" && $outletStatus == "off") {
    $rfCodes = array('0F0FFFFF0110', '0F0FFFFF1010', '0F0FFFF10010', '0F0FFF1F0010', '0F0FF1FF0010');
}
/* Non-remote codes */
else if ($outletLight == "10" && $outletStatus == "on") {
    $rfCodes = array('0F0FFFFF0001')
}
else if ($outletLight == "10" && $outletStatus == "off") {
    $rfCodes = array('0F0FFFFF0010')
}

foreach ($rfCodes as $rfCode) {
        shell_exec($rfPath . $rfargs . $rfCode);
        if (count($rfCodes)>1) {
            usleep(250000);
        }
}

echo json_encode(array('success' => true));
?>
