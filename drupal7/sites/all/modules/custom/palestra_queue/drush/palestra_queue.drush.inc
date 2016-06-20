<?php

/**
* Implements hook_drush_help().
*/
function palestra_queue_drush_help($section) {
  switch ($section) {
    case 'drush:palestra-queue':
      return dt('Atualiza todos os nodes recentes');
    break;
  }
}
 
/**
* Implements hook_drush_command().
*/
function palestra_queue_drush_command() {
  return array(
    'palestra-queue' => array(
    'callback' => '_palestra_queue_drush_callback',
    'description' => 'Atualiza todos os nodes recentes',
    'aliases' => array('pa-at')
    ),
    'examples' => array(
      'drush palestra-queue' => 'Atualiza todos os nodes recentes'
    )
  );
}

function _palestra_queue_drush_callback() {
  if ($redis = _redis_connect(7)) {
    $nids = $redis->smembers('nodes');

    if (!empty($nids)) {
      foreach ($nids as $key => $nid) {
        $node  = node_load($nid);
        $title = $node->title;

        $pos = strpos($title, '- DrupalCamp');

        if ($pos === false) { 
          $node->title = $title . ' - DrupalCamp';
        }

        if (!isset($node->field_image[LANGUAGE_NONE])) {
          $node->field_image[LANGUAGE_NONE][0] = array('fid' => 1);
        }

        node_save($node);

        drush_log('Conteúdo ' . $title . ' atualizado com sucesso.', 'success');
        $redis->sRem('nodes', $nid);
      }
    } 
    else {
      drush_log('Sem conteúdo na fila para atualizar', 'warning');
    }
  }
}
