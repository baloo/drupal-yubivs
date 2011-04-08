<?php
// vim: set foldmethod=marker sw=2 ts=2 et:
/**
 * @file
 * This file provides administration pages for yubikey
 * validation server service
 */


// {{{ Administration Menu callbacks
/**
 * Administration page for setting yubikey related variables
 */
function yubivs_admin_settings() {
  $form = array();


  $form['yubivs_mandatory_signature'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use of request signature is mandatory'),
    '#default_value' => variable_get('yubivs_mandatory_signature', FALSE),
    '#description' => t("Use of request signature is mandatory to have a response from this validation server."),
  );


  $form['yubivs_mandatory_timestamp'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force client to request timestamp'),
    '#default_value' => variable_get('yubivs_mandatory_timestamp', FALSE),
    '#description' => t("This force the client to request for a timestamp to get the otp validated. Note: use of this feature will force the user to use at least Validation protocol version 1.1 or more"),
  );

  return system_settings_form($form);
}
// }}}


