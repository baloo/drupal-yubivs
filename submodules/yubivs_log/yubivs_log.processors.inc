<?php

/**
 * @file 
 *  This file provides request processors for logging facility
 */
class Yubivs_Log_Request_Processor_LogRequest extends Yubivs_Request_Processor {
  public function process(Yubivs_Request $request) {
    $clientid = $request->client->nid;
    $yubikeyid = $request->yubikey->nid;
    $result = $request->status;

    $node = new stdClass;
    $node->type = 'yubivs_log';
    $node->yubivs_log_yubikey = array(
      'und' => array(array('nid' => $yubikeyid)),
    );
    $node->yubivs_log_client = array(
      'und' => array(array('nid' => $clientid)),
    );
    $node->language = 'und';

    node_save($node);

    dsm($request);
    watchdog('yubivs', 'fu');
    return Yubivs_Request::STATUS_OK;
  } 
}


