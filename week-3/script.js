(function() {
    var $on = $('.js-on');
    var $off = $('.js-off');
    var date;
    var count = {};
    var detectorState = document.querySelector('.detector-state');
    var stateEl = document.querySelector('.state-value');
    var buttons = document.querySelectorAll('.button');
    
    checkState();
    
    $on.on('click', function(e) {
        e.preventDefault();
        console.log('on is pressed');
        
        
        
        $.ajax({
            type: 'POST',
            url: 'http://tomsnepvangers.com/IoT/switch.php',
            data: { switch: 'on' }
        });

         $.when( $.ajax( "http://tomsnepvangers.com/IoT/switch.php" ) ).done(function( x ) {
        
            checkState();
        });

    });
    
    $off.on('click', function(e) {
        e.preventDefault();
        console.log('off is pressed');
        
        
        $.ajax({
            type: 'POST',
            url: 'http://tomsnepvangers.com/IoT/switch.php',
            data: {  switch: 'off' }
        });

        $.when( $.ajax( "http://tomsnepvangers.com/IoT/switch.php" ) ).done(function( x ) {
        
            checkState();
        });

    });

     $.ajax({
             url:'motion.txt',
             success: function (data) {
               var data = data;
             }
            });

    function checkState() {
        console.log('checkstate fired');
        $.ajax({
            url: 'switch.json',
            success: function(data) {
                console.log(data.switch);

                if(data.switch == "on"){
                    console.log('detector staat aan');
                    stateEl.innerHTML = "aan";

                } else if (data.switch == "off") {
                    console.log('detector staat uit');
                    stateEl.innerHTML = "uit";
                } else {
                    console.log('er is iets mis met de detector');
                    detectorState.innerHTML = "Er is iets mis met de reiger detector";
                }
            }
        });
    };

    $.ajax({
     url:'motion.txt',
     success: function (data) {

        date = data.toString().split("\n");

        date.pop();

        date.forEach(function(i) { count[i] = (count[i]|| 0)+1;  });
            
     }
    });

    $.when( $.ajax( "motion.txt" ) ).done(function( x ) {
        renderHistory();
    });

    function renderHistory() {
        var keys = Object.keys(count);
        var section = document.getElementById('history');

        for (var i = 0; i < keys.length; i++) {
            var key = keys[i];
            var val = count[keys[i]];
            console.log(key);
            console.log(val);

            var elDiv = document.createElement('div');

            var calendar = document.createElement('img');
            var heron = document.createElement('img');

            calendar.setAttribute('src', 'calendar.png');
            heron.setAttribute('src', 'reiger.png');

            var elDate = document.createElement('p');
            var elValue = document.createElement('p');

            var date = document.createTextNode(key);
            var value = document.createTextNode(val);

            elDate.appendChild(date);
            elValue.appendChild(value);

            elDiv.appendChild(calendar);
            elDiv.appendChild(elDate);
            elDiv.appendChild(heron);
            elDiv.appendChild(elValue);

            section.appendChild(elDiv);
        }
    }
}())