
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
   
    
<style>

body{
    text-align: center;
}
.container {
  margin-top: 40px;
  padding-top: 20px;
  /*background-color: #beb*/
}
.vertical {
  display: inline-block;
  width: 40%;
  height: 400PX;
  -webkit-transform: rotate(-90deg); /* Chrome, Safari, Opera */
  transform: rotate(-90deg);
}
.vertical {
  box-shadow: inset 0px 4px 6px #ccc;
}
.progress-bar {
  box-shadow: inset 0px 4px 6px rgba(100,100,100,0.6);
}

</style>


</head>
<body>
    <h1>
        Iot end term Project
    </h1>
<h4>Water Pump Status:<span id="motorStatus">on</span></h4>
<div class="p-5">
<p>Motor control</p>
<button id="on" >On</button>
<button id="off">Off</button>
</div>  

<div class="container">
    <div class="progress vertical">
      <div class="progress-bar progress-bar-info" id="vol" role="progressbar" aria-valuenow="90" aria-valuemin="0" aria-valuemax="100" style="width: 45%;height: 100%;" >
      
      </div>  
    
    </div>  
    </div>

<script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
  <script>
   
    
    window.addEventListener('load',getData() );
    setInterval(getData,500);
   
  

    function getVolume(){
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange=function (){
        if(this.readyState == 4 && this.status == 200){
        var data = this.responseText
        console.log("volume:"+data);
        const vol = document.getElementById("vol");
        var voldata=data*100+"%";
        vol.style.setProperty("width",voldata);
        }
      }
      xhr.open(200,"/volume",true);
      xhr.send();

    }

    function getMotorStatus(){

      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange=function (){
        if(this.readyState == 4 && this.status == 200){
        var data = this.responseText
        console.log("motorStatus:"+data);
        const motorStatus=document.getElementById("motorStatus");
        if(data==0){
            motorStatus.innerText="OFF"

        }
        else{
          motorStatus.innerText="ON"
        }
      }
      }
      xhr.open(200,"/motorstatus",true);
      xhr.send();

    }


    function getData(){
      getMotorStatus();
      getVolume();
    }

    const onBtn = document.getElementById("on");
    console.log(onBtn);
    const OffBtn=document.getElementById("off");

    onBtn.addEventListener("click", e =>{
      var xhr =new XMLHttpRequest();
      xhr.open("GET","/update?outputPin=12&state=1",true);
      xhr.send();
      // console.log("on clicked")
    });
    OffBtn.addEventListener("click",e=>{
      var xhr = new XMLHttpRequest();
      xhr.open("GET","/update?outputPin=12&state=0",true);
      xhr.send();
      // console.log("off clicked")
    });

  </script>

</body>
</html>
)rawliteral";