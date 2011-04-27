<?php
// vim: set foldmethod=marker sw=2 ts=2 et:
/**
 * @file
 * This file provides rules hooks in order to define complex
 * workflows around yubikeys 
 */

/**
 * Implements hook_rules_confition_info().
 * This hook defines conditions on yubivs_log node types
 */
function yubivs_log_rules_condition_info() {
  $conditions = array(
    'yubivs_log_auth' => array(
      'label' => t('Had attempt to auth more than N instances last M minutes'),
      'parameter' => array(
        'minutes'          => array('label' => t('Minutes'),          'type' => 'integer'),
        'instances'        => array('label' => t('Instances'),        'type' => 'integer'),
        ),
      'group' => t('Yubikey Validation Server'),
      'base' => 'yubivs_log_condition_auth',
      ),
    );
  $conditions['yubivs_log_successfull_auth'] = $conditions['yubivs_log_auth'];
  $conditions['yubivs_log_failed_auth']      = $conditions['yubivs_log_auth'];

  $conditions['yubivs_log_successfull_auth']['label'] = t('Had successfully authed more than N instances last M minutes');
  $conditions['yubivs_log_successfull_auth']['base'] = 'yubivs_log_condition_successfull_auth';

  $conditions['yubivs_log_failed_auth']['label'] = t('Had failed to auth more than N instances last M minutes');
  $conditions['yubivs_log_failed_auth']['base'] = 'yubivs_log_condition_failed_auth';

  return $conditions;
}


function _yubivs_log_rules_condition_auth_helper($node, $minutes, $instances, $only_failed, $only_successfull) {
  
}



