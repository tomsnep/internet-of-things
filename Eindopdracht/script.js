(function() {
    var $on = $('.js-on');
    var $off = $('.js-off');
    
    var domain = 'http://www.work3gether.com/IoT'
    
    
    $on.on('click', function(e) {
        e.preventDefault();
        
        var name = $(e.target).data('name');
        console.log('on clicked');
        $.ajax({
            type: 'POST',
            url: 'http://www.work3gether.com/IoT/trigger.php',
            data: { trigger: 'on' }
        });
    });
    
    $off.on('click', function(e) {
        e.preventDefault();
        
        var name = $(e.target).data('name');
        console.log('off clicked');
        $.ajax({
            type: 'POST',
            url: 'http://www.work3gether.com/IoT/trigger.php',
            data: { trigger: 'off' }
        });
    });
    
    // setInterval(function() {
    //     $.ajax({
    //         type: 'GET',
    //         url: domains['dennis'] + '/getldr.php',
    //         success: function(data) {
    //             $('.js-values.js-dennis').text(data);
    //         }
    //     });
        
    //      $.ajax({
    //         type: 'GET',
    //         url: domains['tom'] + '/getldr.php',
    //         success: function(data) {
    //             $('.js-values.js-tom').text(data);
    //         }
    //     });
        
    //      $.ajax({
    //         type: 'GET',
    //         url: domains['tijs'] + '/getldr.php',
    //         success: function(data) {
    //             $('.js-values.js-tijs').text(data);
    //         }
    //     });
    // }, 1000);
}());