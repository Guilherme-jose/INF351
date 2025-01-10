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
            <button style="grid-area: up; width: 50px; height: 50px; background-color: black; color: white;" onpointerdown="sendAction('up')" onpointerup="sendAction('releaseUp')">Up</button>
            <button style="grid-area: left; width: 50px; height: 50px; background-color: black; color: white;" onpointerdown="sendAction('left')" onpointerup="sendAction('releaseLeft')">Left</button>
            <button style="grid-area: right; width: 50px; height: 50px; background-color: black; color: white;" onpointerdown="sendAction('right')" onpointerup="sendAction('releaseRight')">Right</button>
            <button style="grid-area: down; width: 50px; height: 50px; background-color: black; color: white;" onpointerdown="sendAction('down')" onpointerup="sendAction('releaseDown')">Down</button>
            <button style="grid-area: a; width: 50px; height: 50px; background-color: red; color: white;" onpointerdown="sendAction('a')" onpointerup="sendAction('releaseA')">A</button>
            <button style="grid-area: b; width: 50px; height: 50px; background-color: blue; color: white;" onpointerdown="sendAction('b')" onpointerup="sendAction('releaseB')">B</button>
        </div>
    </div>
</body>
    
</body>
<script>
    function sendAction(action) {
        fetch(`/${action}`);
        console.log(action);
    }
</script>
</html>
)=====";

