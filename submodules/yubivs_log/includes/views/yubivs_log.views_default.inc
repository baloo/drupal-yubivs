<?php


/**
 * Implement hook_views_default_views().
 */
function yubivs_log_views_default_views() {
  /*
   * View 'yubivs_log'
   */
  $view = new view;
  $view->name = 'yubivs_log';
  $view->description = 'This view displays list of authentications for a yubikey';
  $view->tag = 'yubikey yubivs log';
  $view->base_table = 'node';
  $view->human_name = 'yubivs_log';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = FALSE;
  $handler->display->display_options['header']['area']['content'] = 'The yubikey has been seen last on following points';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No validation log match filters';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date:';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created_1']['id'] = 'created_1';
  $handler->display->display_options['fields']['created_1']['table'] = 'node';
  $handler->display->display_options['fields']['created_1']['field'] = 'created';
  $handler->display->display_options['fields']['created_1']['label'] = '';
  $handler->display->display_options['fields']['created_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created_1']['date_format'] = 'time ago';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['external'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node']['text'] = 'See more';
  /* Field: Content: The yubikey authenticated */
  $handler->display->display_options['fields']['yubivs_log_yubikey']['id'] = 'yubivs_log_yubikey';
  $handler->display->display_options['fields']['yubivs_log_yubikey']['table'] = 'field_data_yubivs_log_yubikey';
  $handler->display->display_options['fields']['yubivs_log_yubikey']['field'] = 'yubivs_log_yubikey';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Fields: The yubikey authenticated (yubivs_log_yubikey) - nid */
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['id'] = 'yubivs_log_yubikey_nid';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['table'] = 'field_data_yubivs_log_yubikey';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['field'] = 'yubivs_log_yubikey_nid';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['summary']['format'] = 'default_summary';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'yubivs_log' => 'yubivs_log',
  );
  /* Filter criterion: Authentification date */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'node';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['ui_name'] = 'Authentification date';
  $handler->display->display_options['filters']['created']['operator'] = 'between';
  $handler->display->display_options['filters']['created']['value']['min'] = '-1 month';
  $handler->display->display_options['filters']['created']['value']['max'] = 'now';
  $handler->display->display_options['filters']['created']['value']['type'] = 'offset';
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Date';
  $handler->display->display_options['filters']['created']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
  $handler->display->display_options['filters']['created']['expose']['multiple'] = FALSE;
  /* Filter criterion: Fields: The yubikey authenticated (yubivs_log_yubikey) - nid */
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['id'] = 'yubivs_log_yubikey_nid';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['table'] = 'field_data_yubivs_log_yubikey';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['field'] = 'yubivs_log_yubikey_nid';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['expose']['operator_id'] = 'yubivs_log_yubikey_nid_op';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['expose']['label'] = 'Fields: The yubikey authenticated (yubivs_log_yubikey) - nid';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['expose']['operator'] = 'yubivs_log_yubikey_nid_op';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['expose']['identifier'] = 'yubivs_log_yubikey_nid';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['expose']['reduce'] = 0;

  /* Display: yubikey */
  $handler = $view->new_display('block', 'yubikey', 'yubivs_yubikey');
  $handler->display->display_options['display_description'] = 'yubikey view';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date:';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created_1']['id'] = 'created_1';
  $handler->display->display_options['fields']['created_1']['table'] = 'node';
  $handler->display->display_options['fields']['created_1']['field'] = 'created';
  $handler->display->display_options['fields']['created_1']['label'] = '';
  $handler->display->display_options['fields']['created_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created_1']['date_format'] = 'time ago';
  /* Field: Content: The client requesting authentication */
  $handler->display->display_options['fields']['yubivs_log_client']['id'] = 'yubivs_log_client';
  $handler->display->display_options['fields']['yubivs_log_client']['table'] = 'field_data_yubivs_log_client';
  $handler->display->display_options['fields']['yubivs_log_client']['field'] = 'yubivs_log_client';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['external'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node']['text'] = 'See more';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Fields: The yubikey authenticated (yubivs_log_yubikey) - nid */
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['id'] = 'yubivs_log_yubikey_nid';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['table'] = 'field_data_yubivs_log_yubikey';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['field'] = 'yubivs_log_yubikey_nid';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['yubivs_log_yubikey_nid']['not'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'yubivs_log' => 'yubivs_log',
  );
  /* Filter criterion: Authentification date */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'node';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['ui_name'] = 'Authentification date';
  $handler->display->display_options['filters']['created']['operator'] = 'between';
  $handler->display->display_options['filters']['created']['value']['min'] = '-1 month';
  $handler->display->display_options['filters']['created']['value']['max'] = 'now';
  $handler->display->display_options['filters']['created']['value']['type'] = 'offset';
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Date';
  $handler->display->display_options['filters']['created']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
  $handler->display->display_options['filters']['created']['expose']['multiple'] = FALSE;
  /* Filter criterion: Fields: The client requesting authentication (yubivs_log_client) - nid */
  $handler->display->display_options['filters']['yubivs_log_client_nid']['id'] = 'yubivs_log_client_nid';
  $handler->display->display_options['filters']['yubivs_log_client_nid']['table'] = 'field_data_yubivs_log_client';
  $handler->display->display_options['filters']['yubivs_log_client_nid']['field'] = 'yubivs_log_client_nid';
  $handler->display->display_options['filters']['yubivs_log_client_nid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['yubivs_log_client_nid']['expose']['operator_id'] = 'yubivs_log_client_nid_op';
  $handler->display->display_options['filters']['yubivs_log_client_nid']['expose']['label'] = 'Fields: The client requesting authentication (yubivs_log_client) - nid';
  $handler->display->display_options['filters']['yubivs_log_client_nid']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['yubivs_log_client_nid']['expose']['operator'] = 'yubivs_log_client_nid_op';
  $handler->display->display_options['filters']['yubivs_log_client_nid']['expose']['identifier'] = 'yubivs_log_client_nid';
  $handler->display->display_options['filters']['yubivs_log_client_nid']['expose']['required'] = FALSE;
  $handler->display->display_options['filters']['yubivs_log_client_nid']['expose']['remember'] = FALSE;
  $handler->display->display_options['filters']['yubivs_log_client_nid']['expose']['multiple'] = FALSE;

  /* Display: client */
  $handler = $view->new_display('block', 'client', 'yubivs_client');
  $handler->display->display_options['display_description'] = 'client view';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date:';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created_1']['id'] = 'created_1';
  $handler->display->display_options['fields']['created_1']['table'] = 'node';
  $handler->display->display_options['fields']['created_1']['field'] = 'created';
  $handler->display->display_options['fields']['created_1']['label'] = '';
  $handler->display->display_options['fields']['created_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created_1']['date_format'] = 'time ago';
  /* Field: Content: The yubikey authenticated */
  $handler->display->display_options['fields']['yubivs_log_yubikey']['id'] = 'yubivs_log_yubikey';
  $handler->display->display_options['fields']['yubivs_log_yubikey']['table'] = 'field_data_yubivs_log_yubikey';
  $handler->display->display_options['fields']['yubivs_log_yubikey']['field'] = 'yubivs_log_yubikey';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['external'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node']['text'] = 'See more';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Fields: The client requesting authentication (yubivs_log_client) - nid */
  $handler->display->display_options['arguments']['yubivs_log_client_nid']['id'] = 'yubivs_log_client_nid';
  $handler->display->display_options['arguments']['yubivs_log_client_nid']['table'] = 'field_data_yubivs_log_client';
  $handler->display->display_options['arguments']['yubivs_log_client_nid']['field'] = 'yubivs_log_client_nid';
  $handler->display->display_options['arguments']['yubivs_log_client_nid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['yubivs_log_client_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['yubivs_log_client_nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['yubivs_log_client_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['yubivs_log_client_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['yubivs_log_client_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['yubivs_log_client_nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['yubivs_log_client_nid']['not'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'yubivs_log' => 'yubivs_log',
  );
  /* Filter criterion: Authentification date */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'node';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['ui_name'] = 'Authentification date';
  $handler->display->display_options['filters']['created']['operator'] = 'between';
  $handler->display->display_options['filters']['created']['value']['min'] = '-1 month';
  $handler->display->display_options['filters']['created']['value']['max'] = 'now';
  $handler->display->display_options['filters']['created']['value']['type'] = 'offset';
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Date';
  $handler->display->display_options['filters']['created']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
  $handler->display->display_options['filters']['created']['expose']['multiple'] = FALSE;
  /* Filter criterion: Fields: The yubikey authenticated (yubivs_log_yubikey) - nid */
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['id'] = 'yubivs_log_yubikey_nid';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['table'] = 'field_data_yubivs_log_yubikey';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['field'] = 'yubivs_log_yubikey_nid';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['expose']['operator_id'] = 'yubivs_log_yubikey_nid_op';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['expose']['label'] = 'Fields: The yubikey authenticated (yubivs_log_yubikey) - nid';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['expose']['operator'] = 'yubivs_log_yubikey_nid_op';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['expose']['identifier'] = 'yubivs_log_yubikey_nid';
  $handler->display->display_options['filters']['yubivs_log_yubikey_nid']['expose']['reduce'] = 0;
  $translatables['yubivs_log'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('The yubikey has been seen last on following points'),
    t('No validation log match filters'),
    t('Date:'),
    t('See more'),
    t('The yubikey authenticated'),
    t('All'),
    t('Date'),
    t('Fields: The yubikey authenticated (yubivs_log_yubikey) - nid'),
    t('yubikey'),
    t('yubikey view'),
    t('The client requesting authentication'),
    t('Fields: The client requesting authentication (yubivs_log_client) - nid'),
    t('client'),
    t('client view'),
  );
  $views[$view->name] = $view;

  return $views;
}


