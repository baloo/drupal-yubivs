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
  abstract public function process(Yubivs_Request $request);
}


// {{{ Parameters verification processors
class Yubivs_Request_Processor_ClientIdMandatory extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (empty($request->id)) {
      $request->log('Client id is empty while required by protocol', Yubivs_Request::STATUS_MISSING_PARAMETER);
      return Yubivs_Request::STATUS_MISSING_PARAMETER;
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_SignatureMandatory extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (variable_get('yubivs_mandatory_signature', FALSE)) {
      if (empty($request->h)) {
        $request->log('Signature is empty while required by setup', Yubivs_Request::STATUS_BAD_SIGNATURE);
        return Yubivs_Request::STATUS_BAD_SIGNATURE;
      }
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_TimestampMandatory extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (variable_get('yubivs_mandatory_timestamp', FALSE)) {
      if (empty($request->timestamp)) {
        $request->log('Timestamp is empty while required by setup', Yubivs_Request::STATUS_MISSING_PARAMETER);
        return Yubivs_Request::STATUS_MISSING_PARAMETER;
      }
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_NonceMandatory extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (version_compare($request->api_version, YUBIVS_API_VER_20, '>=')) {
      if (empty($request->nonce)) {
        $request->log('Nonce is mandatory in version 2 protocol', Yubivs_Request::STATUS_MISSING_PARAMETER);
        return Yubivs_Request::STATUS_MISSING_PARAMETER;
      }
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_OtpMandatory extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (empty($request->otp)) {
      $request->log('Otp is required for validating otp', Yubivs_Request::STATUS_MISSING_PARAMETER);
      return Yubivs_Request::STATUS_MISSING_PARAMETER;
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_OtpRegexp extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (!preg_match('/^[cbdefghijklnrtuvCBDEFGHIJKLNRTUV]{44}$/', $request->otp)) {
      $request->log('Otp looks invalid', Yubivs_Request::STATUS_BAD_OTP);
      return Yubivs_Request::STATUS_BAD_OTP;
    }
    return Yubivs_Request::STATUS_OK;
  }
}
//  }}}


// {{{ Additional informations
class Yubivs_Request_Processor_ClientIdLookup extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    $client_nid = db_select('node', 'n')
                      ->fields('n', array('nid'))
                      ->condition('type', 'yubivs_client')
                      ->condition('title', check_plain($request->id))
                      ->range(0, 1)
                      ->execute()
                      ->fetchField();
    if (is_numeric($client_nid)) {
      $client = node_load(intval($client_nid));
      if ($client instanceof stdClass) {
        if (isset($client->yubivs_client_shared_key) &&
            isset($client->yubivs_client_shared_key[$client->language])) {
          $shared_key = reset($client->yubivs_client_shared_key[$client->language]);
          $request->signature['shared_key'] = $shared_key['value'];
          $request->client = $client;
          return Yubivs_Request::STATUS_OK;
        }
      }
    }
    $request->log('Can\'t find client id', Yubivs_Request::STATUS_NO_SUCH_CLIENT);
    return Yubivs_Request::STATUS_NO_SUCH_CLIENT;
  }
}


class Yubivs_Request_Processor_YubikeyLookup extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    $publicid = drupal_substr($request->otp, 0, -32);

    $yubikey_nid = db_select('node', 'n')
                    ->fields('n', array('nid'))
                    ->condition('type', 'yubivs_yubikey')
                    ->condition('title', check_plain($publicid))
                    ->range(0, 1)
                    ->execute()
                    ->fetchField();
    if (is_numeric($yubikey_nid)) {
      $yubikey = node_load(intval($yubikey_nid));
      if ($yubikey instanceof stdClass) {
        $request->yubikey = $yubikey;
        return Yubivs_Request::STATUS_OK;
      }
    }
    $request->log('Can\'t find yubikey public', Yubivs_Request::STATUS_BAD_OTP);
    return Yubivs_Request::STATUS_BAD_OTP;
  }
}
// }}}


// {{{ Replay check
class Yubivs_Request_Processor_ReplayCheck extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (isset($request->yubikey) &&
      isset($request->yubikey->language) &&
      isset($request->yubikey->yubivs_yubikey_counter[$request->yubikey->language]) &&
      isset($request->yubikey->yubivs_yubikey_counter[$request->yubikey->language][0]['value']) &&
      isset($request->yubikey->yubivs_yubikey_use[$request->yubikey->language]) &&
      isset($request->yubikey->yubivs_yubikey_use[$request->yubikey->language][0]['value']) &&
      isset($request->decrypted_data['counter']) &&
      !empty($request->decrypted_data['counter']) &&
      isset($request->decrypted_data['use'])) {
      $current_counter = $request->yubikey->yubivs_yubikey_counter[$request->yubikey->language][0]['value'];
      $current_use = $request->yubikey->yubivs_yubikey_use[$request->yubikey->language][0]['value'];

      if ($current_counter < $request->decrypted_data['counter']) {
        return Yubivs_Request::STATUS_OK;
      }
      elseif ($current_counter == $request->decrypted_data['counter']) {
        if ($current_use < $request->decrypted_data['use']) {
          return Yubivs_Request::STATUS_OK;
        }
      }
      $request->log('Replayed otp', Yubivs_Request::STATUS_REPLAYED_OTP);
      return Yubivs_Request::STATUS_REPLAYED_OTP;
    }
    $request->log('Missing parameter', Yubivs_Request::STATUS_MISSING_PARAMETER);
    return Yubivs_Request::STATUS_MISSING_PARAMETER;
  }
}


