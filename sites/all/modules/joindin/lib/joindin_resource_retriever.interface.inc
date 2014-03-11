<?php
/**
 * @file
 * JoindIn resource retrieval interface specification.
 */

/**
 * Class JoindinResourceRetrieverInterface
 */
interface JoindinResourceRetrieverInterface {

  /**
   * Retrieve a JoindIn resource.
   *
   * @param String $resource
   *   A resource identifier, such as 'events', 'events/123', 'talks/456', etc.
   *
   * @return String
   *   The resource, encoded as JSON data.
   */
  public static function fetchResource($resource);
}
