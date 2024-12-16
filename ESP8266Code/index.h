const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<style type="text/css">
   .w{
      width:100%;
      height:auto;
   }
   .i_w{
       height:40px;
       width:90%;
       margin:0 auto;
       border:thin solid #000;
   }
   .c_l{
      width:35%;
      height:auto;
      float:left;
       border:thin solid #000;
   }
   .c_r{
      width:55%;
      height:auto;
      float:right;
       border:thin solid #000;
   }
   #da_i{
     background-color: #ff0000;
   }

</style>
<body>
<div id="json_i">
     <button type="button" onclick="GetJSON('A0', 1, 'resp_i')">LED ON</button>
</div>
<div id="resp_i">
     <button type="button" onclick="GetJSON('A0', 1, 'resp_i')">LED ON</button>
</div>
<div class="w">
   <div class="i_w">
       <div class="c_l">
           Dad's Door
       </div>
       <div class="c_r">
            <div id="da_i" >
               <h1>Test LED Button</h1>
 <button type="button" onclick="SetPin(12, 1, 0);">LED ON</button>
  <button type="button" onclick="SetPin(12, 0, 0);">LED OFF</button><BR>
            </div>
       </div>
   </div>
 <div class="i_w">
       <div class="c_l">
           Dad's Door
       </div>
       <div class="c_r">
            <div id="da_i" >
               
 <button type="button" onclick="SetPin(11, 1, 0);">LED ON</button>
  <button type="button" onclick="SetPin(11, 0, 0);">LED OFF</button><BR>
            </div>
       </div>
   </div>
   <div class="i_w">
       <div class="c_l">
           Dad's Door
       </div>
       <div class="c_r">
            <div id="da_i" >
               
 <button type="button" onclick="SetPin(9, 1, 0);">LED ON</button>
  <button type="button" onclick="SetPin(9, 0, 0);">LED OFF</button><BR>
            </div>
       </div>
   </div>
   <div class="i_w">
       <div class="c_l">
           Dad's Door
       </div>
       <div class="c_r">
            <div id="da_i" >
              
 <button type="button" onclick="SetPin(8, 1, 0);">LED ON</button>
  <button type="button" onclick="SetPin(8, 0, 0);">LED OFF</button><BR>
            </div>
       </div>
   </div>
</div>
<script>
function SetPin(pin, value, ana) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      //document.getElementById("resp_i").innerHTML =
      //this.responseText;
    }
  };
  xhttp.open("GET", "SetPin?PinNumber="+pin+"&HighLow="+value+"&IsAnalog="+ana, true);
  xhttp.send();
}
function GetJSON(pin, ana, divid){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById(divid).innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "GetJSON?PinNumber="+pin+"&IsAnalog="+ana, true);
  xhttp.send(); 
}
</script>
<br>
</body>
</html>
)=====";
