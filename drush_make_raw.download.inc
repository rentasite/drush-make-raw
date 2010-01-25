<?php
// $Id$

class DrushMakeDownload_Raw extends DrushMakeDownload {
  function download() {
    $name = $this->project->name;
    $tmp_path = $this->project->tmp_path;
    if (is_array($this->project->download['url'])) {
      drush_op('mkdir', "$tmp_path/$name");
      foreach ($this->project->download['url'] as $original_file => $url) {
        $sanitized_file = preg_replace('/[^0-9a-z\.\_\-]/i','',$original_file);
        if (!is_numeric($original_file) && $sanitized_file == $original_file) {
          $filename = "$tmp_path/$name/" . $original_file;
        } else {
          $filename = "$tmp_path/$name/" . basename($url);
        }
        // Download the project -- try wget, fall back to curl.
        if (drush_get_context('DRUSH_SIMULATE') || drush_shell_exec('wget %s -O %s', $url, $filename) || drush_shell_exec('curl -o %s %s', $filename, $url)) {
          drush_log(dt('%project downloaded from %url.', array('%project' => $name, '%url' => $url)), 'ok');
        }
      }

      return $name;
    }

    return FALSE;
  }
}
