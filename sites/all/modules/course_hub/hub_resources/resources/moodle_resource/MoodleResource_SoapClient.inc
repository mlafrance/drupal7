<?php

/**
 * A custom SoapClient that manages authentication to Moodle.
 */
class MoodleResource_SoapClient {

  /**
   * Constructor. Authenticate and store our client ID and session key.
   *
   * @return void
   */
  public function __construct() {
    $wsdl = variable_get('moodle_resource_wsdl', '');
    if (empty($wsdl))
      throw new Exception(t('WSDL url not defined. Please define it in the <a href="@url">Moodle Resource Configuration</a>.', array('@url' => url('admin/course_hub/resources/moodle'))));

    $user = variable_get('moodle_resource_soap_user', '');
    if (empty($user))
      throw new Exception(t('SOAP username not defined. Please define it in the <a href="@url">Moodle Resource Configuration</a>.', array('@url' => url('admin/course_hub/resources/moodle'))));

    $password = variable_get('moodle_resource_soap_password', '');
    if (empty($password))
      throw new Exception(t('SOAP password not defined. Please define it in the <a href="@url">Moodle Resource Configuration</a>.', array('@url' => url('admin/course_hub/resources/moodle'))));

    try {
      $this->_soapclient = new SoapClient($wsdl, array('trace' => 1));
    } catch (SoapFault $e) {
      throw new Exception(t('Could not communicate with Moodle. SoapFault: @message', array('@message' => $e->getMessage())));
    }
    // Log in
    try {
      $response = $this->_soapclient->login($user, $password);

      $this->_client = $response->client;
      $this->_sessionkey = $response->sessionkey;

    } catch (SoapFault $e) {
      throw new Exception(t('Could not authenticate against Moodle. <br/>SoapFault: "@message" <br/>Request: "@request"', array('@message' => $e->getMessage(), '@request' => $this->_soapclient->__getLastRequest())));
    }
  }

  /**
   * Perform a soap request, prepending our authentication tokens.
   */
  public function __call($function, $arguments) {
    if (!preg_match('/^__/', $function))
      array_unshift($arguments, $this->_client, $this->_sessionkey);
    return call_user_func_array(array($this->_soapclient, $function), $arguments);
  }

  /**
   * Destructor. Log out.
   */
  public function __destruct() {
    try {
      $this->logout();
    } catch (SoapFault $e) {
      throw new Exception(t('Could not log out from Moodle. SoapFault: @message', array('@message' => $e->getMessage())));
    }
  }

  /**
   * Answer the error string if one exists, NULL otherwise
   *
   * @return void
   */
  public function getError() {
    $doc = new DomDocument();
    $doc->loadXML($this->__getLastResponse());
    $errors = $doc->getElementsByTagName('error');
    if ($errors->length) {
      return $errors->item(0)->nodeValue;
    }
  }
}