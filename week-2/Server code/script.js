(function() {
    var $on = $('.js-on');
    var $off = $('.js-off');
    
    var domains = {
        'dennis': 'http://iot.dennisvanbennekom.com',
        'tom': 'http://work3gether.com/IoT',
        'tijs': 'http://tijsluitse.com/iot'
    }
    
    $on.on('click', function(e) {
        e.preventDefault();
        
        var name = $(e.target).data('name');
        
        $.ajax({
            type: 'POST',
            url: domains[name] + '/light.php',
            data: { light: 'on' }
        });
    });
    
    $off.on('click', function(e) {
        e.preventDefault();
        
        var name = $(e.target).data('name');
        
        $.ajax({
            type: 'POST',
            url: domains[name] + '/light.php',
            data: { light: 'off' }
        });
    });
    
    setInterval(function() {
        $.ajax({
            type: 'GET',
            url: domains['dennis'] + '/getldr.php',
            success: function(data) {
                $('.js-values.js-dennis').text(data);
            }
        });
        
         $.ajax({
            type: 'GET',
            url: domains['tom'] + '/getldr.php',
            success: function(data) {
                $('.js-values.js-tom').text(data);
            }
        });
        
         $.ajax({
            type: 'GET',
            url: domains['tijs'] + '/getldr.php',
            success: function(data) {
                $('.js-values.js-tijs').text(data);
            }
        });
    }, 1000);
}());