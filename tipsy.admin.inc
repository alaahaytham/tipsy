<?php // $Id: tipsy.admin.inc,v 1.6 2010/11/14 12:37:25 doublethink Exp $

/*
 * Implementation of tipsy admin form
 */
function tipsy_admin() {
  $settings = _tipsy_get_settings();
   
  $form = array();
  $form['drupal_forms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Drupal forms general settings'),
    '#weight' => -5,
    '#collapsible' => TRUE,
    '#collapsed' => False,
  );
  $form['drupal_forms']['forms'] = array(
    '#type' => 'checkbox',
    '#default_value' => $settings['drupal_forms']['forms'],
    '#title' => t('Apply Tipsy for form items descriptions on all Drupal forms.'),
    '#description' => t('This will automatically enable Tipsy tooltips to form elements descriptions.'),
  );
  $form['drupal_forms']['wrapper'] = array(
      '#tree' => TRUE,
      '#weight' => 0,
      '#prefix' => '<div class="clear-block" id="tipsy-drupal-forms-wrapper">',
      '#suffix' => '</div>',
  );
  $form['drupal_forms']['wrapper']['options'] = tipsy_options_form($settings['drupal_forms'], true);
  
  $form['custom_selectors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom selectors'),
    '#weight' => -4,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['custom_selectors']['rules'] = array(
    '#tree' => TRUE,
    '#prefix' => '<div id="tipsy-custom-selectors">',
    '#suffix' => '</div>',
    '#theme' => 'tipsy_custom_selectors_form',
  );
  $form['custom_selectors']['rules_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add another rule'),
    '#submit' => array('tipsy_custom_selectors_add'), // If no javascript action.
    '#ahah' => array(
      'path' => 'admin/settings/tipsy/ahah',
      'wrapper' => 'tipsy-custom-selectors',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  if ($settings['custom_selectors']) {
	  foreach ($settings['custom_selectors'] as $delta => $options) {
	    $form['custom_selectors']['rules'][$delta] = tipsy_custom_selector_form($options);
	  }
  } else {
  	$form['custom_selectors']['rules'][0] = tipsy_custom_selector_form();
  }
  
  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );
  $form['#theme'] = 'system_settings_form';
  $form['#submit'][] = 'tipsy_admin_submit';
  return $form;
}

/*
 * Implementation of form function for the tooltip options
 */
function tipsy_options_form($settings = false, $drupal_forms = false) {
	if ($settings == false) { $settings = _tipsy_get_settings(true); }
	
	$form = array();
	$form['fade'] = array(
    '#type' => 'checkbox',
    '#default_value' => $settings['options']['fade'],
	  '#description' => t('This will make the tooltip fade.'),
    '#title' => t('Make Tipsy tooltips fade.'),
	  '#weight' => 0,
	  '#prefix' => '<div class="tipsy-selector-options clear-block">',
  );
  $form['gravity'] = array(
    '#type' => 'select',
    '#default_value' => $settings['options']['gravity'],
    '#title' => t('Tipsy arrow position'),
    '#description' => t('Specify the position of the tooltip when it appears.'),
    '#weight' => 2,
    '#options' => array(
      'nw' => t('North west'), 'n' => t('North'), 'ne' => t('North east'),
      'w' => t('West'), 'e' => t('East'), 'sw' => t('South west'), 's' => t('South'),
      'se' => t('South east'), 'autoNS' => t('Auto detect North/South'), 'autoWE' => t('Auto detect West/East')
    ),
  );
  $form['delayIn'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['options']['delayIn'],
    '#title' => t('Delay when appearing'),
    '#description' => t('Amount of milliseconds for the tooltip to appear.'),
    '#size' => 5,
    '#maxlength' => 5,
    '#weight' => 3,
  );
  $form['delayOut'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['options']['delayOut'],
    '#title' => t('Delay when disappearing'),
    '#description' => t('Amount of milliseconds for the tooltip to disappear.'),
    '#size' => 5,
    '#maxlength' => 5,
    '#weight' => 4,
  );
  $form['trigger'] = array(
    '#type' => 'select',
    '#default_value' => $settings['options']['trigger'],
    '#description' => t('Specify what action will make the tooltip appear.'),
    '#title' => t('Tipsy trigger'),
    '#weight' => 5,
    '#options' => array(
      'focus' => t('Focus'), 'hover' => t('Hover')
    ),
  );
  $form['opacity'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['options']['opacity'],
    '#title' => t('Tooltip opacity'),
    '#description' => t('A value between 0 and 1.'),
    '#size' => 5,
    '#maxlength' => 4,
    '#weight' => 6,
  );
  $form['offset'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['options']['offset'],
    '#title' => t('Tooltip offset'),
    '#description' => t('Number of pixels in which the tooltip will distance from the element.'),
    '#size' => 5,
    '#maxlength' => 5,
    '#weight' => 7,
  );
  if ($drupal_forms == false) {
  	$form['html'] = array(
	    '#type' => 'checkbox',
	    '#default_value' => $settings['options']['html'],
	    '#description' => t('This will let HTML code be parsed inside the tooltip.'),
	    '#title' => t('Allow HTML in tooltip content.'),
  	  '#weight' => 1,
    );
    $form['title'] = array(
      '#type' => 'textarea',
      '#title' => t('Tooltip content'),
	    '#default_value' => $settings['options']['title'],
	    '#description' => t("Specify the HTML attribute which will be the content of the tooltip.<br />Refer to the module's README.txt for advanced usage of this feature."),
	    '#rows' => 1,
	    '#maxlength' => 400,
      '#weight' => 9,
    );
  }
  $form['closure'] = array(
      '#weight' => 10,
      '#suffix' => '</div>',
  );
  return $form;
}

