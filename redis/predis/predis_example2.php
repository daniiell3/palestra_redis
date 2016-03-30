<?php

include __DIR__ . '/predis.php';

$hash_key = 'hash';

$hash_value = [
  'field1' => 'value field 1',
  'field2' => 'value field 2'
];

$redis->hmset($hash_key, $hash_value);

print 'Todos os valores<br>';

print_r($redis->hvals($hash_key));

print '<br><br>';

print 'Field especifico<br>';

print_r($redis->hmget($hash_key, 'field1'));