void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

String HTML="<!DOCTYPE html>
<html>
<body background="https://www.jordanrobins.com.au/wp-content/uploads/2020/10/Summer-Sun-_-Hyams-Beach-V1.3.jpg">

<style> 
#main {
margin-top:50px;
display: flex;
flex-direction: column;
align-items:center;
justify-content:center;
}


#main2 {
display:flex;
flex-direction:row;
align-items:center;
}
#main3 {
display:flex;
flex-direction:row;
align-items:center;
margin-top:25px
}

</style>

<h1 style="text-align: center; margin-top:50px">Sıcaklık</h1>
<div id="main">
<div id="main2">
<img src="https://cdn.mos.cms.futurecdn.net/jqkeHZrc7H2qJGzQkfkgnX.jpg" alt="temperature" style="width:75px; height:75px; border-radius:10%"/>
<p style="color:white; margin-left:10px;">30 derece</p>
</div>


<div id="main3">
<img src="https://clipart-library.com/images/Lcd5ndBri.jpg" alt="temperature" style="width:75px; height:75px;margin-top:10px; border-radius:10%"/>
<p style="color:white; margin-left:10px">%30 nem</p>
</div>
</div>

</body>
</html>
";
