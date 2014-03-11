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
<footer id="footer">
  <div class="inner">
  <div id="footer-left">
    <p>Copyright © 2014 Drupalcamp London</p>
    <p>Drupal is a&nbsp;<a href="http://drupal.com/trademark" target="_blank">registered trademark</a>&nbsp;of&nbsp;<a href="http://buytaert.net/" style="color: rgb(1, 204, 255); text-decoration: none;" target="_blank">Dries Buytaert</a>.<br />
    Built using <a href="http://drupal.org/project/cod">COD</a> on Drupal - <a href="/credits">Credits</a></p>

  </div>
  <div id="footer-right"><a id="hosting" href="http://www.aberdeencloud.com">Hosting by Aberdeen Cloud</a></div>
  </div>
  <div style="clear:both;"></div>
</footer>
