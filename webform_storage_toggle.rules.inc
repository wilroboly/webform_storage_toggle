<?php
/**
 * @file
 * Rules integration.
 */

/**
 * @defgroup rules_hooks Rules hooks
 * @{
 */

/**
 * Implements hook_rules_data_info().
 */
function webform_storage_toggle_rules_data_info() {
  return array(
    'webform_storage_toggle' => array(
      'label' => t('Submission Data'),
      'group' => t('Storage Toggle'),
      'property info' => _webform_storage_toggle_rules_submission_info(),
    ),
  );
}

/**
 * Implements hook_rules_event_info().
 */
function webform_storage_toggle_rules_event_info() {
  $defaults = array(
    'group' => t('Storage Toggle'),
    'module' => 'webform_storage_toggle',
  );
  return array(
    'after_submission_obfuscation' => $defaults + array(
        'label' => t('After a submission has been obfuscated'),
        'variables' => array(
          'submission' => array('type' => 'submission', 'label' => 'Submission value obfuscation'),
        ),
      ),
  );
}

/**
 * Implements hook_rules_action_info().
 */
function webform_storage_toggle_rules_action_info() {
  $defaults = array(
    'group' => t('Storage Toggle'),
  );
  return array(
    'webform_storage_toggle_obfuscate' => $defaults + array(
      'label' => t('Obfuscate submission value'),
      'description' => t('This will apply the obfuscation value to the submission field in question.'),
      'base' => 'webform_storage_toggle_rules_action_handle_default',
      'parameter' => array(
        'data' => array(
          'type' => 'data',
          'label' => t('Submission data value to obfuscate'),
        ),
        'message' => array(
          'type' => 'text',
          'label' => t('Message'),
          'sanitize' => TRUE,
          'translatable' => TRUE,
        ),
        'type' => array(
          'type' => 'token',
          'label' => t('Message type'),
          'options list' => 'rules_action_drupal_message_types',
          'default value' => 'status',
          'optional' => TRUE,
        ),
        'repeat' => array(
          'type' => 'boolean',
          'label' => t('Repeat message'),
          'description' => t("If disabled and the message has been already shown, then the message won't be repeated."),
          'default value' => TRUE,
          'optional' => TRUE,
          'restriction' => 'input',
        ),
      ),
    ),
  );
}

/**
 * Implements hook_rules_condition_info().
 */
function webform_storage_toggle_rules_condition_info() {
  /* Blank at the moment */
}

/**
 * @} End of "defgroup rules_hooks".
 */




/**
 * @defgroup condition_callbacks Condition callbacks
 * @{
 */

/**
 * Metadata callbacks.
 */
function _webform_storage_toggle_rules_submission_info() {
  return array();
}

/**
 * @} End of "defgroup condition_callbacks".
 */
