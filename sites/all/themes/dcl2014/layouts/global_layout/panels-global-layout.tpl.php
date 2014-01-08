<?php
/**
 * @file
 * Template for a 3 row layout.
 *
 * This template provides a three row panel display layout.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['content']: Content in the main content row.
 *   - $content['bottom']: Content in the bottom row.
 */
?>

<header id="header"><div class="inner">
   <?php print $content['header']; ?>
</div></header>
<div id="bodycontent">
   <?php print $content['content']; ?>
</div>
<footer id="footer" class="inner">
   <?php print $content['footer']; ?>
</footer>