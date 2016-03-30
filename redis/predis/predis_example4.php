<?php

include __DIR__ . '/predis.php';

$sorted_key = 'sorted';

$list_value = ['Daniel', 'Apache', 'Barril'];

// Insere os itens como uma lista
$redis->sadd($sorted_key, $list_value);

print 'Todos os valores<br>';

// Retorna todos os itens da lista
print_r($redis->smembers($sorted_key));

print '<br><br>';

print 'Quantidade de itens<br>';

print_r($redis->scard($sorted_key));

print '<br><br>';

print 'Remove o primeiro item<br>';

print 'Valor removido ' . $redis->spop($sorted_key) . '<br><br>';

print_r($redis->smembers($sorted_key));
