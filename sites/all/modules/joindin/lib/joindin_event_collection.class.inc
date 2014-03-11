<?php

/**
 * @file
 *
 * Collection class for joind.in events
 */

/**
 * Class JoindinEventCollection
 */
class JoindinEventCollection extends JoindinCollection {

  /**
   * Constructor.
   *
   * @param String $json
   *   JSON data from the JoindIn API representing a list of 1 or more events.
   */
  function __construct($event_data) {
    $this->_constructFromJSON($event_data);
  }

  /**
   * Build an event using a JSON data structure.
   *
   * @param String $json
   *   JSON data from the JoindIn API representing a list of 1 or more events.
   */
  public function _constructFromJSON($json) {
    // Decode the JSON.
    $events = drupal_json_decode($json);

    // The API wraps the response for a single event with 2 tiers of array:
    // $events = array('events' => array(0 => array(………), 1 => array(………))).
    if (is_array($events) && isset($events['events'])) {
      foreach ($events['events'] as $event_data) {
        // If an array is passed to the JoindinEvent constructor, the event
        // data is automatically populated from the array properties.
        $event = new JoindinEvent($event_data);

        // Add to our collection, indexed by ID.
        $this[$event->event_id] = $event;
      }
    }
  }

  //
  // /**
  //  * Get the events in this collection.
  //  *
  //  * @return Array
  //  *   An unordered array of JoindinEvent objects.
  //  */
  // public function getEvents() {
  //   return (array) $this;
  // }
  //
 /**
  * Get an event in this collection.
  *
  * @param optional int $event_id
  *   The position in this collection of the desired event. If omitted, the
  *   first resource in the list will be returned.
  *
  * @return JoindinEvent
  *   A single event object
  */
  public function getEvent($event_id = NULL) {
    if (is_null($event_id)) {
      return reset($this);
    }
    elseif (array_key_exists($this, $event_id)) {
      return $this[$event_id];
    }
    else {
      return NULL;
    }
  }
}
