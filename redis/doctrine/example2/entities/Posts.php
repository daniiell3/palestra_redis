<?php

/**
 * @Entity @Table(name="posts")
 **/
class Posts {
  /** @Id @Column(type="integer") @GeneratedValue **/
  protected $id;
  /** @Column(type="string") **/
  protected $title;
  /** @Column(type="string") **/
  protected $body;
  /** @Column (type="integer") **/
  protected $author;
   
  public function getId(){
    return $this->id;
  }

  public function getTitle(){
    return $this->title;
  }

  public function setTitle($title){
    $this->title = $title;
  }

  public function getBody(){
    return $this->body;
  }

  public function setBody($body){
    $this->body = $body;
  }

  public function getAuthor(){
    return $this->author;
  }

  public function setAuthor($author){
    $this->author = $author;
  }
}
