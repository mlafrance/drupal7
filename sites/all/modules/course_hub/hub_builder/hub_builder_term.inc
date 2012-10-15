<?php

/**
 * @file
 * Access to terms
 */

/**
 * Answer an array of all of the terms
 *
 * @return array of HubBuilder_Term objects
 */
function hub_builder_get_terms() {
  $sql = "
    SELECT t.*, u.name AS last_built_by_name
    FROM {hub_builder_term} t
      LEFT JOIN {users} u ON t.last_built_by = u.uid
    ORDER BY t.id DESC";
  $result = db_query($sql);
  $terms = array();
  while ($data = db_fetch_array($result))
    $terms[] = new HubBuilder_Term($data, true);
  return $terms;
}

/**
 * Answer a term object
 *
 * @return HubBuilder_Term
 */
function hub_builder_get_term($id) {
  $sql = "
    SELECT t.*, u.name AS last_built_by_name
    FROM {hub_builder_term} t
      LEFT JOIN {users} u ON t.last_built_by = u.uid
    WHERE t.id = '%s'";
  $result = db_query($sql, $id);
  $data = db_fetch_array($result);
  if (empty($data))
    return null;
  else
    return new HubBuilder_Term($data, true);
}

class HubBuilder_Term {
  private $data = array();
  private $exists = false;
  private $dbId = null;
  private $changed = false;
  private $catalog;

  public function __construct(array $data = array(), $exists = false) {
    $this->data = $data;
    if ($exists) {
      $this->exists = true;
      $this->dbId = $data['id'];
    }
  }

  public function getCatalog() {
    if (empty($this->catalog))
      $this->catalog = hub_builder_get_catalog($this->catalog_id);
    return $this->catalog;
  }

  public function getMainCourseDataUrl() {
    $catalog = $this->getCatalog();
    $url = $catalog->main_data_url;
    $url = str_replace('[CATALOG_ID]', rawurlencode($catalog->id), $url);
    $url = str_replace('[TERM_ID]', rawurlencode($this->id), $url);
    return $url;
  }

  public function getInstructorCourseListUrl($instructor_id) {
    $catalog = $this->getCatalog();
    $url = $catalog->instructor_course_list_url;
    $url = str_replace('[CATALOG_ID]', rawurlencode($catalog->id), $url);
    $url = str_replace('[TERM_ID]', rawurlencode($this->id), $url);
    $url = str_replace('[INSTRUCTOR_ID]', rawurlencode($instructor_id), $url);
    return $url;
  }

  public function markBuilt() {
    if (!$this->exists)
      throw new Exception('The term must be saved before it can be marked as built');

    global $user;
    $sql = "
      UPDATE {hub_builder_term}
      SET last_built = NOW(), last_built_by = %d
      WHERE id = '%s'";
    if (db_query($sql, $user->uid, $this->dbId)) {
      $this->data['last_built'] = date('Y-m-d H:i:s');
      $this->data['last_built_by'] = $user->uid;
      $this->data['last_built_by_name'] = $user->name;
    }
    else {
      throw new Exception('Update failed.');
    }
  }

  public function save() {
    if (!$this->changed)
      return;

    if ($this->exists) {
      $sql = "
      UPDATE {hub_builder_term}
      SET catalog_id = '%s', id = '%s', display_name = '%s',  import_path = '%s'
      WHERE id = '%s'";
      if (db_query($sql, $this->catalog_id, $this->id, $this->display_name, $this->import_path, $this->dbId)) {
        $this->dbId = $this->id;
      }
      else {
        throw new Exception('Update failed.');
      }
    }
    else {
      $sql = "
      INSERT INTO {hub_builder_term}
      (catalog_id, id, display_name, import_path)
      VALUES ('%s', '%s', '%s', '%s')";
      if (db_query($sql, $this->catalog_id, $this->id, $this->display_name, $this->import_path)) {
        $this->dbId = $this->id;
        $this->exists = true;
      }
      else {
        throw new Exception('Insert failed.');
      }
    }
  }

  public function delete() {
    $sql = "
      DELETE FROM {hub_builder_term}
      WHERE id = '%s'";
    if (db_query($sql, $this->dbId)) {
      $this->dbId = null;
      $this->exists = false;
    }
    else {
      throw new Exception("Delete failed.");
    }
  }

  public function __get($name) {
    if (array_key_exists($name, $this->data)) {
      return $this->data[$name];
    }
    else {
      return null;
    }
  }

  public function __set($name, $value) {
    static $allowed = array('catalog_id', 'id', 'display_name', 'import_path');
    if (!in_array($name, $allowed))
      throw new InvalidArgumentException(t("%name is not in the allowed list: @allowed", array("%name" => $name, "@allowed" => implode(", ", $allowed))));

    if (empty($this->data[$name]) || $this->data[$name] != $value)
      $this->changed = true;

    $this->data[$name] = $value;
  }

  public function __isset($name) {
    return isset($this->data[$name]);
  }

  public function __unset($name) {
    unset($this->data[$name]);
  }
}