<?php
/**
 * @file
 */

/**
 * Class JoindinEventCommentCollection
 */
class JoindinEventCommentCollection extends JoindinCollection {

  public $comment_list = array();

  /**
   * Constructor.
   *
   * @param String $json
   *   JSON data from the JoindIn API representing a list of 1 or more comments.
   */
  function __construct($data) {
    $this->_constructFromJSON($data);
  }

  /**
   * Build an event using a JSON data structure.
   *
   * @param String $json
   *   JSON data from the JoindIn API representing a list of 1 or more events.
   */
  public function _constructFromJSON($json) {
    // Decode the JSON.
    $comments = drupal_json_decode($json);

    // The API wraps the response for a single talk with 2 tiers of array:
    // $events = array('comments' => array(0 => array(………), 1 => array(………))).
    if (is_array($comments) && isset($comments['comments'])) {
      foreach ($comments['comments'] as $comment_data) {
        // If an array is passed to the JoindinEvent constructor, the event
        // data is automatically populated from the array properties.
        $comment = new JoindinEventComment($comment_data);
        // Index by comment ID.
        $this->collection[$comment->comment_id] = $comment;
      }
    }
  }

  /**
   * Get the comments in this collection.
   *
   * @return Array
   *   An unordered array of JoindinEventComment objects.
   */
  public function getComments() {
    return $this->comment_list;
  }

  /**
   * Get a comment in this collection.
   *
   * @param optional int $comment_id
   *   The comment_id of the desired talk. If omitted, the first resource in the
   *   list will be returned.
   *
   * @return JoindinEventComment
   *   A single comment object
   */
  public function getComment($comment_id = NULL) {
    if (is_null($comment_id)) {
      return reset($this->comment_list);
    }
    elseif (array_key_exists($this->comment_list, $comment_id)) {
      return $this->comment_list[$comment_id];
    }
    else {
      return NULL;
    }
  }
}
