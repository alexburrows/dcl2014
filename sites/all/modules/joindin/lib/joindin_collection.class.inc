<?php

/**
 * @file
 *
 * Contains the base class for collections of joind.in objects
 *
 * Many calls to the API return collections of objects, eg all events on the
 * site, all talks at an event, all comments on a talk/event
 */

/**
 * Iterable base class for Collection objects.
 */
class JoindinCollection implements ArrayAccess, Iterator, Countable {
  // Array of the iterable values.
  protected $collection = array();
  protected $keys = array();
  protected $current_key;

  /**
   * Whether a offset exists
   * @link http://php.net/manual/en/arrayaccess.offsetexists.php
   * @param mixed $offset <p>
   * An offset to check for.
   * </p>
   * @return boolean true on success or false on failure.
   * </p>
   * <p>
   * The return value will be casted to boolean if non-boolean was returned.
   */
  public function offsetExists($offset) {
    return array_key_exists($this->collection, $offset);
  }

  /**
   * Offset to retrieve
   * @link http://php.net/manual/en/arrayaccess.offsetget.php
   * @param mixed $offset <p>
   * The offset to retrieve.
   * </p>
   * @return mixed Can return all value types.
   */
  public function offsetGet($offset) {
    return $this->collection[$offset];
  }

  /**
   * Offset to set
   * @link http://php.net/manual/en/arrayaccess.offsetset.php
   * @param mixed $offset <p>
   * The offset to assign the value to.
   * </p>
   * @param mixed $value <p>
   * The value to set.
   * </p>
   * @return void
   */
  public function offsetSet($offset, $value) {
    $this->collection[$offset] = $value;
  }
  /**
   * Offset to unset
   * @link http://php.net/manual/en/arrayaccess.offsetunset.php
   * @param mixed $offset <p>
   * The offset to unset.
   * </p>
   * @return void
   */
  public function offsetUnset($offset) {
    unset($this->collection[$offset]);
  }
  /**
   * Count elements of an object
   * @link http://php.net/manual/en/countable.count.php
   * @return int The custom count as an integer.
   * </p>
   * <p>
   * The return value is cast to an integer.
   */
  public function count() {
    return count($this->collection);
  }

  /**
   * Return the current element
   * @link http://php.net/manual/en/iterator.current.php
   * @return mixed Can return any type.
   */
  public function current() {
    return $this->collection[$this->current_key];
  }

  /**
   * Return the key of the current element
   * @link http://php.net/manual/en/iterator.key.php
   * @return mixed scalar on success, or null on failure.
   */
  public function key() {
    return $this->current_key;
  }

  /**
   * Move forward to next element
   * @link http://php.net/manual/en/iterator.next.php
   * @return void Any returned value is ignored.
   */
  public function next() {
    $keys = array_keys($this->collection);
    $current_position = array_search($this->current_key, $keys);

    // Only increment the position if the end of the array is not yet reached.
    if ($current_position < count($this->collection) - 1) {
      $next_position = $current_position + 1;
      $next_key = $keys[$next_position];
      $this->current_key = $next_key;
    }
    else {
      $this->current_key = NULL;
    }
  }

  /**
   * Rewind the Iterator to the first element
   * @link http://php.net/manual/en/iterator.rewind.php
   * @return void Any returned value is ignored.
   */
  public function rewind() {
    $keys = array_keys($this->collection);
    $this->current_key = reset($keys);
  }

  /**
   * Checks if current position is valid
   * @link http://php.net/manual/en/iterator.valid.php
   * @return boolean The return value will be casted to boolean and then evaluated.
   * Returns true on success or false on failure.
   */
  public function valid() {
    if (!is_int($this->current_key) && !is_string($this->current_key)) {
      return FALSE;
    }
    return array_key_exists($this->current_key, $this->collection);
  }
}
