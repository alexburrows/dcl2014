<?php
/**
 * @file
 * Template for a 2 row 2 col layout
 *
 * This template provides a three row panel display layout.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top_content']: Content in the top row.
 *   - $content['below_content']: Content in the main content row.
 *   - $content['bottom_left']: Content in the bottom row.
 *   - $content['bottom_right']: Content in the bottom row.
 */
?>
<section id="main-content">
  <?php print $content['content_left']; ?>
</section>
<aside id="sidebar-right">
  <?php print $content['content_right']; ?>
</aside>