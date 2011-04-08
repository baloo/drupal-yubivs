<?php

/**
 * @file
 * Hooks provided by Yubikey Validation Server module
 */

/**
 * @addtogroup hooks
 * @{
 */


/**
 * Adds custom preprocessors to the request processing chain
 * @return
 *   * String of processor class
 *   * Array of string of processor class
 */
function hook_yubivs_request_preprocessors() {
  return 'foobar_Request_Processor_LogRequest';
}


/**
 * Adds custom preprocessors to the response processing chain
 * @return
 *   * String of processor class
 *   * Array of string of processor class
 */
function hook_yubivs_response_preprocessors() {
  return array(
    'foobar_Request_Processor_AddYubikeyNodeId',
    'foobar_Request_Processor_AdditionalInformation',
    );
}


/**
 * Adds custom postprocessors to the request processing chain
 * @return
 *   * String of processor class
 *   * Array of string of processor class
 */
function hook_yubivs_request_postprocessors() {
  return 'foobar_Request_Processor_VerifyAgainstOtherBackend';
}


/**
 * Adds custom postprocessors to the response processing chain
 * @return
 *   * String of processor class
 *   * Array of string of processor class
 */
function hook_yubivs_response_postprocessors() {
  return array(
    'foobar_Request_Processor_PublicKeySignature',
    'foobar_Request_Processor_LogReponse',
    );
}


/**
 * Alters request processors
 * @param $processors
 *   The array of request processors
 */
function hook_yubivs_request_processors_alter(&$processors) {
  // Removes some processors
  $processors = array_diff($processors, array(
    'I_Dont_Want_This_One',
    'Nor_This_One',
    ));
}


/**
 * Alters response processors
 * @param $processors
 *   The array of response processors
 */
function hook_yubivs_response_processors_alter(&$processors) {
  // Replaces some processors
  foreach ($processors as $id => $name) {
    if ($name === 'Yubivs_Request_Processor_RequestSignatureStringBuild') {
      $processors[$id] = 'Yubivs_Request_Processor_RequestSignatureStringBuildAnotherWay';
    }
  }
}


/**
 * @} End of "addtogroup hooks".
 */
