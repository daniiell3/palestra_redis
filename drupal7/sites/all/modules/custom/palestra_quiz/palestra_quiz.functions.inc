<?php

/**
 * Implements custom function of menu "quiz"
 */
function _palestra_quiz_form() {
  $form['#id'] = 'palestra_quiz';

  $form['team_campinas'] = array(
    '#type'    => 'radios',
    '#title'   => t('Qual o maior time de Campinas?'),
    '#options' => array('ponte_preta' => t('Ponte Preta'), 'guarani' => t('Guarani'), 'red_bull' => t('Red Bull Brasil'))
  );

  $form['submit'] = array(
    '#type'   => 'submit',
    '#value'  => t('Votar'),
  );

  // add custom js
  drupal_add_js(drupal_get_path('module', 'palestra_quiz') . '/assets/js/quiz.js');

  // add custom css
  drupal_add_css(drupal_get_path('module', 'palestra_quiz') . '/assets/css/quiz.css');

  return $form;
}

/**
 * Implements custom function of menu "quiz/vote"
 */
function _palestra_quiz_vote_computed() {
  $option    = (isset($_POST['vote'])) ? $_POST['vote'] : '';
  $vote      = '';
  $total_key = 'total';

  if (!empty($option)) {
    if ($redis = _redis_connect(6)) {
      if (!$redis->get($option)) {
        $redis->set($option, 1);
      } else {
        $redis->incr($option);
      }

      if (!$redis->get($total_key)) {
        $redis->set($total_key, 1);
      } else {
        $redis->incr($total_key);
      }

      $vote = $option;
    }
  }

  return drupal_json_output(array('vote' => $vote));
}
