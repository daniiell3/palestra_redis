<?php

require_once '../vendor/autoload.php';
 
use Doctrine\ORM\Tools\Setup;
use Doctrine\ORM\EntityManager;
use Doctrine\Common\Cache\RedisCache;

$redis = new Redis;
$redis->connect('127.0.0.1');
$redis->auth('mypass');
$redis->setOption(Redis::OPT_PREFIX, 'doctrine-example2:');
$redis->select(4);

$cache = new RedisCache;
$cache->setRedis($redis);
 
// the connection configuration
$dbParams = array(
  'driver'   => 'pdo_mysql',
  'user'     => 'root',
  'password' => '',
  'dbname'   => 'doctrine',
  'host'     => 'localhost',
  'port'     => '3307',
);
 
$config = Setup::createAnnotationMetadataConfiguration(array("/entities"), true, null, $cache);

$entityManager = EntityManager::create($dbParams, $config);
