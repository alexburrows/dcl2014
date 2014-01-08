<?php

// Plugin definition.
$plugin = array(
  'title' => t('VIMN two row two col'),
  'category' => t('Site Structure'),
  'icon' => 'tworowtwocol.png',
  'theme' => 'vimn_tworow_twocol',
  'regions' => array(
    'content_top' => t('Content top'),
    'content_below' => t('Content below'),
    'content_left' => t('Content left'),
    'content_right' => t('Content right'),
  ),
);
