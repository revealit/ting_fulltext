<?php
/**
 * @file
 * Rudimentary parser for a simple subset of docbook.
 */

/**
 * Parse given xml. Return an array holding selected values.
 */
function ting_fulltext_parse($xml) {
  static $xpath;
  $ret = array();
  if (!isset($xpath)) {
    $xpath = ting_fulltext_get_xpath($xml);
  }

  // Main title.
  $query = '//docbook:article/docbook:title';
  $nodelist = $xpath->query($query);
  if ($nodelist->length > 0) {
    (isset($nodelist->item(0)->nodeValue) ? $ret['title'] = $nodelist->item(0)->nodeValue : $ret['title'] = '');
  }

  // Author first name.
  $query = '//docbook:firstname';
  $nodelist = $xpath->query($query);
  if ($nodelist->length > 0) {
    (isset($nodelist->item(0)->nodeValue) ? $ret['firstname'] = $nodelist->item(0)->nodeValue : $ret['firstname'] = '');
  }

  // Author surname.
  $query = '//docbook:surname';
  $nodelist = $xpath->query($query);
  if ($nodelist->length > 0) {
    (isset($nodelist->item(0)->nodeValue) ? $ret['surname'] = $nodelist->item(0)->nodeValue : $ret['surname'] = '');
  }

  // Section (there can be more than one section) and furthermore there can
  // be one or more sections in a section.
  $query = '//docbook:section';
  $nodelist = $xpath->query($query);
  if ($nodelist->length > 0) {
    foreach ($nodelist as $node) {
      $sections[] = ting_fulltext_get_section($node);
    }
    $ret['section'] = $sections;
  }


  // <docbook:subjectset><docbook:subject><docbook:subjectitem>.
  $query = '//docbook:subjectitem';
  $nodelist = $xpath->query($query);
  if ($nodelist->length > 0) {
    foreach ($nodelist as $node) {
      $ret['subject'][] = $node->nodeValue;
    }
  }

  return $ret;
}


/**
 * Get a docbook section?.
 *
 * Not sure whether this is a complete parse of section - there might be more
 * cases. TODO make this parse complete? what? Document me.
 */
function ting_fulltext_get_section($node) {
  foreach ($node->childNodes as $child) {
    switch ($child->nodeName) {
      case 'docbook:title':
        $ret['title'] = $child->nodeValue;
        break;

      // There might be more than one para in each section.
      case 'docbook:para':
        $ret['para'][] = $child->nodeValue;
        break;

      case 'docbook:info':
        $ret['title'] = $child->getElementsByTagName('title')->item(0)->nodeValue;
        break;

      case 'docbook:section':
        // Recursive.
        ting_fulltext_get_section($child);
        break;
    }
  }
  return $ret;
}

/**
 * Prepare XML string for xpath processing.
 */
function ting_fulltext_get_xpath($xml) {
  // TODO errorhandling.
  $dom = new DOMDocument();
  $dom->loadXML($xml);
  $xpath = new DOMXPath($dom);
  $xpath->registerNamespace('docbook', 'http://docbook.org/ns/docbook');
  return $xpath;
}
