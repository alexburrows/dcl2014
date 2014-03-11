<?php

/**
 * @file
 *
 * Joindin Event Comment class
 *
 * Note event and talk comments are different
 */

class JoindinTalkComment extends JoindinRetriever {
  /**
   * Constructor.
   *
   * The argument can be either a JSON array (representing the response from
   * the JoindIn API), or an array (representing the decoded JSON).
   */
  function __construct($data) {
    switch (gettype($data)) {
      case 'string':
        $this->_constructFromJSON($data);
        break;

      case 'array':
        $this->_constructFromArray($data);
        break;

      default:
        // Throw an exception.
    }
    $this->inferProperties();
  }

  /**
   * Build an event comment using a JSON data structure.
   *
   * @param String $json
   *   JSON data from the JoindIn API representing a list of 1 or more comments.
   */
  function _constructFromJSON($json) {
    // Decode the JSON.
    $comments = drupal_json_decode($json);

    // The API wraps the response for a single talk with 2 tiers of array.
    if (is_array($comments) && isset($comments['comments'])) {
      // Only take the first comment, even if there are multiple comments.
      $comment = reset($comment['comments']);
    }

    $this->_constructFromArray($comments);
  }

  /**
   * Build a comment using a decoded JSON array structure.
   *
   * @param String $talk
   *   Decoded JSON data from the JoindIn API representing a single comment.
   */
  protected function _constructFromArray($comment) {
    foreach (self::validProperties() as $property => $isRequired) {
      // Validate required fields.
      if ($isRequired && !array_key_exists($property, $comment)) {
        // Throw exception.
      }
      $this->$property = $comment[$property];
    }
  }

  /**
   * List the property keys that a comment may have, and whether the property is
   * required.
   *
   * @return Array
   *   An array indexed by the property-name, where the value is a boolean:
   *   TRUE if the property is required.
   */
  protected static function validProperties() {
    return array(
      'rating' => FALSE,
      'comment' => TRUE,
      'user_display_name' => FALSE,
      'talk_title' => 'FALSE',
      'created_date' => FALSE,
      'uri' => TRUE,
      'verbose_uri' => FALSE,
      'talk_uri' => TRUE,
      'talk_comments_uri' => TRUE,
      'user_uri' => FALSE,
    );
  }

  /**
   * Infer undeclared properties (such as the event ID) from the properties
   * that are provided.
   */
  protected function inferProperties() {
    if (preg_match('#talk_comments/([0-9]+)$#', $this->uri, $matches)) {
      $this->comment_id = $matches[1];
    }
  }
}
