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


  // Not yet implemented
  public $sl;
  public $timeout;


  // Array of Yubivs_Request_Processor objects;
  protected $backends;


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
    foreach($this->backends as $backend) {
      $result |= $backend->verify($this);

      if($result !== self::STATUS_OK) {
        break;
      }
    }
    return $result;
  }

  /**
   * Setter for backends list
   */
  public function addBackend(Yubivs_Request_Processor $backend) {
    $this->backends[] = $backend;
  }

  /**
   * Logger function
   */
  public function log($message, $return = self::STATUS_NAN) {
    // TODO implement this function with watchdog stuff and backtrace 
  }
}
// }}}


// {{{ API Menu callbacks
/**
 * Verify callback
 */
function yubivs_verify($api_version) {
  $defaults = array(
    'id'        => '',
    'otp'       => '',
    'h'         => '',
    'timestamp' => '',
    'nonce'     => '',
    'sl'        => '',
    'timeout'   => '',
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

  _yubivs_populate_processors($request);


  // If request looks valid, then we can check otp further
  $status = $request->verify();

  

//  switch($status) {
//    case Yubivs_Request::STATUS_OK:
//    case Yubivs_Request::STATUS_BAD_OTP:
//    case Yubivs_Request::STATUS_REPLAYED_OTP:
//    case Yubivs_Request::STATUS_BAD_SIGNATURE:
//    case Yubivs_Request::STATUS_MISSING_PARAMETER:
//    case Yubivs_Request::STATUS_NO_SUCH_CLIENT:
//    case Yubivs_Request::STATUS_OPERATION_NOT_ALLOWED:
//    case Yubivs_Request::STATUS_BACKEND_ERROR:
//    case Yubivs_Request::STATUS_NOT_ENOUGH_ANSWERS:
//    case Yubivs_Request::STATUS_REPLAYED_REQUEST:
//      dsm($status);
//      break;
//  }


  dsm($status);
  dsm($request);
  dsm($api_version);
  dsm(arg());
  dsm($_GET);

  return '';
}
// }}}


// {{{ Helpers functions
function _yubivs_populate_processors($request) {
  $processors = array(
    'Yubivs_Request_Processor_SignatureMandatory',
    'Yubivs_Request_Processor_TimestampMandatory',
    'Yubivs_Request_Processor_NonceMandatory',
    'Yubivs_Request_Processor_OtpMandatory',
    'Yubivs_Request_Processor_OtpRegexp',
    'Yubivs_Request_Processor_DecryptOtp',
//    '',
//    '',
//    '',
//    '',
    );
  foreach($processors as $processor) {
    $request->addBackend(new $processor());
  }
}
// }}}


