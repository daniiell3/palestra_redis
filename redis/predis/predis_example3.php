<?php

include __DIR__ . '/predis.php';

$list_key = 'list';

$list_value = ['Daniel', 'Apache', 'Barril'];

// Insere os itens como uma lista
$redis->lpush($list_key, $list_value);

print 'Todos os valores<br>';

// Retorna a quantidade de itens na chave
$itens = $redis->llen($list_key);

// Retorna todos os itens da lista
print_r($redis->lrange($list_key, 0, -1));

print '<br><br>';

print 'Quantidade de itens<br>';

print_r($itens);

print '<br><br>';

print 'Remove o primeiro item<br>';

$redis->lpop($list_key);

print_r($redis->lrange($list_key, 0, -1));
