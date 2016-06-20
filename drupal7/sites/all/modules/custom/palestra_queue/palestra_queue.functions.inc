<?php

/*
 * Implements custom function for add item in redis
 */
function _palestra_queue_add($nid) {
  if ($redis = _redis_connect(7)) {
    $redis->sAdd('nodes', $nid);
  }
}
