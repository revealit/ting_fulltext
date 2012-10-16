<?php
/**
 * @file
 * Template to render full text object.
 */
?>
<div class="ting_fulltext_wrap">

  <h3>
    <?php if (isset($element['title'])):
      echo $element['title'];
    endif; ?>
  </h3>

  <div class="ting_fulltext_name">
  <?php if (!empty($element['firstname'])):
    echo '<b>Forfatter:</b>';
    echo $element['firstname'] . '&nbsp;' . $element['surname'];
  endif; ?>
  </div>

  <?php if (isset($element['subject'])):
    echo '<div class="ting_fulltext_subject">' . t('subject:') . '</div>';
    foreach ($element['subject'] as $key => $subject):
      echo '<div class="ting_fulltext_subjectitem">' . $subject . '</div>';
    endforeach;
    echo '</div>';
  endif; ?>


  <?php
  if (isset($element['section'])):
    foreach ($element['section'] as $key => $section):
      if (isset($section['title'])):
        echo '<h4>' . $section['title'] . '</h4>';
      endif;
      if (isset($section['para'])):
        foreach($section['para'] as $para):
          echo '<p class="ting_fulltext_para">' . $para . '</p>';
        endforeach;
      endif;
    endforeach;
  endif;
  ?>
</div>
