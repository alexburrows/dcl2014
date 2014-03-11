<?php

/**
 * @file
 *
 * Definition of the JoindinEvent class
 */

/**
 * Class JoindinEvent
 *
 *  JoindIn v2.1 resources:
 *  Event overview:
 *    events
 *    events/123
 *    events/123/talks
 *    events/123/comments/
 *    events/123/comments/456
 *
 *  Event properties:
 *  - name
 *  - start_date
 *  - end_date
 *  - description
 *  - href
 *  - attendee_count
 *  - attending
 *  - events_comment_count
 *  - icon
 *  - tags
 *  - uri
 *  - verbose_url
 *  - comments_url
 *  - talks_url
 *  - website_url
 *  - humane_website_url
 */
class JoindinEvent extends JoindinRetriever {

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
   * List talks for this event.
   */
  public function getTalks() {
    $resource = $this->fetchResource($this->talks_uri);
    $collection = new JoindinTalkCollection($resource);
    return $collection;
  }

  /**
   * Gets the talk from joind.in
   *
   * @param $talk_id
   * @return JoindinTalk talk object requested, or NULL
   */
  public function getTalk($talk_id) {
    $resource = $this->fetchResource("events/{$this->event_id}/talks/{$talk_id}");
    $collection = new JoindinTalkCollection($resource);
    return $collection->getTalk();
  }

  /**
   * Gets the comments for event
   *
   * @return JoindinEventCommentCollection
   *   Collection of all comments for this event
   */
  public function getComments() {
    $resource = $this->fetchResource($this->comments_uri);
    $collection = new JoindinEventCommentCollection($resource);
    return $collection;
  }

  /**
   * Infer undeclared properties (such as the event ID) from the properties
   * that are provided.
   */
  protected function inferProperties() {
    if (preg_match('#events/([0-9]+)$#', $this->uri, $matches)) {
      $this->event_id = $matches[1];
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
    $event = drupal_json_decode($json);

    // The API wraps the response for a single event with 2 tiers of array.
    if (is_array($event) && isset($event['events'])) {
      // Only take the first event, even if there are multiple events.
      $event = reset($event['events']);
    }

    $this->_constructFromArray($event);
  }

  /**
   * Build an event using a decoded JSON array structure.
   *
   * @param String $event
   *   Decoded JSON data from the JoindIn API representing a single event.
   */
  protected function _constructFromArray($event) {
    foreach (self::validProperties() as $property => $isRequired) {
      // Validate required fields.
      if ($isRequired && !array_key_exists($property, $event)) {
        // Throw exception.
      }
      $this->$property = $event[$property];
    }
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
      'name' => TRUE,
      'start_date' => TRUE,
      'end_date'  => FALSE,
      'description' => FALSE,
      'href' => FALSE,
      'attendee_count' => FALSE,
      'attending' => FALSE,
      'event_comments_count' => FALSE,
      'icon' => FALSE,
      'tags' => FALSE,
      'uri' => FALSE,
      'verbose_uri' => FALSE,
      'comments_uri' => TRUE,
      'talks_uri' => TRUE,
      'website_uri' => TRUE,
      'humane_website_uri' => FALSE,
    );
  }
}
