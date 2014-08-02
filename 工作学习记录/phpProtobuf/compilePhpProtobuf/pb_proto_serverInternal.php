<?php
class NineOneLoginAuthReq extends PBMessage
{
  var $wired_type = PBMessage::WIRED_LENGTH_DELIMITED;
  public function __construct($reader=null)
  {
    parent::__construct($reader);
    $this->fields["1"] = "PBString";
    $this->values["1"] = "";
    $this->fields["2"] = "PBString";
    $this->values["2"] = "";
  }
  function Uin()
  {
    return $this->_get_value("1");
  }
  function set_Uin($value)
  {
    return $this->_set_value("1", $value);
  }
  function SessionId()
  {
    return $this->_get_value("2");
  }
  function set_SessionId($value)
  {
    return $this->_set_value("2", $value);
  }
}
class NineOneLoginAuthAck extends PBMessage
{
  var $wired_type = PBMessage::WIRED_LENGTH_DELIMITED;
  public function __construct($reader=null)
  {
    parent::__construct($reader);
    $this->fields["1"] = "PBInt";
    $this->values["1"] = "";
    $this->fields["2"] = "PBString";
    $this->values["2"] = "";
  }
  function ErrorCode()
  {
    return $this->_get_value("1");
  }
  function set_ErrorCode($value)
  {
    return $this->_set_value("1", $value);
  }
  function ErrorDesc()
  {
    return $this->_get_value("2");
  }
  function set_ErrorDesc($value)
  {
    return $this->_set_value("2", $value);
  }
}
?>