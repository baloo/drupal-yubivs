<?php
// vim: set foldmethod=marker sw=2 ts=2 et:
/**
 * @file
 * This file provides verification callbacks for 
 * yubikey validation server service
 */


// {{{ Request class
/**
 * Class for storing a request object
 */
class Yubivs_Request {
  const STATUS_NAN                   = 0xFFFF;

  // This have to be 0x000, otherwise everything will fail
  const STATUS_OK                    = 0x0000;

  // Any other value will result in fail
  const STATUS_BAD_OTP               = 0x0001;
  const STATUS_REPLAYED_OTP          = 0x0002;
  const STATUS_BAD_SIGNATURE         = 0x0004;
  const STATUS_MISSING_PARAMETER     = 0x0008;
  const STATUS_NO_SUCH_CLIENT        = 0x0010;
  const STATUS_OPERATION_NOT_ALLOWED = 0x0020;
  const STATUS_BACKEND_ERROR         = 0x0040;
  const STATUS_NOT_ENOUGH_ANSWERS    = 0x0080;
  const STATUS_REPLAYED_REQUEST      = 0x0100;

  public $api_version;

  public $id;
  public $otp;
  public $h;
  public $timestamp;
  public $nonce;


  // Populated by request processors 
  public $decrypted_data;
  // This request signature
  public $signature;
  // The yubikey envolved
  public $yubikey;
  // This response
  public $response;
  public $status;


  // Not yet implemented
  public $sl;
  public $timeout;


  // Array of Yubivs_Request_Processor objects;
  protected $request_backends;

  // Array of Yubivs_Request_Processor objects;
  protected $response_backends;


  /**
   * Class constructor
   */
  public function __construct() {
    // Init the backends list
    $this->backends = array();

  }


  /**
   * Verify request
   */
  public function verify() {
    $result = self::STATUS_OK;
    foreach($this->request_backends as $backend) {
      $result |= $backend->process($this);
      $this->status = $result;

      if($result !== self::STATUS_OK) {
        break;
      }
    }

    return $result;
  }


  /**
   * Respond to the client
   */
  public function respond() {
    $result = self::STATUS_OK;
    foreach($this->response_backends as $backend) {
      $result |= $backend->process($this);
    }
    return $result;
  }


  /**
   * Setter for backends list
   */
  public function addRequestBackend(Yubivs_Request_Processor $backend) {
    $this->request_backends[] = $backend;
  }


  /**
   * Setter for backends list
   */
  public function addResponseBackend(Yubivs_Request_Processor $backend) {
    $this->response_backends[] = $backend;
  }


  /**
   * Logger function
   */
  public function log($message, $return = self::STATUS_NAN) {
    // TODO implement this function with watchdog stuff and backtrace 
////   var_dump($message);
    drupal_set_message($message, 'warning');
  }
}
// }}}


// {{{ API Menu callbacks
/**
 * Verify callback
 */
function yubivs_verify($api_version) {
  $defaults = array(
    'id'        => NULL,
    'otp'       => NULL,
    'h'         => NULL,
    'timestamp' => NULL,
    'nonce'     => NULL,
    'sl'        => NULL,
    'timeout'   => NULL,
    );
  $arguments = $_GET+$defaults;
  // Construct request object
  $request = new Yubivs_Request();
  $request->api_version = $api_version;

  $request->id          = $arguments['id'       ];
  $request->h           = $arguments['h'        ];
  $request->otp         = $arguments['otp'      ];
  $request->timestamp   = $arguments['timestamp'];
  $request->nonce       = $arguments['nonce'    ];
  $request->sl          = $arguments['sl'       ];
  $request->timeout     = $arguments['timeout'  ];

  _yubivs_populate_request_processors($request);
  _yubivs_populate_response_processors($request);


  // If request looks valid, then we can check otp further
  $status = $request->verify();

  // Populate response
  $status = $request->respond();

  return _yubivs_format_output($request);
}
// }}}


// {{{ Helpers functions
/**
 * This function adds response processors to a simple request
 */