class Yubivs_Request_Processor_SaveCounters extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (isset($request->yubikey) &&
      isset($request->yubikey->language) &&
      isset($request->yubikey->yubivs_yubikey_counter[$request->yubikey->language]) &&
      isset($request->yubikey->yubivs_yubikey_counter[$request->yubikey->language][0]['value']) &&
      isset($request->yubikey->yubivs_yubikey_use[$request->yubikey->language]) &&
      isset($request->yubikey->yubivs_yubikey_use[$request->yubikey->language][0]['value']) &&
      isset($request->decrypted_data['counter']) &&
      !empty($request->decrypted_data['counter']) &&
      isset($request->decrypted_data['use'])) {

      $request->yubikey->yubivs_yubikey_counter[$request->yubikey->language][0]['value'] = $request->decrypted_data['counter'];
      $request->yubikey->yubivs_yubikey_use[$request->yubikey->language][0]['value'] = $request->decrypted_data['use'];

      node_save($request->yubikey);
      return Yubivs_Request::STATUS_OK;
    }
    $request->log('Missing parameter', Yubivs_Request::STATUS_MISSING_PARAMETER);
    return Yubivs_Request::STATUS_MISSING_PARAMETER;
  }
}
// }}}


// {{{ Signature validation
class Yubivs_Request_Processor_RequestSignatureStringBuild extends Yubivs_Request_Processor_SignatureTools {
  public function process(Yubivs_Request $request) {
    $element_names = array('id', 'otp', 'timestamp', 'nonce', 'sl', 'timeout');
    $elements = array();

    foreach ($element_names as $name) {
      $elements[$name] = $request->$name;
    }

    $request->signature['request_base_str'] = $this->_buildString($elements);

    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_RequestSignatureGenerate extends Yubivs_Request_Processor_SignatureTools {
  public function process(Yubivs_Request $request) {
    if (isset($request->signature ['shared_key']) &&
        !empty($request->signature['shared_key']) &&
        isset($request->signature ['request_base_str']) &&
        !empty($request->signature['request_base_str'])) {
      $request->signature['request_signature'] = $this->_sign($request->signature ['request_base_str'], $request->signature['shared_key']);
      if (is_string($request->signature['request_signature'])) {
        return Yubivs_Request::STATUS_OK;
      }
      else {
        $request->log('Signature returned an error', Yubivs_Request::STATUS_BACKEND_ERROR);
        return Yubivs_Request::STATUS_BACKEND_ERROR;
      }
    }

    $request->log('Missing a parameter to regenerate request signature', Yubivs_Request::STATUS_BACKEND_ERROR);
    return Yubivs_Request::STATUS_BACKEND_ERROR;
  }
}


class Yubivs_Request_Processor_RequestSignatureValidate extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (isset($request  ->h) &&
        !empty($request->h) &&
        isset($request ->signature['request_signature']) &&
        !empty($request->signature['request_signature'])) {
      if ($request->h === $request->signature['request_signature']) {
        return Yubivs_Request::STATUS_OK;
      }
      else {
        $request->log('Signature mismatch', Yubivs_Request::STATUS_BAD_SIGNATURE);
        return Yubivs_Request::STATUS_BAD_SIGNATURE;
      }
    }
    $request->log('Signature miss parameters', Yubivs_Request::STATUS_BACKEND_ERROR);
    return Yubivs_Request::STATUS_BACKEND_ERROR;
  }
}


