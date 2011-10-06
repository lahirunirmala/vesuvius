<?php
// print "Configuring error reporting  ...\n";
error_reporting(E_ALL ^ E_NOTICE);
// print "Configuring error display  ...\n";
ini_set("display_errors", "stdout");

// Delete all records for an incident. Requires an incident id.
// 
// set approot since we don't know it yet
$global['approot'] = getcwd() . "/../";
require_once("../conf/sahana.conf");
require_once("../3rd/adodb/adodb.inc.php");
require_once("../inc/handler_db.inc");
require_once("../inc/lib_uuid.inc");
require_once("../inc/lib_image.inc");
require_once("../inc/lib_locale/gettext.inc");

/*
 -----------------------------------------------------------------------------------------------------------------------
*/

if ($argc < 2) {
   die("Wrong number of arguments: Expecting an incident ID.\n");
}
$incident_id = $argv[1];

print "Beginning cleanup at " . strftime("%c") . "\n";
print "Using db " . $global['db']->database . "\n";
$webroot = $global['approot'] . "www/";

print "Prune of $incident_id has begun.\n";

// Delete all records for this incident.
// Get all missing persons (but not their reporters).
$sql = "SELECT pu.p_uuid FROM person_uuid pu WHERE pu.incident_id=$incident_id";
$p_uuids = $global['db']->GetCol($sql);
if($p_uuids === false) {
   $errchk = $global['db']->ErrorMsg();
   die("Error getting records for this incident: ".$errchk);
}

foreach ($p_uuids as $p_uuid) {
   // Delete any associated images.
   $sql = "SELECT url, url_thumb FROM image WHERE p_uuid = '$p_uuid'";
   $image_result = $global['db']->GetRow($sql);
   if($image_result === false) {
      $errchk = $global['db']->ErrorMsg();
      //die("Error getting images for this incident: ".$errchk);
      error_log("Error getting images for this incident: ".$errchk);
   } else if (count($image_result) > 0) {
      // There is an image so delete it and its thumbnail.
      $file = $webroot . $image_result['url'];
      //print "Deleting '" . $file . "'\n";
      if (!unlink($file)) {
         error_log("Unable to delete $file.");
      }
      $thumb = $webroot . $image_result['url_thumb'];
      if ($thumb != $file) {
         //print "Deleting '" . $thumb . "'\n";
         if (!unlink($thumb)) {
            error_log("Unable to delete $thumb.");
         }
      }
   }
   // Delete the person in question and all dependent data (such as reporter) .
   $sql = "CALL delete_reported_person('$p_uuid', 1)";  // delete Notes
   $st = $global['db']->Execute($sql);
   if($st === false) {
      $errchk = $global['db']->ErrorMsg();
      //die("Error calling delete_pfif_person for this incident: ".$errchk);
      error_log("Error calling delete_person for this incident: ".$errchk);
   }
   //print "Deleted '$p_uuid'\n";
}
print count($p_uuids)." persons deleted from incident $incident_id.\n";

print "Cleanup completed at ".strftime("%c")."\n";