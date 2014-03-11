/**
 * @file
 * custom.js
 */
(function ($) {
    Drupal.behaviors.dcl2014 = {
        attach: function (context) {
            $('.cta').click(function() {
                window.location = jQuery(this).find(" a:first").attr("href");
            });
        }
    };
})(jQuery);
