<?php

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
