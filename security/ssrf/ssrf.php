<?php
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $_GET['url']);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  $html = curl_exec($ch);
  echo $html;
