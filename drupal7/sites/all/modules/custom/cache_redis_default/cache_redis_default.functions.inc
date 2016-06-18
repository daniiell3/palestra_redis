<?php

/*
 ** Implements callback of menu /teste/redis
 */
function _cache_redis_default_callback() {
  if ($cached = cache_get('list:data:apache')) {
    $data = $cached->data;
  }

  if (empty($data)) {
    $data = array(
      'apache' => 'Barril',
      'eggs'   => 'Banana'
    );

    cache_set('list:data:apache', $data, 'cache', time() + 60*60);
  }

  drupal_json_output($data);
}
