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

  return system_settings_form($form);
}
// }}}


