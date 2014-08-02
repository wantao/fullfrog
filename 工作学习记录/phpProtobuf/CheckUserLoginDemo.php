<?php
/**
 * 这个是调用Sdk里检查用户登陆SessionId是否有效的DEMO
 * 
 */
require_once 'Sdk.php';
require_once 'log.php';
require_once 'compilePhpProtobuf/message/pb_message.php';
require_once 'compilePhpProtobuf/pb_proto_serverInternal.php';

$Sdk = new Sdk();
$contents = file_get_contents('php://input', 'r');

$NineOneLoginAuthReq = new NineOneLoginAuthReq();
$NineOneLoginAuthReq->parseFromString($contents);

//用户的91Uin
#$Uin = "155697594";
$Uin = $NineOneLoginAuthReq->Uin();


//用户登陆SessionId
#$SessionId = "39a973600853e9e9970c38f6c6779bdd";
$SessionId = $NineOneLoginAuthReq->SessionId();
$Uin = "wantao234";
$SessionId = "testkey";
writeLog("Uin:".$Uin." SessionId:".$SessionId,3);

if (empty($Uin) || empty($SessionId)) {
    $logMsg = "Uin:".$Uin." SessionId:".$SessionId;
    writeLog($logMsg,3);
    return; 
}


$Res = $Sdk->check_user_login($Uin,$SessionId);
writeLog("Res:".$Res."ErrorCode:".$Res["ErrorCode"]." ErrorDesc:".$Res["ErrorDesc"],3);

$NineOneLoginAuthAck = new NineOneLoginAuthAck();
$NineOneLoginAuthAck->set_ErrorCode($Res["ErrorCode"]);
$NineOneLoginAuthAck->set_ErrorDesc($Res["ErrorDesc"]);
$ResSerializeToString = $NineOneLoginAuthAck->SerializeToString();

print_r($ResSerializeToString);

?>