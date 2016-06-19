(function ($) {
  Drupal.behaviors.quizResult = {
    attach: function () {
      var self = this;
      this.ponte = $('.js-result-ponte');
      this.guarani = $('.js-result-guarani');
      this.red = $('.js-result-red');

      var timeout = function() {
        $.ajax({
          url: "/quiz/result",
          success: function(data) {
            self.finishRequest(data);
          }
        });
      }

      timeout();

      window.setInterval(timeout, 1500);
    },
    finishRequest: function(data) {
      var self = Drupal.behaviors.quizResult,
          total = data.total;

      if (data.ponte != 0) {
        self.ponte.css('width', self.getProgress(total, data.ponte));
      }

      if (data.guarani != 0) {
        self.guarani.css('width', self.getProgress(total, data.guarani));
      }

      if (data.red != 0) {
        self.red.css('width', self.getProgress(total, data.red));
      }
    },
    getProgress: function(total, data) {
      return (100 * data) / total;
    }
  };
}(jQuery));