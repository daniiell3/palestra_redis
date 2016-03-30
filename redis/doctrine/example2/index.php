<?php
  require_once "posts.php";
?>

<ul>
  <?php foreach($posts as $post): ?>
    <li>
      <h2><?php print $post['title']; ?></h2>
      <span><?php print $post['author']; ?></span>
      <div>
        <p><?php print $post['body']; ?></p>
      </div>
    </li>
  <?php endforeach; ?>
</ul>