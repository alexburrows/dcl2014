<?php

// Plugin definition.
$plugin = array(
  'title' => t('VIMN two col'),
  'category' => t('Site Structure'),
  'icon' => 'tworowtwocol.png',
  'theme' => 'vimn_twocol',
  'regions' => array(
    'content_left' => t('Content left'),
    'content_right' => t('Content right'),
  ),
);