function _yubivs_populate_response_processors($request) {
  $default_processors = array(
    'Yubivs_Request_Processor_AddStatus',
    'Yubivs_Request_Processor_AddT',
    'Yubivs_Request_Processor_AddTimestamp',
    'Yubivs_Request_Processor_AddSessionCounter',
    'Yubivs_Request_Processor_AddSessionUse',
    'Yubivs_Request_Processor_AddSl',
    'Yubivs_Request_Processor_AddNonce',
    'Yubivs_Request_Processor_AddOtp',
    'Yubivs_Request_Processor_ResponseSignatureStringBuild',
    'Yubivs_Request_Processor_ResponseSignatureGenerate',
    );

  $pre_processors = module_invoke_all('yubivs_response_preprocessors');
  $post_processors = module_invoke_all('yubivs_response_postprocessors');

  $processors = $pre_processors + $default_processors + $post_processors;
  module_invoke_all('yubivs_response_processors_alter', $processors);

  foreach($processors as $processor) {
    $request->addResponseBackend(new $processor());
  }
}


/**
 * This function adds request processors to a simple request
 */
function _yubivs_populate_request_processors($request) {
  $default_processors = array(
    'Yubivs_Request_Processor_ClientIdMandatory',
    'Yubivs_Request_Processor_SignatureMandatory',
    'Yubivs_Request_Processor_TimestampMandatory',
    'Yubivs_Request_Processor_NonceMandatory',
    'Yubivs_Request_Processor_OtpMandatory',
    'Yubivs_Request_Processor_OtpRegexp',
    'Yubivs_Request_Processor_ClientIdLookup',
    'Yubivs_Request_Processor_RequestSignatureStringBuild',
    'Yubivs_Request_Processor_RequestSignatureGenerate',
    'Yubivs_Request_Processor_RequestSignatureValidate',
    'Yubivs_Request_Processor_YubikeyLookup',
    'Yubivs_Request_Processor_DecryptOtp',
    'Yubivs_Request_Processor_ReplayCheck',
    'Yubivs_Request_Processor_SaveCounters',
    );
  $pre_processors = module_invoke_all('yubivs_request_preprocessors');
  $post_processors = module_invoke_all('yubivs_request_postprocessors');

  $processors = $pre_processors + $default_processors + $post_processors;
  module_invoke_all('yubivs_request_processors_alter', $processors);

  foreach($processors as $processor) {
    $request->addRequestBackend(new $processor());
  }
}


/**
 * This function formats api output
 */
function _yubivs_format_output($request) {
  $return = array();

  // This part is enougth for api
  $return['#request'] = $request;

  // This part formats optionnal debug
  $return['result'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Result'),
    '#collapsible' => FALSE,
    'content' => array(
      '#type' => 'fieldset',
      '#title' => t('Result parameters'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      ),
    'result' => array(
      '#weight' => -1,
      '#markup' => t('@result (%hexval)', array(
        '@result' => $request->status,
        '%hexval' => sprintf('%04x', $request->status),
        )),
       '#type' => 'item',
       '#title' => t('Result'),
      ),
    );
  foreach($request->response as $name => $element) {
    $return['result']['content'][$name] = array(
      '#markup' => check_plain($element),
      '#type' => 'item',
      '#title' => check_plain($name),
      );
  }
  $return['process'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Process information'),
    'content' => array(
      ),
    );

  $reflector = new ReflectionClass('Yubivs_Request');
  foreach ($reflector->getConstants() as $constname => $value) {
    if (preg_match('#^STATUS_[A-Z_]+$#', $constname)) {
      $return['process']['content'][] = array(
        '#prefix' => '<p>',
        '#suffix' => '</p>',
        '#markup' => t('%constname (%value) is %status', array(
          '%constname' => drupal_substr($constname, 7),
          '%value' => sprintf('%04x', $value),
          '%status' => (($request->status & $value) || ($request->status == $value))? t('enabled'): t('disabled'),
          )),
        );
    }
  }


  return $return;
}
// }}}


