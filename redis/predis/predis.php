<?php

require_once __DIR__ . '/vendor/autoload.php';

use Predis\Client as Redis;

$parameters = [
  'scheme'   => 'tcp',
  'database' => 2,
  'password' => 'mypass'
];

$options = [
  'prefix'   => 'predis_'
];

$redis = new Redis($parameters, $options);