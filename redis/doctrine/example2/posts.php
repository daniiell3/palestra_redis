<?php

require_once "bootstrap.php";
require_once "entities/Posts.php";
require_once "entities/Authores.php";

$postsRepo = $entityManager->getRepository('Posts');
$authoresRepo = $entityManager->getRepository('Authores');

$postsDB = $postsRepo->findAll();
$posts   = array();

foreach ($postsDB as $id => $post) {
  $posts[$id]['title'] = $post->getTitle();
  $author = $authoresRepo->find($post->getAuthor());

  $posts[$id]['author'] = $author->getName();
  $posts[$id]['body'] = $post->getBody();
}
