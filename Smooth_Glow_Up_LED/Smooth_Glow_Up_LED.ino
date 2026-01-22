#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

/* ===== LED CONFIGURATION ===== */
int leds[] = { 21, 22, 23, 19, 18, 5 };
int pwmChannels[] = { 0, 1, 2, 3, 4, 5 };

bool startSequence = false;

/* ===== Wi-Fi CONFIGURATION ===== */
const char* ssid = "ESP32_LED";
const char* password = "12345678";

/* ===== SETUP ===== */
void setup() {
  Serial.begin(115200);

  // PWM setup (ESP32 core v3.x)
  for (int i = 0; i < 6; i++) {
    ledcAttach(leds[i], 5000, 8);  // pin, freq, resolution
    ledcWrite(leds[i], 0);
  }

  WiFi.softAP(ssid, password);
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/start", startLED);
  server.on("/stop", stopLED);

  server.begin();
}

/* ===== LOOP ===== */
void loop() {
  server.handleClient();

  if (startSequence) {
    for (int i = 0; i < 6; i++) {
      for (int brightness = 0; brightness <= 255; brightness++) {
        ledcWrite(leds[i], brightness);
        delay(8);
      }
      delay(150);
    }
    startSequence = false;
  }
}

/* ===== HANDLERS ===== */

void startLED() {
  startSequence = true;
  server.send(200, "text/plain", "Started");
}

void stopLED() {
  for (int i = 0; i < 6; i++) {
    ledcWrite(leds[i], 0);
  }
  startSequence = false;
  server.send(200, "text/plain", "Stopped");
}

/* ===== UI ===== */

void handleRoot() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32 Smart Diya</title>
<style>
body{
 margin:0;height:100vh;
 background:radial-gradient(circle,#1c1917,#020617);
 font-family:Segoe UI;
 display:flex;align-items:center;justify-content:center;
 color:#f8fafc;
}
.container{text-align:center;}
h1{margin-bottom:40px;letter-spacing:1px;}
.diya-btn{
 width:160px;height:160px;border-radius:50%;
 border:none;
 background:radial-gradient(circle,#fde68a,#f59e0b,#b45309);
 box-shadow:0 0 20px rgba(245,158,11,.6),0 0 60px rgba(245,158,11,.4);
 font-size:1.05rem;font-weight:600;
 cursor:pointer;
}
.status{font-size:1.4rem;margin-bottom:25px;}
.back-btn{
 padding:12px 28px;border-radius:25px;border:none;
 background:#334155;color:white;font-size:.9rem;
 cursor:pointer;
}
</style>
</head>

<body>
<div class="container">
<h1>ESP32 Smart Diya</h1>

<div id="initial">
 <button class="diya-btn" onclick="lightDiya()">Light up Diya</button>
</div>

<div id="lit" style="display:none;">
 <div class="status">Diya is Lit</div>
 <button class="back-btn" onclick="turnOff()">Back</button>
</div>
</div>

<script>
function lightDiya(){
 fetch("/start");
 initial.style.display="none";
 lit.style.display="block";
}
function turnOff(){
 fetch("/stop");
 lit.style.display="none";
 initial.style.display="block";
}
</script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}
