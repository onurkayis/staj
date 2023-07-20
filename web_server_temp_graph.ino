#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ChargeTek";
const char* password = "password";

WebServer server(80);

const int pin34 = 34; //analog ADC1_CH6

void initWiFi(){
  
  Serial.print("İnternete bağlanılıyor");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Bağlantı başarısız oldu!");
  }else{
    Serial.print("\n");
    Serial.println("İnternete bağlanıldı!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }

}

int adcValue;  
float temperature;
float resistance;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  initWiFi();

  server.on("/",handle_root);
  server.on("/readTempC",readTempC);
  server.begin();
  Serial.println("HTTP server started!");

}

String tempC;

void readTempC(){

  adcValue = analogRead(pin34);

  double voltage = (float)adcValue / 4095.0 * 3.3;                // calculate voltage
  double Rt = 10 * voltage / (3.3 - voltage);                     //calculate resistance value of thermistor
  double tempK = 1 / (1 / (273.15 + 25) + log(Rt / 10) / 3950.0); //calculate temperature (Kelvin)
  tempC = (tempK - 273.15);                                  //calculate temperature (Celsius)
  Serial.printf("ADC value : %d,\tVoltage : %.2fV, \tTemperature : %sC\n", adcValue, voltage, tempC);
  server.send(200,"text/plane",tempC);
  delay(750);
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();


  // resistance = REFERENCE_RESISTANCE /  (STM32_ANALOG_RESOLUTION /  adcValue - 1);
	// TempKelvin = log(resistance / NOMINAL_RESISTANCE);
  
	// /*
	// https://www.allaboutcircuits.com/industry-articles/how-to-obtain-the-temperature-value-from-a-thermistor-measurement/  
	// https://mehmettopuz.net/stm32-ve-ntc-sensoru-ile-sicaklik-olcme/.html
	// */
	// TempKelvin /= B_VALUE;
	// TempKelvin += (1 / NOMINAL_TEMPERATURE);
	// TempKelvin = 1 / TempKelvin;
	// temperature = TempKelvin - 273.15;



  // Serial.print("ADC Value: ");
  // Serial.print(adcValue);
  // Serial.print(" - ");
  // Serial.print("Resistance: ");
  // Serial.print(resistance);
  // Serial.print(" - ");
  // Serial.print("Temperature: ");
  // Serial.println(temperature);
  delay(1000);

}


