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
//function webform_storage_toggle_rules_data_info() {
//  return array(
//    'webform_storage_toggle' => array(
//      'label' => t('Submission Data'),
//      'group' => t('Storage Toggle'),
//      'property info' => _webform_storage_toggle_rules_submission_info(),
//    ),
//  );
//}

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
 * Implements hook_rules_condition_info().
 */
function webform_storage_toggle_rules_condition_info() {
  /* Blank at the moment */
}


/**
 * Implements hook_rules_action_info().
 *
 * TODO: Review the access callback and see if we can mitigate it use in certain cases.
 *       For now, we omit it and hope for the best.
 *
 */
function webform_storage_toggle_rules_action_info() {
  $defaults = array(
    'group' => t('Storage Toggle'),
  );
  return array(
    'webform_storage_toggle_obfuscate' => $defaults + array(
        'label' => t('Obfuscate submission values'),
        'description' => t('This will apply the obfuscation value to the submission fields marked "<strong>Do not store this field\'s value in the DB</strong>"'),
        'base' => 'webform_storage_toggle_obfuscate_submission',
        'access callback' => 'webform_storage_toggle_node_access',
        'parameter' => array(
          'node' => array(
            'type' => 'node',
            'label' => t('Webform Node'),
            'description' => t('The full object of the webform node to update the submission for.'),
          ),
          'data' => array(
            'type' => 'webform',
            'label' => t('Submission'),
            'description' => t('The current submission values'),
            'allow null' => TRUE,
            'optional' => TRUE,
          ),
        ),
      ),
  );
}


/**
 * Node integration admin access callback.
 */
function webform_storage_toggle_node_access() {
  return user_access('administer nodes') || user_access('update anonymous submission');
}

/**
 * Rules action to obfuscate submission values
 */
function webform_storage_toggle_obfuscate_submission($node, $data = NULL) {
  // Make sure the needed functions are available.
  module_load_include('inc', 'webform', 'includes/webform.submissions');

  $filters = array(
    'nid' => $node->nid,
  );
  if (!empty($data)) {
    $filters['sid'] = $data['sid'];
  }
  //TODO: With the NODE ID and the SID we can now run through the submission, component by component and
  //      iterate through the list of values. As we
  //webform_submission_update($node, $submission)
}


/**
 * @} End of "defgroup rules_hooks".
 */




/**
 * @defgroup webform_storage_toggle_rules
 * @{
 */

/**
 * Metadata callbacks.
 */
function _webform_storage_toggle_rules_submission_info() {
  return array();
}

/**
 * @} End of "defgroup webform_storage_toggle_rules".
 */
