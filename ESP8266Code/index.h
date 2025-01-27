const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Simple Webpage</title>
</head>
<body style="background-color: gray;"></body>
    <div style="display: flex; justify-content: center; align-items: center; height: 100vh;">
        <div style="display: grid; grid-template-areas: 
            '. up . . . .'
            'left . right . a b'
            '. down . . . .';
            gap: 10px;">
            <button style="grid-area: up; width: 50px; height: 50px; background-color: black; color: white;" onclick="sendAction('up')">Up</button>
            <button style="grid-area: left; width: 50px; height: 50px; background-color: black; color: white;" onclick="sendAction('left')">Left</button>
            <button style="grid-area: right; width: 50px; height: 50px; background-color: black; color: white;" onclick="sendAction('right')">Right</button>
            <button style="grid-area: down; width: 50px; height: 50px; background-color: black; color: white;" onclick="sendAction('down')">Down</button>
            <button style="grid-area: a; width: 50px; height: 50px; background-color: red; color: white;" onclick="sendAction('a')">A</button>
            <button style="grid-area: b; width: 50px; height: 50px; background-color: blue; color: white;" onclick="sendAction('b')">B</button>
        </div>
    </div>
</body>
    
</body>
<script>
    function sendAction(action) {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "/" + action, true);
        xhttp.send();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                if (this.responseText == "OK") {
                    enableButtons();
                }
            }
        };
        disableButtons();
    }

    function disableButtons() {
        var buttons = document.querySelectorAll('button');
        buttons.forEach(function(button) {
            button.disabled = true;
        });
    }

    function enableButtons() {
        var buttons = document.querySelectorAll('button');
        buttons.forEach(function(button) {
            button.disabled = false;
        });
    }

</script>
</html>
)=====";

