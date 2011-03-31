<?php
// vim: set foldmethod=marker sw=2 ts=2 et:
/**
 * @file
 * This file provide request processors for yubikey validation server
 * service
 */


/**
 * Basic class describing processors
 */
abstract class Yubivs_Request_Processor {
  /**
   * Callback function for validation request processing
   */
  abstract public function verify(Yubivs_Request $request);
} 


// {{{ Parameters verification processors
class Yubivs_Request_Processor_SignatureMandatory extends Yubivs_Request_Processor {
  public function verify(Yubivs_Request $request) {
    if(variable_get('yubivs_mandatory_signature', FALSE)) {
      if(empty($request->h)) {
        $request->log('Signature is empty while required by setup', Yubivs_Request::STATUS_BAD_SIGNATURE);
        return Yubivs_Request::STATUS_BAD_SIGNATURE;
      }
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_TimestampMandatory extends Yubivs_Request_Processor {
  public function verify(Yubivs_Request $request) {
    if(variable_get('yubivs_mandatory_timestamp', FALSE)) {
      if(empty($request->timestamp)) {
        $request->log('Timestamp is empty while required by setup', Yubivs_Request::STATUS_MISSING_PARAMETER);
        return Yubivs_Request::STATUS_MISSING_PARAMETER;
      }
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_NonceMandatory extends Yubivs_Request_Processor {
  public function verify(Yubivs_Request $request) {
    if(version_compare($request->api_version, YUBIVS_API_VER_20, '>=')) {
      if(empty($request->nonce)) {
        $request->log('Nonce is mandatory in version 2 protocol', Yubivs_Request::STATUS_MISSING_PARAMETER);
        return Yubivs_Request::STATUS_MISSING_PARAMETER;
      }
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_OtpMandatory extends Yubivs_Request_Processor {
  public function verify(Yubivs_Request $request) {
    if(empty($request->otp)) {
      $request->log('Otp is required for validating otp', Yubivs_Request::STATUS_MISSING_PARAMETER);
      return Yubivs_Request::STATUS_MISSING_PARAMETER;
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_OtpRegexp extends Yubivs_Request_Processor {
  public function verify(Yubivs_Request $request) {
    if (!preg_match('/^[cbdefghijklnrtuvCBDEFGHIJKLNRTUV]{44}$/', $request->otp)) {
      $request->log('Otp looks invalid', Yubivs_Request::STATUS_BAD_OTP);
      return Yubivs_Request::STATUS_BAD_OTP;
    }
    return Yubivs_Request::STATUS_OK;
  }
}
// }}}


class Yubivs_Request_Processor_DecryptOtp extends Yubivs_Request_Processor {
  public function verify(Yubivs_Request $request) {
    $yubiksm = db_select('node', 'n')
                 ->fields('n', array('nid'))
                 ->condition('type', 'yubivs_ksm')
                 ->execute()
                 ->fetchAll();
    // TODO: implement round robin selection of ksm
    // One way could be : shuffle($yubiksm)
    // TODO: implement ksm sorting
    while ($selected_yubiksm_id = array_shift($yubiksm)) {
      $selected_yubiksm = node_load($selected_yubiksm_id->nid);
      //dsm($selected_yubiksm);
      // TODO really implement this function
      $request->decrypted_data = array(
        '',
        );

    }
    return Yubivs_Request::STATUS_OK;
  }
}


