(function ($) {
  Drupal.behaviors.quiz = {
    attach: function (context, settings) {
      var self = this;

      $('#edit-submit').click(function(e) {
        e.preventDefault();

        var optionChecked = $('input[name="team_campinas"]:checked').val();

        if (typeof optionChecked == 'undefined') {
          self.messageError();
          return;
        }

        self.voteSubmit(optionChecked);
      });
    },
    voteSubmit: function(vote) {
      var self = Drupal.behaviors.quiz;

      $.post('quiz/vote', {vote: vote}, function(data) {
        self.messageSuccess(data);
      });
    },
    messageError: function() {
      var self = Drupal.behaviors.quiz;

      var markup = '<div class="alert alert-danger js-message-success">';
      markup += 'Selecione <strong>Guarani</strong> ou <strong>Ponte Preta</strong> antes de votar.';
      markup += '</div>';

      $('#palestra_quiz').before(markup);
    },
    messageSuccess: function(data) {
      var self = Drupal.behaviors.quiz,
          vote = 'Guarani';

      switch (data.vote) {
        case 'ponte_preta':
          vote = 'Ponte Preta';
        break;
        case 'red_bull':
          vote = 'Red Bull Brasil';
        break;
      }

      var markup = '<div class="alert alert-success js-message-success">';
      markup += 'Voto <strong>'+ vote +'</strong> computado com sucesso!';
      markup += '</div>';

      $('#palestra_quiz').before(markup);

      self.hideMessage();
    },
    hideMessage: function() {
      var unCheck = function() {
        $('input[name="team_campinas"]:checked').attr('checked', false);
      }

      setTimeout(function() {
        var message = $('.js-message-success');

        message.hide('slow', function() { 
          message.remove(); 
          unCheck();
        });

      }, 1500);
    }
  };
}(jQuery));