<?php

/**
 * @file
 *
 * Factory class to access joind.in API
 */

/**
 * Class JoindinFactory
 *  Default class to fetch JoindIn resources.
 *
 *  JoindIn v2.1 resources:
 *   Event overview:
 *     events
 *     events/123
 *     events/123/talks
 *     events/123/comments/
 *     events/123/comments/456
 *   Talk detail:
 *     talks/789
 *     talks/789/comments
 *     talks/789/comments/012
 *   User information:
 *     users/123
 *     users/123/attended
 *     users/123/talks
 */
class JoindinFactory {
  public static $RESOURCE_RETRIEVER_CLASS = 'JoindinResourceRetrieverHTTP';

  /**
   * Get a list of events.
   *
   * @return JoindinEventCollection
   *   A collection object of JoindIn events.
   */
  public static function listEvents() {
    $resource = self::fetchResource('events');
    return new JoindinEventCollection($resource);
  }

  /**
   * Get a single event.
   *
   * @param Int $event_id
   *   The event identifier provided by JoindIn.
   *
   * @return JoindinEvent
   *   An event object.
   */
  public static function getEvent($event_id) {
    $resource = self::fetchResource("events/{$event_id}");
    $collection = new JoindinEventCollection($resource);
    return $collection[$event_id];
  }

  /**
   * Gets all talks for an event.
   *
   * @param Int $event_id
   *   The event identifier provided by JoindIn.
   *
   * @return JoindinTalkCollection
   *   An collection of JoindinTalk objects.
   */
  public static function getEventTalks($event_id) {
    $resource = self::fetchResource("events/{$event_id}/talks");
    $collection = new JoindinTalkCollection($resource);
    return $collection;
  }

  /**
   * Gets all comments for an event.
   *
   * @param Int $event_id
   *   The event identifier provided by JoindIn.
   *
   * @return JoindinEvent
   *   An event object.
   */
  public static function getEventComments($event_id) {
    $resource = self::fetchResource("events/{$event_id}/comments");
    $collection = new JoindinEventCommentCollection($resource);
    return $collection;
  }

  /**
   * @param $comment_id
   *   The comment identifier
   *
   * @return JoindinEventComment
   *   A comment object
   */
  public static function getEventComment($comment_id) {
    $resource = self::fetchResource("event_comments/{$comment_id}");
    $collection = new JoindinEventCommentCollection($resource);
    return $collection[$comment_id];
  }

  /**
   * Gets all comments for an talk.
   *
   * @param Int $talk_id
   *   The talk identifier provided by JoindIn.
   *
   * @return JoindinTalkCommentCollection
   *   A collection of talk comments.
   */
  public static function getTalkComments($talk_id) {
    $resource = self::fetchResource("talks/{$talk_id}/comments");
    $collection = new JoindinTalkCommentCollection($resource);
    return $collection;
  }

  /**
   * @param $comment_id
   *   The comment identifier
   *
   * @return JoindinTalkComment
   *   A comment object
   */
  public static function getTalkComment($comment_id) {
    $resource = self::fetchResource("talk_comments/{$comment_id}");
    $collection = new JoindinTalkCommentCollection($resource);
    return $collection[$comment_id];
  }

  /**
   * @param $user_id
   *   user's id on joind.in
   *
   * @return JoindinUser
   *   user object
   */
  public static function getUser($user_id) {
    $resource = self::fetchResource("users/{$user_id}");
    $user = new JoindinUser($resource);
    return $user;
  }

  /**
   * Gets all talks given by a specific user
   *
   * @param $user_id
   *   user's id on joind.in
   *
   * @return JoindinTalkCollection
   *   all talks given by the specified user
   */
  public static function getUserTalks($user_id) {
    $resource = self::fetchResource("users/{$user_id}/talks");
    $collection = new JoindinTalkCollection($resource);
    return $collection;
  }

  /**
   * Gets all events attended by a specific user
   *
   * @param $user_id
   *   user's id on joind.in
   *
   * @return JoindinEventCollection
   *   all events attended by the specified user
   */
  public static function getUserAttendedEvents($user_id) {
    $resource = self::fetchResource("users/{$user_id}/attended");
    $collection = new JoindinEventCollection($resource);
    return $collection;
  }

  /**
   * Fetch a resource from JoindIn.
   *
   * @param String $resource
   *   The identifier for a resource, such as 'events', 'events/123', etc.
   *
   * @return String
   *   The resource, encoded as JSON data.
   */
  protected static function fetchResource($resource) {
    $retriever_class = self::$RESOURCE_RETRIEVER_CLASS;
    return $retriever_class::fetchResource($resource);
  }
}
