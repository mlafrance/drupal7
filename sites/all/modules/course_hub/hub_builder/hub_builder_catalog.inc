<?php

/**
 * @file
 * Access to catalogs
 */

/**
 * Answer an array of all of the catalogs
 *
 * @return array of HubBuilder_Catalog objects
 */
function hub_builder_get_catalogs() {
  $sql = "
    SELECT c.*
    FROM {hub_builder_catalog} c
    ORDER BY c.id ASC";
  $result = db_query($sql);
  $catalogs = array();
  while ($data = db_fetch_array($result))
    $catalogs[] = new HubBuilder_Catalog($data, TRUE);
  return $catalogs;
}

/**
 * Answer a catalog object
 *
 * @return HubBuilder_Catalog
 */
function hub_builder_get_catalog($id) {
  $sql = "
    SELECT c.*
    FROM {hub_builder_catalog} c
    WHERE c.id = '%s'";
  $result = db_query($sql, $id);
  $data = db_fetch_array($result);
  if (empty($data))
    return NULL;
  else
    return new HubBuilder_Catalog($data, TRUE);
}

class HubBuilder_Catalog {
  private $data = array();
  private $exists = FALSE;
  private $dbId = NULL;
  private $changed = FALSE;

  public function __construct(array $data = array(), $exists = FALSE) {
    if (!is_array($data['types_to_import'])) {
      $data['types_to_import'] = json_decode($data['types_to_import']);
    }
    if (!is_array($data['types_to_import'])) {
      $data['types_to_import'] = array();
    }
    $this->data = $data;
    if ($exists) {
      $this->exists = TRUE;
      $this->dbId = $data['id'];
    }
  }

  public function getNumTerms() {
    $sql = "SELECT COUNT(*) FROM {hub_builder_term} WHERE catalog_id = '%s'";
    $result = db_query($sql, $this->dbId);
    return intval(db_result($result));
  }

  public function save() {
    if (!$this->changed)
      return;

    if ($this->exists) {
      $sql = "
      UPDATE {hub_builder_catalog}
      SET id = '%s', class_group_base_dn = '%s',  main_data_url = '%s',  instructor_course_list_url = '%s', types_to_import = '%s'
      WHERE id = '%s'";
      if (db_query($sql, $this->id, $this->class_group_base_dn, $this->main_data_url, $this->instructor_course_list_url, json_encode($this->types_to_import), $this->dbId)) {
        $this->dbId = $this->id;
      }
      else {
        throw new Exception('Update failed.');
      }
    }
    else {
      $sql = "
      INSERT INTO {hub_builder_catalog}
      (id, class_group_base_dn, main_data_url, instructor_course_list_url, types_to_import)
      VALUES ('%s', '%s', '%s', '%s', '%s')";
      if (db_query($sql, $this->id, $this->class_group_base_dn, $this->main_data_url, $this->instructor_course_list_url, json_encode($this->types_to_import))) {
        $this->dbId = $this->id;
        $this->exists = TRUE;
      }
      else {
        throw new Exception('Insert failed.');
      }
    }
  }

  public function delete() {
    $sql = "
      DELETE FROM {hub_builder_catalog}
      WHERE id = '%s'";
    if (db_query($sql, $this->dbId)) {
      $this->dbId = NULL;
      $this->exists = FALSE;
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
      return NULL;
    }
  }

  public function __set($name, $value) {
    static $allowed = array('id', 'class_group_base_dn', 'main_data_url', 'instructor_course_list_url', 'types_to_import');
    if (!in_array($name, $allowed))
      throw new InvalidArgumentException(t("%name is not in the allowed list: @allowed", array("%name" => $name, "@allowed" => implode(", ", $allowed))));
    if ($name == 'types_to_import' && !is_array($value))
      throw new InvalidArgumentException(t("%name must be an array.", array("%name" => $name)));

    if (empty($this->data[$name]) || $this->data[$name] != $value)
      $this->changed = TRUE;

    $this->data[$name] = $value;
  }

  public function __isset($name) {
    return isset($this->data[$name]);
  }

  public function __unset($name) {
    unset($this->data[$name]);
  }
}