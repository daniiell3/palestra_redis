<?php

require_once '../vendor/autoload.php';

use Doctrine\Common\Cache\RedisCache;

$redis = new Redis;
$redis->connect('127.0.0.1');
$redis->auth('mypass');
$redis->setOption(Redis::OPT_PREFIX, 'doctrine-example1:');
$redis->select(3);

$cache_driver = new RedisCache;
$cache_driver->setRedis($redis);

$cache_driver->setNamespace('doctrine_');

$cache_driver->save('doctrine_key', 'my value for doctrine');

$cache_driver->save('doctrine_array', ['key1' => 'value 1', 'key2' => 'value 2']);

if ($cache_driver->contains('doctrine_key')) {
  print_r($cache_driver->fetch('doctrine_key'));
}

print '<br><br>';

if ($cache_driver->contains('doctrine_array')) {
  print_r($cache_driver->fetch('doctrine_array'));  
}

if ($cache_driver->contains('doctrine_array')) {
  print '<br><br> Deletando chave "doctrine_key"<br><br>';
  
  $cache_driver->delete('doctrine_array');

  print_r($cache_driver->fetch('doctrine_array'));
}
