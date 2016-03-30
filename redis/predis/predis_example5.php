<?php

include __DIR__ . '/predis.php';

$set_key = 'set_sorted';

$values = ['Daniel', 'Apache', 'Pedro', 'Barril', 'Denise'];

print 'Itens a serem inseridos<br>';
print_r($values);

for ($i=0; $i < count($values); $i++) { 
  $redis->zadd($set_key, 0, $values[$i]);
}

print '<br><br>';

print 'Todos os valores ja ordenados ASC por string<br>';

// Retorna todos os itens da lista
print_r($redis->zrange($set_key, 0, -1));

print '<br><br>';

print 'Quantidade de itens<br>';

print_r($redis->zcard($set_key));

print '<br><br>';

print 'Order By DESC pelo score<br>';

print_r($redis->zrevrangebyscore($set_key, '+inf', '-inf'));

print '<br><br>';

print 'Valor do score do Denise<br>';

print_r($redis->zrank($set_key, 'Denise'));
