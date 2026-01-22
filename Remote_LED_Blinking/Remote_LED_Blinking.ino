#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

// LED pins
int leds[] = { 21, 22, 23, 19, 18, 5 };
bool startSequence = false;

// Wi-Fi credentials
const char* ssid = "ESP32_LED";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);

  // Set LED pins as output
  for (int i = 0; i < 6; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  // Start ESP32 Access Point
  WiFi.softAP(ssid, password);

  Serial.println("WiFi Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Web routes
  server.on("/", handleRoot);
  server.on("/start", startLED);
  server.on("/stop", stopLED);

  server.begin();
}

void loop() {
  server.handleClient();

  if (startSequence) {
    for (int i = 0; i < 6; i++) {
      digitalWrite(leds[i], HIGH);
      delay(500);
    }
    startSequence = false;
  }
}

// ===== Web Page =====
void handleRoot() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32 Smart Diya</title>

<style>
  body {
    margin: 0;
    height: 100vh;
    background: radial-gradient(circle at center, #1c1917, #020617);
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    display: flex;
    align-items: center;
    justify-content: center;
    color: #f8fafc;
  }

  .container {
    text-align: center;
  }

  h1 {
    font-weight: 500;
    letter-spacing: 1px;
    margin-bottom: 40px;
    opacity: 0.9;
  }

  .diya-btn {
    width: 160px;
    height: 160px;
    border-radius: 50%;
    border: none;
    background: radial-gradient(circle at top, #fde68a, #f59e0b, #b45309);
    box-shadow:
      0 0 20px rgba(245, 158, 11, 0.6),
      0 0 60px rgba(245, 158, 11, 0.4);
    color: #1c1917;
    font-size: 1.05rem;
    font-weight: 600;
    cursor: pointer;
    transition: transform 0.1s ease, box-shadow 0.2s ease;
  }

  .diya-btn:active {
    transform: scale(0.94);
    box-shadow:
      0 0 10px rgba(245, 158, 11, 0.4),
      0 0 30px rgba(245, 158, 11, 0.2);
  }

  .status {
    display: none;
    font-size: 1.4rem;
    margin-bottom: 25px;
    letter-spacing: 1px;
  }

  .back-btn {
    padding: 12px 26px;
    border-radius: 25px;
    border: none;
    background: #334155;
    color: white;
    font-size: 0.9rem;
    cursor: pointer;
  }

  a, button {
    outline: none;
    -webkit-tap-highlight-color: transparent;
  }
</style>
</head>

<body>
  <div class="container">

    <div id="initial">
      <button class="diya-btn" onclick="lightDiya()">Light up Diya</button>
    </div>

    <div id="lit">
      <div class="status">Diya is Lit</div>
      <button class="back-btn" onclick="turnOff()">Back</button>
    </div>

  </div>

<script>
  document.getElementById("lit").style.display = "none";

  function lightDiya() {
    fetch("/start");
    document.getElementById("initial").style.display = "none";
    document.getElementById("lit").style.display = "block";
  }

  function turnOff() {
    fetch("/stop");
    document.getElementById("lit").style.display = "none";
    document.getElementById("initial").style.display = "block";
  }
</script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}



void startLED() {
  startSequence = true;
  server.send(200, "text/plain", "LED Sequence Started");
}

void stopLED() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(leds[i], LOW);
  }
  startSequence = false;
  server.send(200, "text/plain", "LEDs Stopped");
}
