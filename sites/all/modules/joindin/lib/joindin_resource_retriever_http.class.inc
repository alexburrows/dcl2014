<?php
/**
 * @file
 * JoindIn resource retrieval class.
 */

/**
 * Class JoindinResourceRetrieverHTTP
 */
class JoindinResourceRetrieverHTTP implements JoindinResourceRetrieverInterface {

  // URL to connect to the JoinIn API.
  public static $JOINDIN_BASE_URL = JOINDIN_BASE_URL_DEFAULT;

  // API version.
  public static $JOINDIN_API_VERSION = JOINDIN_API_VERSION_DEFAULT;

  // User-agent to send in HTTP requests.
  public static $USER_AGENT = 'Drupal JoindIn (+http://drupal.org/project/joindin)';

  /**
   * Connect to the JoindIn REST API web service to retrieve a JoindIn
   * resource.
   *
   * @param String $resource
   *   A resource identifier, such as 'events', 'events/123', 'talks/456', etc,
   *   or a full url to get the resource
   *
   * @return String
   *   The resource, encoded as JSON data.
   */
  public static function fetchResource($resource) {
    // could be a full URI
    if (strncasecmp($resource, 'http://', strlen('http://')) == 0
      || strncasecmp($resource, 'https://', strlen('https://')) == 0) {
      $api_url = $resource;
    }
    else {
      $api_url = self::getURIPrefix() . '/' . $resource;
    }
    $response = self::callAPI($api_url);
    return $response;
  }

  /**
   * Call the web service to retrieve the resource.
   *
   * @param String $uri
   *   The URI where a resource is expected to be available.
   *
   * @return String
   *   The resource, encoded as JSON data.
   */
  protected static function callAPI($uri) {
    // Provide a custom user-agent string in the API request, to identify the
    // module.
    $http_response = drupal_http_request($uri, array(
      'headers' => array(
        'USER-AGENT', self::$USER_AGENT,
      ),
    ));

    // If the HTTP request succeeds, return the HTTP response body.
    if ($http_response->code == 200) {
      return $http_response->data;
    }
    // Log failures.
    else {
      $variables = array(
        '%uri' => $uri,
        '%code' => $http_response->code,
      );
      watchdog('joindin', "Call to joind.in URI %uri failed with return code %code", $variables);
    }
  }

  /**
   * Get the URL prefix for API requests.
   *
   * @return String
   */
  protected static function getURIPrefix() {
    return self::$JOINDIN_BASE_URL . '/' . self::$JOINDIN_API_VERSION;
  }
}
