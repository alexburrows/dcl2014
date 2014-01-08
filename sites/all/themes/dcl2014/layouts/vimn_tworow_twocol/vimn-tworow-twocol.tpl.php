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
<section id="top-content">
  <?php print $content['content_top']; ?>
</section>
<section id="below-content">
  <?php print $content['content_below']; ?>
</section>
<section id="bottom-left">
  <?php print $content['content_left']; ?>
</section>
<section id="bottom-right">
  <?php print $content['content_right']; ?>
</section>