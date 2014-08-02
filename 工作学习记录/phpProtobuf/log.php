<?php
    function writeLog ($msg,$logType) {
    	$logFile = '';
    	if ($logType == 1) {
    	    $logFile = 'log/charge-'.date('Y-m-d').'.log';
    	}else if ($logType == 2) {
    	    $logFile = 'log/db_error-'.date('Y-m-d').'.log';
    	}else if ($logType == 3) {
    	    $logFile = 'log/user-'.date('Y-m-d').'.log';
    	}else {
    	    return;
    	} 
    	$msg = date('H:i:s').': '.$msg."\r\n";
    	file_put_contents($logFile,$msg,FILE_APPEND );
    }
?>