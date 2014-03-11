<?php
/**
 * @file
 *
 * Collection class for talk objects
 */


/**
 * Class JoindinTalkCollection
 */
class JoindinTalkCollection extends JoindinCollection {

  /**
   * Constructor.
   *
   * @param String $json
   *   JSON data from the JoindIn API representing a list of 1 or more events.
   */
  function __construct($talk_data) {
    $this->_constructFromJSON($talk_data);
  }

  /**
   * Build an event using a JSON data structure.
   *
   * @param String $json
   *   JSON data from the JoindIn API representing a list of 1 or more events.
   */
  public function _constructFromJSON($json) {
    // Decode the JSON.
    $talks = drupal_json_decode($json);

    // The API wraps the response for a single talk with 2 tiers of array:
    // $events = array('talks' => array(0 => array(………), 1 => array(………))).
    if (is_array($talks) && isset($talks['talks'])) {
      foreach ($talks['talks'] as $talk_data) {
        // If an array is passed to the JoindinTalk constructor, the
        // data is automatically populated from the array properties.
        $talk = new JoindinTalk($talk_data);
        // Index by talk ID.
        $this->collection[$talk->talk_id] = $talk;
      }
    }
  }

  /**
   * Get the events in this collection.
   *
   * @return Array
   *   An unordered array of JoindinEvent objects.
   */
  public function getTalks() {
    return $this->collection;
  }

  /**
   * Get a talk in this collection.
   *
   * @param optional int $talk_id
   *   The talk_id of the desired talk. If omitted, the first resource in the
   *   list will be returned.
   *
   * @return JoindinTalk
   *   A single talk object
   */
  public function getTalk($talk_id = NULL) {
    if (is_null($talk_id)) {
      return reset($this->collection);
    }
    elseif (array_key_exists($this->talk_list, $talk_id)) {
      return $this->collection[$talk_id];
    }
    else {
      return NULL;
    }
  }
}
