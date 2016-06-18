<?php

/*
 * Implements callback of menu /palestra
 */
function _palestra_acessos_callback() {
  $result = [];

  if ($redis = _redis_connect()) {
    $result['requests'] = ($redis->get(REDIS_INCR)) ? $redis->get(REDIS_INCR) : '';

    $result['ips'] = (!empty($redis->zrange(REDIS_IPS, 0, -1))) ? $redis->zrange(REDIS_IPS, 0, -1) : '';

    $result['single_request_by_ip'] = (!empty($redis->zcard(REDIS_IPS))) ? $redis->zcard(REDIS_IPS) : '';
  }

  drupal_json_output($result);
}

/*
 * Implements callback of menu /palestra
 */
function _palestra_callback() {
  if ($redis = _redis_connect()) {
    // Incrementando requests
    _palestra_requests($redis, REDIS_INCR);

    // guardando ips
    _palestra_ip($redis, REDIS_IPS);

    // add custom js
    drupal_add_js(drupal_get_path('module', 'palestra_acessos') . '/assets/js/palestra.js');

    // add custom css
    drupal_add_css(drupal_get_path('module', 'palestra_acessos') . '/assets/css/palestra.css');
  }

  return theme('palestra');
}

/*
 * Implements custom function redis connect
 */
function _redis_connect() {
  $redis = null;

  if ('PhpRedis' === variable_get('redis_client_interface')) {
    $redis = new Redis;
    $redis->connect(variable_get('redis_client_host'));
    $redis->auth(variable_get('redis_client_password'));
    $redis->select(5);
  }

  return $redis;
}

/*
 * Implements custom function set in redis increment in each request
 */
function _palestra_requests($redis, $key) {
  if ($redis->get($key)) {
    $redis->incr($key);
  } else {
    $redis->set($key, 1);
  }
}

/*
 * Implements custom function set in redis ip client in request
 */
function _palestra_ip($redis, $key) {
  if ($ip = _get_ip()) {
    if (!in_array($ip, $redis->zrange($key, 0, -1))) {
      $score = $redis->zcard($key);

      $redis->zadd($key, $score, $ip);
    } 
  }
}

/*
 * Implements custom function get client ip
 */
function _get_ip() {
  $ip = null;

  if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
    $ip = $_SERVER['HTTP_CLIENT_IP'];
  } elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
    $ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
  } else {
    $ip = $_SERVER['REMOTE_ADDR'];
  }

  return $ip;
}
