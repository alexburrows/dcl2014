<?php
/**
 * @file
 * Base retriever class to joind.in
 */

/**
 * Class JoindinRetriever
 */
class JoindinRetriever {

  // Provide a default resource retriever.
  protected $resourceRetrieverClass = 'JoindinResourceRetrieverHTTP';

  /**
   * Fetch a resource from JoindIn.
   *
   * @param String $resource
   *   The identifier for a resource, such as 'events', 'events/123', etc.
   *
   * @return String
   *   The resource, encoded as JSON data.
   */
  protected function fetchResource($resource) {
    $retriever_class = $this->resourceRetrieverClass;
    return $retriever_class::fetchResource($resource);
  }

  /**
   * Set the name of the class that will handle retrieving the resource.
   */
  protected function setRetrieverClass($className) {
    // Validate that the resource retriever is appropriate.
    if (!is_a($className, 'JoindinResourceRetrieverInterface')) {
      // Throw.
      throw new Exception('fail');
    }

    $this->resourceRetrieverClass = $className;

    return $this;
  }

  /**
   * Get the name of the class that will handle retrieving the resource.
   */
  protected function getRetrieverClass() {
    return $this->resourceRetrieverClass;
  }

}
