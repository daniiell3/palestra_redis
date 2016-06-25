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
      'drupal'   => 'Camp',
      // 'daniel' => 'Santos'
    );

    cache_set('list:data:apache', $data, 'cache', time() + 40);
  }

  // key drupal_:cache:list:data:apache

  drupal_json_output($data);
}
