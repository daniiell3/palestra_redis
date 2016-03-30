<?php

include __DIR__ . '/predis.php';

$string_key = 'string';

$redis->set($string_key, 'my cache value');

print_r($redis->get($string_key));
