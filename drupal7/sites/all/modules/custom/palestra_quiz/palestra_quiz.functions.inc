<?php

define('DATABASE', 6);
define('KEYTEAM', 'team');
define('TOTALKEY', 'total');

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

  if (!empty($option)) {
    if ($redis = _redis_connect(DATABASE)) {

      // string
      if (!$redis->get($option)) {
        $redis->set($option, 1);
      } else {
        $redis->incr($option);
      }

      if (!$redis->get(TOTALKEY)) {
        $redis->set(TOTALKEY, 1);
      } else {
        $redis->incr(TOTALKEY);
      }
      // end

      // hash
      /*
      if (!$redis->hget(KEYTEAM, $option)) {
        $redis->hset(KEYTEAM, $option, 1);
      } else {
        $redis->hincrby(KEYTEAM, $option, 1);
      }

      if (!$redis->hget(KEYTEAM, TOTALKEY)) {
        $redis->hset(KEYTEAM, TOTALKEY, 1);
      } else {
        $redis->hincrby(KEYTEAM, TOTALKEY, 1);
      }
      */
      // end

      $vote = $option;
    }
  }

  return drupal_json_output(array('vote' => $vote));
}

/**
 * Implements custom function of menu "quiz/placar"
 */
function _palestra_quiz_result() {
  // add custom js
  drupal_add_js(drupal_get_path('module', 'palestra_quiz') . '/assets/js/quiz-result.js');

  // add custom css
  drupal_add_css(drupal_get_path('module', 'palestra_quiz') . '/assets/css/quiz-result.css');

  return theme('quiz');
}

/**
 * Implements custom function of menu "quiz/result"
 */
function _palestra_quiz_result_callback() {
  $data = array('total' => 0);

  if ($redis = _redis_connect(DATABASE)) {
    $ponte_key   = 'ponte_preta';
    $guarani_key = 'guarani';
    $red_key     = 'red_bull';

    // string
    $data = array(
      'total' => ($redis->get(TOTALKEY)) ? $redis->get(TOTALKEY) : 0,
      'ponte' => ($redis->get($ponte_key)) ? $redis->get($ponte_key) : 0,
      'guarani' => ($redis->get($guarani_key)) ? $redis->get($guarani_key) : 0,
      'red' => ($redis->get($red_key)) ? $redis->get($red_key) : 0
    );

    // hash
    /*
    $data = array(
      'total' => ($redis->hget(KEYTEAM, TOTALKEY)) ? $redis->hget(KEYTEAM, TOTALKEY) : 0,
      'ponte' => ($redis->hget(KEYTEAM, $ponte_key)) ? $redis->hget(KEYTEAM, $ponte_key) : 0,
      'guarani' => ($redis->hget(KEYTEAM, $guarani_key)) ? $redis->hget(KEYTEAM, $guarani_key) : 0,
      'red' => ($redis->hget(KEYTEAM, $red_key)) ? $redis->hget(KEYTEAM, $red_key) : 0
    );
    */
  }

  drupal_json_output($data);
}
