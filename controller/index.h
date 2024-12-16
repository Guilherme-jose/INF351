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
            <button style="grid-area: up; width: 50px; height: 50px; background-color: black; color: white;" onmousedown="Up()" onmouseup="ReleaseUp()">Up</button>
            <button style="grid-area: left; width: 50px; height: 50px; background-color: black; color: white;" onmousedown="Left()" onmouseup="ReleaseLeft()">Left</button>
            <button style="grid-area: right; width: 50px; height: 50px; background-color: black; color: white;" onmousedown="Right()" onmouseup="ReleaseRight()">Right</button>
            <button style="grid-area: down; width: 50px; height: 50px; background-color: black; color: white;" onmousedown="Down()" onmouseup="ReleaseDown()">Down</button>
            <button style="grid-area: a; width: 50px; height: 50px; background-color: red; color: white;" onmousedown="A()" onmouseup="ReleaseA()">A</button>
            <button style="grid-area: b; width: 50px; height: 50px; background-color: blue; color: white;" onmousedown="B()" onmouseup="ReleaseB()">B</button>
        </div>
    </div>
</body>
    
</body>
<script>
    function Up() {
        console.log("Up button pressed");
    }

    function ReleaseUp() {
        console.log("Up button released");
    }

    function Left() {
        console.log("Left button pressed");
    }

    function ReleaseLeft() {
        console.log("Left button released");
    }

    function Right() {
        console.log("Right button pressed");
    }

    function ReleaseRight() {
        console.log("Right button released");
    }

    function Down() {
        console.log("Down button pressed");
    }

    function ReleaseDown() {
        console.log("Down button released");
    }
</script>
</html>
)=====";