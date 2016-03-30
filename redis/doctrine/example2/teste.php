<?php

$redis = new Redis;
$redis->connect('127.0.0.1');

$doctrine = $redis->get('dc2_d42b9c57d24cf5db3bd8d332dc35437f_[Authores$CLASSMETADATA][1]');

print '<pre>';
print_r(unserialize($doctrine));