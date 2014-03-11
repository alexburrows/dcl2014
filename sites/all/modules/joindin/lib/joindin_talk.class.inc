<?php
/**
 * @file
 * Joind.in talk class
 */

/**
 * Class JoindinTalk
 */
class JoindinTalk extends JoindinRetriever {
  // JoindIn v2.1 resources:
  //
  // Talk resources:
  //   talks/789
  //   talks/789/comments
  //   talks/789/comments/012


  // Talk properties:
  // - talk_title
  // - talk_description
  // - slides_link
  // - language
  // - start_date
  // - average_rating
  // - comments_enabled
  // - comment_count
  // - speakers
  // - tracks
  // - uri
  // - verbose_uri
  // - website_uri
  // - comments_uri
  // - verbose_comments_uri
  // - event_uri

  /**
   * Constructor.
   *
   * The argument can be either a JSON array (representing the response from
   * the JoindIn API), or an array (representing the decoded JSON).
   */
  function __construct() {
    $args = func_get_args();
    if (!empty($args)) {
      if (is_string($args[0])) {
        $this->_constructFromJSON($args[0]);
      }
      elseif (is_array($args[0])) {
        $this->_constructFromArray($args[0]);
      }
    }
    $this->inferProperties();
  }


  /**
   * Infer undeclared properties (such as the event ID) from the properties
   * that are provided.
   */
  protected function inferProperties() {
    if (preg_match('#talks/([0-9]+)$#', $this->uri, $matches)) {
      $this->talk_id = $matches[1];
    }
  }

  /**
   * Build an event using a JSON data structure.
   *
   * @param String $json
   *   JSON data from the JoindIn API representing a list of 1 or more events.
   */
  function _constructFromJSON($json) {
    // Decode the JSON.
    $talks = drupal_json_decode($json);

    // The API wraps the response for a single talk with 2 tiers of array.
    if (is_array($talks) && isset($talk['talks'])) {
      // Only take the first event, even if there are multiple events.
      $talk = reset($talks['talks']);
    }

    $this->_constructFromArray($talk);
  }

  /**
   * Build a talk using a decoded JSON array structure.
   *
   * @param String $talk
   *   Decoded JSON data from the JoindIn API representing a single talk.
   */
  protected function _constructFromArray($talk) {
    foreach (self::validProperties() as $property => $isRequired) {
      // Validate required fields.
      if ($isRequired && !array_key_exists($property, $talk)) {
        // Throw exception.
      }
      $this->$property = $talk[$property];
    }
  }

  /**
   * Gets the comments for talk
   *
   * @return JoindinTalkCommentCollection
   *   Collection of all comments for this talk
   */
  public function getComments() {
    $resource = $this->fetchResource($this->comments_uri);
    $collection = new JoindinTalkCommentCollection($resource);
    return $collection;
  }

  /**
   * List the property keys that an event may have, and whether the property is
   * required.
   *
   * @return Array
   *   An array indexed by the property-name, where the value is a boolean:
   *   TRUE if the property is required.
   */
  protected static function validProperties() {
    return array(
      'talk_title' => TRUE,
      'talk_description' => FALSE,
      'slides_link' => FALSE,
      'language' => FALSE,
      'start_date' => FALSE,
      'average_rating' => FALSE,
      'comments_enabled' => FALSE,
      'comment_count' => FALSE,
      'speakers' => FALSE,
      'tracks' => FALSE,
      'uri' => TRUE,
      'verbose_uri' => FALSE,
      'website_uri' => FALSE,
      'comments_uri' => FALSE,
      'verbose_comments_uri' => FALSE,
      'event_uri' => FALSE,
    );
  }
}