class Yubivs_Request_Processor_ResponseSignatureStringBuild extends Yubivs_Request_Processor_SignatureTools {
  public function process(Yubivs_Request $request) {
    $element_names = array('t', 'status', 'timestamp', 'sessioncounter', 'sessionuse', 'sl', 'nonce', 'otp');
    $elements = array();

    foreach ($element_names as $name) {
      if (isset($request->response[$name]))
        $elements[$name] = $request->response[$name];
    }

    $request->signature['response_base_str'] = $this->_buildString($elements);

    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_ResponseSignatureGenerate extends Yubivs_Request_Processor_SignatureTools {
  public function process(Yubivs_Request $request) {
    if (isset($request->signature ['shared_key']) &&
        !empty($request->signature['shared_key']) &&
        isset($request->signature ['response_base_str']) &&
        !empty($request->signature['response_base_str'])) {
      $request->signature['response_signature'] = $this->_sign($request->signature ['response_base_str'], $request->signature['shared_key']);
      if (is_string($request->signature['response_signature'])) {
        $request->response['h'] = $request->signature['response_signature'];
        return Yubivs_Request::STATUS_OK;
      }
      else {
        $request->log('Signature returned an error', Yubivs_Request::STATUS_BACKEND_ERROR);
        return Yubivs_Request::STATUS_BACKEND_ERROR;
      }
    }

    $request->log('Missing a parameter to generate response signature', Yubivs_Request::STATUS_BACKEND_ERROR);
    return Yubivs_Request::STATUS_BACKEND_ERROR;
  }
}
// }}}


// {{{ Otp decypher
class Yubivs_Request_Processor_DecryptOtp extends Yubivs_Request_Processor {
  public function __construct() {
    if (!extension_loaded('curl')) {
      trigger_error('Curl is mandatory for yubikey validation server', E_USER_ERROR);
    }
  }

  public function process(Yubivs_Request $request) {
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
      // TODO really implement this function
      $ch = curl_init();
      $url = $selected_yubiksm->title . '?otp=' . $request->otp;
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
      curl_setopt($ch, CURLOPT_URL, $selected_yubiksm->title . '?otp=' . $request->otp);
      $content = curl_exec($ch);
      if ($content === FALSE || curl_errno($ch)) {
        // TODO log failure
        continue;
      }

      if (preg_match('#^OK counter=([0-9a-f]{4}) low=([0-9a-f]{4}) high=([0-9a-f]{2}) use=([0-9a-f]{2})#', $content, $matches)) {
        // Data populate
        $data['counter'] = hexdec($matches[1]);
        $data['low'    ] = hexdec($matches[2]);
        $data['high'   ] = hexdec($matches[3]);
        $data['use'    ] = hexdec($matches[4]);
        $request->decrypted_data = $data;

        curl_close($ch);
        return Yubivs_Request::STATUS_OK;
      }

      // Unknown format
      // Giving up and return BACKEND_ERROR
      curl_close($ch);
      break;
    }
    $request->log('Backend error', Yubivs_Request::STATUS_BACKEND_ERROR);
    return Yubivs_Request::STATUS_BACKEND_ERROR;
  }
}
// }}}


// {{{ Response argument handlers
class Yubivs_Request_Processor_AddStatus extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    switch ($request->status) {
      case Yubivs_Request::STATUS_OK:                   $status = 'OK';
        break;
      case Yubivs_Request::STATUS_BAD_OTP:              $status = 'BAD_OTP';
        break;
      case Yubivs_Request::STATUS_REPLAYED_OTP:         $status = 'REPLAYED_OTP';
        break;
      case Yubivs_Request::STATUS_BAD_SIGNATURE:        $status = 'BAD_SIGNATURE';
        break;
      case Yubivs_Request::STATUS_MISSING_PARAMETER:    $status = 'MISSING_PARAMETER';
        break;
      case Yubivs_Request::STATUS_NO_SUCH_CLIENT:       $status = 'NO_SUCH_CLIENT';
        break;
      case Yubivs_Request::STATUS_OPERATION_NOT_ALLOWED:$status = 'OPERATION_NOT_ALLOWED';
        break;
      case Yubivs_Request::STATUS_BACKEND_ERROR:        $status = 'BACKEND_ERROR';
        break;
      case Yubivs_Request::STATUS_NOT_ENOUGH_ANSWERS:   $status = 'NOT_ENOUGH_ANSWERS';
        break;
      case Yubivs_Request::STATUS_REPLAYED_REQUEST:     $status = 'REPLAYED_REQUEST';
        break;
    }

    $request->response['status'] = $status;
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_AddT extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    $request->response['t'] = date('c');
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_AddNonce extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (isset($request->nonce)) {
      $request->response['nonce'] = $request->nonce;
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_AddOtp extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (isset($request->otp)) {
      $request->response['otp'] = $request->otp;
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_AddTimestamp extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (!empty($request->timestamp) && $request->timestamp == 1 && $request->status == Yubivs_Request::STATUS_OK) {
      $request->response['timestamp'] = $request->decrypted_data['high'] . $request->decrypted_data['low'];
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_AddSessionCounter extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (!empty($request->timestamp) && $request->timestamp == 1 && $request->status == Yubivs_Request::STATUS_OK) {
      $request->response['sessioncounter'] = $request->decrypted_data['counter'];
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_AddSessionUse extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (!empty($request->timestamp) && $request->timestamp == 1 && $request->status == Yubivs_Request::STATUS_OK) {
      $request->response['sessionuse'] = $request->decrypted_data['use'];
    }
    return Yubivs_Request::STATUS_OK;
  }
}


class Yubivs_Request_Processor_AddSl extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    if (version_compare($request->api_version, YUBIVS_API_VER_20, '>=')) {
      // TODO to implement
      $request->response['sl'] = 100;
    }
    return Yubivs_Request::STATUS_OK;
  }
}
// }}}


// {{{ Signature helpers classes
abstract class Yubivs_Request_Processor_SignatureTools extends Yubivs_Request_Processor {
  protected function _buildString($parameters) {
    // Sort parameters
    ksort($parameters, SORT_STRING);

    // Build string
    foreach ($parameters as $name => $value) {
      if (!is_null($value)) {
        $elements[] = $name . '=' . $value;
      }
    }

    return implode('&', $elements);
  }
  protected function _sign($data, $key) {
    return base64_encode(hash_hmac('sha1', $data, $key, TRUE));
  }
}
// }}}

