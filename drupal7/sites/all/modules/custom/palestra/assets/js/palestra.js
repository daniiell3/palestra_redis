(function ($) {
  Drupal.behaviors.palestra = {
    attach: function (context, settings) {
      var qtdRequests     = $(context).find('#qtd-requests');
      var qtdRequestsByIP = $(context).find('#qtd-requests-by-ip');
      var wrapperIpsList  = $(context).find('#ips-list');

      var finishRequest = function(data) {
        qtdRequests.text(data.requests);
        qtdRequestsByIP.text(data.single_request_by_ip);

        var ipsList = $(document).find('.js-ips-list');

        if (ipsList.length > data.ips.length) {
          for (var y = 0; y < ipsList.length; y++) {
            ipsList[y].remove();
          }

          return;
        }

        for (var i = ipsList.length; i < data.ips.length; i++) {
          wrapperIpsList.append('<li class="js-ips-list palestra__items__item">'+data.ips[i]+'</li>');
        }
      }

      var timeout = function() {
        $.ajax({
          url: "/palestra/acessos",
          success: function( data ) {
            finishRequest(data);
          }
        });
      }

      timeout();

      window.setInterval(timeout, 1500);
    }
  };
}(jQuery));