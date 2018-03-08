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
 *
 * The reason we have this rule is in order for some obfuscation to happen, it would have to occur
 * after the submission already exists in the DB. This could be due to a post-processing module on the
 * webform submission. Obfuscation could happen on submission in a normal course of action, but would
 * therefore empty the fields when an action occurs on the submission post the "saved" values. This would
 * mean values analyzed or managed on the submission would return incorrect information. This method helps
 * to permit values stored in the DB for post-submission processing can be acted upon and once completed,
 * this RULES ACTION could then be applied, filtering through all the fields which are flagged "ready for
 * obfuscation".
 */
function webform_storage_toggle_obfuscate_submission($node, $data = NULL) {
  // Make sure the needed functions are available.
  module_load_include('inc', 'webform', 'includes/webform.submissions');

  if (!empty($data) && is_object($node) && !empty($node->webform)) {
    // Get the submission object from the DB
    $submission = webform_get_submission($node->webform['nid'], $data['sid']);
    // Iterate through the webform submission and obfuscate
    foreach ($data['components'] as $name => $component) {
      // We're checking to see if the object is requesting to be processed via a rule in post.
      if (isset($component['component']['extra']['webform_storage_toggle_process_order']) && ($component['component']['extra']['webform_storage_toggle_process_order'] == 'post')) {
        // modify the submission object
        $submission->data[$component['component']['cid']][0] = _webform_storage_toggle_obfuscate_value($component['component']);
      }
    }
    // Here, once the $data object has been updated, we run the update on the submission data.
    $result = webform_submission_update($node, $submission);

    watchdog('webform_storage_toggle', 'Obfuscation of webform %webformID submission %subID completed.', array('%webformID' => $node->webform['nid'], '%subID' => $data['sid']), WATCHDOG_INFO);

  }


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
