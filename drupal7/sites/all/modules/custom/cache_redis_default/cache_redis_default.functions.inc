<?php

/*
 ** Implements callback of menu redis/drupal-default
 */
function _cache_redis_default_callback() {
  if ($cached = cache_get('list:data:apache')) {
    $data = $cached->data;
  }

  if (empty($data)) {
    $data = array(
      'apache' => 'Barril',
      'eggs'   => 'Banana',
      // 'daniel' => 'Santos'
    );

    cache_set('list:data:apache', $data, 'cache', time() + 60);
  }

  drupal_json_output($data);
}