/*
 * Implementation of a single tipsy rule form
 */
function tipsy_custom_selector_form($options = false) {
  $form = array();
  $form['#tree'] = TRUE;
  $form['selector'] = array(
    '#type' => 'textarea',
    '#weight' => 1,
    '#rows' => 2,
    '#default_value' => $options['selector'],
  );
  $form['options'] = tipsy_options_form($options);
  return $form;
}

/*
 * Theme the table form for tipsy rules
 */
function theme_tipsy_custom_selectors_form($form) {
  $rows = array();
  $headers = array(t('Selectors'), t('Options'));
  foreach (element_children($form) as $key) {
    $row = array(
      'data' => array(
        array('data' => drupal_render($form[$key]['selector'])),
        array('data' => drupal_render($form[$key]['options'])),
      ),
    ); $rows[] = $row;
  }
  $output = theme('table', $headers, $rows);
  $output .= drupal_render($form);
  return $output;
}

/*
 * Implementation of hook_validate for admin form
 */
function tipsy_admin_validate($form, &$form_values) {
  $drupal_forms = $form_values['values']['wrapper'];
  if ($form_values['values']['forms'] != 0) {
	  if (!is_numeric($drupal_forms['options']['delayIn']) || $drupal_forms['options']['delayIn'] == '') {
	  	form_set_error('wrapper][options][delayIn', t('Invalid value'));
	  }
	  if (!is_numeric($drupal_forms['options']['delayOut']) || $drupal_forms['options']['delayOut'] == '') {
	    form_set_error('wrapper][options][delayOut', t('Invalid value'));
	  }
	  if (!is_numeric($drupal_forms['options']['opacity']) || $drupal_forms['options']['opacity'] == '') {
	    form_set_error('wrapper][options][opacity', t('Invalid value'));
	  }
	  if (!is_numeric($drupal_forms['options']['offset']) || $drupal_forms['options']['offset'] == '') {
	    form_set_error('wrapper][options][offset', t('Invalid value'));
	  }
  }
  
  foreach($form_values['values']['rules'] as $delta => $rule) {
  	if (trim($rule['selector']) != '') {
      if (!is_numeric($rule['options']['delayIn']) || $rule['options']['delayIn'] == '') {
	      form_set_error('rules][' . $delta .  '][options][delayIn', t('Invalid value'));
	    }
	    if (!is_numeric($rule['options']['delayOut']) || $rule['options']['delayOut'] == '') {
	      form_set_error('rules][' . $delta .  '][options][delayOut', t('Invalid value'));
	    }
	    if (!is_numeric($rule['options']['opacity']) ||$rule['options']['opacity'] == '') {
	      form_set_error('rules][' . $delta .  '][options][opacity', t('Invalid value'));
	    }
	    if (!is_numeric($rule['options']['offset']) || $rule['options']['offset'] == '') {
	      form_set_error('rules][' . $delta .  '][options][offset', t('Invalid value'));
	    }
  	  if (trim($rule['options']['title']) == '') {
        form_set_error('rules][' . $delta .  '][options][title', t("Invalid value set for title. Use <em>title</em> if you don't know what you are doing"));
      }
  	}
  }
}

/*
 * Implementation of form submit function for the admin form
 */
function tipsy_admin_submit($form, &$form_values) {
  $settings = array();
  $drupal_forms = $form_values['values']['wrapper'];
  
  $settings['drupal_forms'] = array(
    'forms' => $form_values['values']['forms'],
    'options' => array(
      'fade' => $drupal_forms['options']['fade'],
      'gravity' => $drupal_forms['options']['gravity'],
      'delayIn' => trim($drupal_forms['options']['delayIn']),
      'delayOut' => trim($drupal_forms['options']['delayOut']),
      'trigger' => $drupal_forms['options']['trigger'],
      'opacity' => trim($drupal_forms['options']['opacity']),
      'offset' => trim($drupal_forms['options']['offset'])
    )
  );
  foreach($form_values['values']['rules'] as $delta => $rule) {
  	if (trim($rule['selector']) != '') {
	    $settings['custom_selectors'][] = array(
	      'selector' => trim($rule['selector']),
	      'options' => array(
	        'fade' => $rule['options']['fade'],
          'gravity' => $rule['options']['gravity'],
          'trigger' => $rule['options']['trigger'],
			    'delayIn' => trim($rule['options']['delayIn']),
			    'delayOut' => trim($rule['options']['delayOut']),
			    'opacity' => trim($rule['options']['opacity']),
			    'offset' => trim($rule['options']['offset']),
	        'html' => $rule['options']['html'],
			    'title' => trim($rule['options']['title']),
	      )
	    );
  	}
  }
  variable_set('tipsy', $settings);
  drupal_set_message(t('Configuration saved'));
}

/*
 * This function will work if JavaScript is disabled to add the new tipsy rule form
 */
function tipsy_custom_selectors_add() {
  
}

/*
 * AHAH callback to render the tipsy rules form
 */
function _tipsy_custom_selectors_ahah() {
	$delta = count($_POST['rules']);
  $details = array('delta' => $delta);
  $form_element = tipsy_custom_selector_form();
  drupal_alter('form', $form_element, array(), '_tipsy_custom_selectors_ahah');
  
  // Build the new form.
  $form_state = array('submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);
  $form['custom_selectors']['rules'][$delta] = $form_element;
  form_set_cache($form_build_id, $form, $form_state);
  $form += array('#post' => $_POST, '#programmed' => FALSE,);
  $form = form_builder('tipsy_admin', $form, $form_state);
  
  // Render the new output.
  $rules_form = $form['custom_selectors']['rules'];
  $output = theme('status_messages') . drupal_render($rules_form);
  drupal_json(array('status' => TRUE, 'data' => $output));
}