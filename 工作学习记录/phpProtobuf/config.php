<?php 
    require_once 'log.php';
	$MY_CHARGE_DB_CONFIG = array(
		'url'      => '127.0.0.1',
		'user'     => 'test',
		'password' => '123456',
		'database' => 'z_all',
		'table'    => 'tbl_recharge',
		'order_table'    => 'tbl_recharge_order',
	);
	function my_connect_mysql($db){
    	if (isset($db["url"]) && isset($db["user"]) && isset($db["password"]) && isset($db["database"])) {
    		$link = @mysql_connect($db["server"],$db["user"],$db["password"]);
    		if (!$link) {
    	        mysql_set_charset('utf8', $link);
    	        if (!mysql_select_db($db["database"], $link)) {
    	            $msqlErrorMsg = 'Could not select database';
    	            writeLog($mysqlErrorMsg,2);
    	            die('Could not select database');
    	        } 
    			return $link;  
    		} else {
    		    $mysqlErrorMsg = "Could not connect:".mysql_error();
    		    writeLog($mysqlErrorMsg,2);
    		    die('Could not connect: ' . mysql_error());
    		}
	    }
	    return null;
    }
?>