void handle_root(){
  String HTML="<!DOCTYPE html>\n"
  "<html>\n"
  "<head>\n"
  "\t<meta charset='utf-8'>\n"
  "\t<title>Sıcaklık Grafiği</title>\n"
  "    <link href='https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-KyZXEAg3QhqLMpG8r+8fhAXLRk2vvoC2f3B09zVXn8CA5QIVfZOJ3BCsw2P0p/We' crossorigin='anonymous'>\n"
  "  </head>\n"
  "<style type=\"text/css\">\n"
  ".button {\n"
  "  background-color: #4CAF50; /* Green */\n"
  "  border: none;\n"
  "  color: white;\n"
  "  padding: 15px 32px;\n"
  "  text-align: center;\n"
  "  text-decoration: none;\n"
  "  display: inline-block;\n"
  "  font-size: 16px;\n"
  "}\n"
  "</style>\n"
  "<body style=\"background-color: #75C2F6 \">\n"
  "\n"
  "<center>\n"
  "<h3 style=\"margin-top:30px;\">\n"
  "  ESP32 WEB SERVER\n"
  "</h3>\n"
  "<h5>Sıcaklık Grafiği</h5>\n"
  "    <div id='wrapper'>\n"
  "      <div id='content-wrapper' class='d-flex flex-column'>\n"
  "        <div id='content'>\n"
  "          \n"
  "          <div class='container-fluid' id='container-wrapper'>\n"
  "            <div class='d-sm-flex align-items-center justify-content-between mb-4'></div>\n"
  "            <div class='row'>\n"
  "              <div class='col-lg-12'>\n"
  "                <div class='card mb-4'>\n"
  "                  <div class='card-header py-3 d-flex flex-row align-items-center justify-content-between'>\n"
  "                    <h6 style=\"color:black; font-weight:bold;\" >Son 10 dakikalık sıcaklık verisi</h6>\n"
  "                  </div>\n"
  "                  <div class='card-body'>\n"
  "                    <div class='chart-area'>\n"
  "                      <canvas id='myAreaChart'></canvas>\n"
  "                    </div>\n"
  "                    <hr>\n"
  "                  </div>\n"
  "                </div>\n"
  "              </div>\n"
  "            </div>\n"
  "          </div>\n"
  "        </div>\n"
  "      </div>\n"
  "    </div>\n"
  "    <p>\n"
  "  <b>Anlık Sıcaklık Değeri(°C):</b> <b style=\"color:white\" id=\"adc_val\">0</b> &nbsp;&nbsp;&nbsp;\n"
  "</p>\n"
  "<script src='https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.4.0/Chart.min.js'></script>\n"
  "    <script>\n"
  "      function number_format(number, decimals, dec_point, thousands_sep) {\n"
  "        number = (number + '').replace(',', '').replace(' ', '');\n"
  "        var n = !isFinite(+number) ? 0 : +number,\n"
  "          prec = !isFinite(+decimals) ? 0 : Math.abs(decimals),\n"
  "          sep = (typeof thousands_sep === 'undefined') ? ',' : thousands_sep,\n"
  "          dec = (typeof dec_point === 'undefined') ? '.' : dec_point,\n"
  "          s = '',\n"
  "          toFixedFix = function(n, prec) {\n"
  "            var k = Math.pow(10, prec);\n"
  "            return '' + Math.round(n * k) / k;\n"
  "          };\n"
  "        s = (prec ? toFixedFix(n, prec) : '' + Math.round(n)).split('.');\n"
  "        if (s[0].length > 3) {\n"
  "          s[0] = s[0].replace(/\\B(?=(?:\\d{3})+(?!\\d))/g, sep);\n"
  "        }\n"
  "        if ((s[1] || '').length < prec) {\n"
  "          s[1] = s[1] || '';\n"
  "          s[1] += new Array(prec - s[1].length + 1).join('0');\n"
  "        }\n"
  "        return s.join(dec);\n"
  "      }\n"
  "      var ctx = document.getElementById('myAreaChart');\n"
  "      var myLineChart = new Chart(ctx, {\n"
  "        type: 'line',\n"
  "        data: {\n"
  "          labels: ['-50 sec', '-45 sec', '-40 sec', '-35 sec', '-30 sec', '-25 sec', '-20 sec', '-15 sec', '-10 sec', '-5 sec', 'Now'],\n"
  "          datasets: [{\n"
  "            label: 'Sıcaklık',\n"
  "            lineTension: 0.3,\n"
  "            backgroundColor: 'rgba(78, 115, 223, 0.5)',\n"
  "            borderColor: 'rgba(78, 115, 223, 1)',\n"
  "            pointRadius: 3,\n"
  "            pointBackgroundColor: 'rgba(78, 115, 223, 1)',\n"
  "            pointBorderColor: 'rgba(78, 115, 223, 1)',\n"
  "            pointHoverRadius: 3,\n"
  "            pointHoverBackgroundColor: 'rgba(78, 115, 223, 1)',\n"
  "            pointHoverBorderColor: 'rgba(78, 115, 223, 1)',\n"
  "            pointHitRadius: 10,\n"
  "            pointBorderWidth: 2,\n"
  "            data: [null, null, null, null, null, null, null, null, null, null],\n"
  "          }],\n"
  "        },\n"
  "        options: {\n"
  "          responsive: true,\n"
  "          maintainAspectRatio: false,\n"
  "          layout: {\n"
  "            padding: {\n"
  "              left: 10,\n"
  "              right: 25,\n"
  "              top: 25,\n"
  "              bottom: 0\n"
  "            }\n"
  "          },\n"
  "          scales: {\n"
  "            xAxes: [{\n"
  "              time: {\n"
  "                unit: 'date'\n"
  "              },\n"
  "              gridLines: {\n"
  "                display: false,\n"
  "                drawBorder: false\n"
  "              },\n"
  "              ticks: {\n"
  "                maxTicksLimit: 7\n"
  "              }\n"
  "            }],\n"
  "            yAxes: [{\n"
  "              ticks: {\n"
  "                maxTicksLimit: 5,\n"
  "                padding: 10,\n"
  "                callback: function(value, index, values) {\n"
  "                  return number_format(value) + ' C°';\n"
  "                }\n"
  "              },\n"
  "              gridLines: {\n"
  "                color: 'rgb(234, 236, 244)',\n"
  "                zeroLineColor: 'rgb(234, 236, 244)',\n"
  "                drawBorder: false,\n"
  "                borderDash: [2],\n"
  "                zeroLineBorderDash: [2]\n"
  "              }\n"
  "            }],\n"
  "          },\n"
  "          legend: {\n"
  "            display: false\n"
  "          },\n"
  "          tooltips: {\n"
  "            backgroundColor: 'rgb(255,255,255)',\n"
  "            bodyFontColor: '#858796',\n"
  "            titleMarginBottom: 10,\n"
  "            titleFontColor: '#6e707e',\n"
  "            titleFontSize: 14,\n"
  "            borderColor: '#dddfeb',\n"
  "            borderWidth: 1,\n"
  "            xPadding: 15,\n"
  "            yPadding: 15,\n"
  "            displayColors: false,\n"
  "            intersect: false,\n"
  "            mode: 'index',\n"
  "            caretPadding: 10,\n"
  "            callbacks: {\n"
  "              label: function(tooltipItem, chart) {\n"
  "                var datasetLabel = chart.datasets[tooltipItem.datasetIndex].label || '';\n"
  "                return datasetLabel + ' ' + number_format(tooltipItem.yLabel) + ' C°';\n"
  "              }\n"
  "            }\n"
  "          }\n"
  "        }\n"
  "      });\n"
  "    </script>\n"
  "<script>\n"
  "setInterval(function() \n"
  "{\n"
  "  getData();\n"
  "}, 1000); \n"
  "setInterval(function() \n"
  "{\n"
  "  getData2();\n"
  "}, 2000); \n"
  "function getData() {\n"
  "  var xhttp = new XMLHttpRequest();\n"
  "  xhttp.onreadystatechange = function() {\n"
  "    if (this.readyState == 4 && this.status == 200) {\n"
  "      document.getElementById(\"adc_val\").innerHTML = this.responseText;\n"
  "    }\n"
  "  };\n"
  "  xhttp.open(\"GET\", \"readTempC\", true);\n"
  "  xhttp.send();\n"
  "}\n"
  "function getData2() {\n"
  "  var xhttp = new XMLHttpRequest();\n"
  "  xhttp.onreadystatechange = function() {\n"
  "    if (this.readyState == 4 && this.status == 200) {\n"
  "\t  if (myLineChart.config.data.datasets[0].data.length >= 11) myLineChart.config.data.datasets[0].data.shift();\n"
  "        myLineChart.config.data.datasets[0].data.push(this.responseText);\n"
  "        myLineChart.update();\n"
  "    }\n"
  "  };\n"
  "  xhttp.open(\"GET\", \"readTempC\", true);\n"
  "  xhttp.send();\n"
  "}\n"
  "</script>\n"
  "</center>\n"
  "</body>\n"
  "</html>\n"
  "\n"
  "";

  server.send(200, "text/html", HTML);
}
