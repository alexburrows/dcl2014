<?php

/**
 * @file
 * Joindin user class
 */

class JoindinUser extends JoindinRetriever {
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
   * Build an user using a JSON data structure.
   *
   * @param String $json
   *   JSON data from the JoindIn API representing the user.
   */
  function _constructFromJSON($json) {
    // Decode the JSON.
    $user = drupal_json_decode($json);

    // The API wraps the response for a single event with 2 tiers of array.
    if (is_array($user) && isset($user['users'])) {
      // Only take the first event, even if there are multiple events.
      $user = reset($user['users']);
    }

    $this->_constructFromArray($user);
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
   * Infer undeclared properties (such as the event ID) from the properties
   * that are provided.
   */
  protected function inferProperties() {
    if (preg_match('#users/([0-9]+)$#', $this->uri, $matches)) {
      $this->user_id = $matches[1];
    }
  }

  /**
   * List the property keys that a user may have, and whether the property is
   * required.
   *
   * @return Array
   *   An array indexed by the property-name, where the value is a boolean:
   *   TRUE if the property is required.
   */
  protected static function validProperties() {
    return array(
      'username' => TRUE,
      'full_name' => FALSE,
      'twitter_username'  => FALSE,
      'uri' => FALSE,
      'verbose_uri' => FALSE,
      'website_uri' => FALSE,
      'talks_uri' => TRUE,
      'attend_events' => FALSE,
    );
  }
}
