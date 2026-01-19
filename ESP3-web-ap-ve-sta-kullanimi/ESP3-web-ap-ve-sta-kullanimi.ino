#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <time.h>

WebServer server(80);
Preferences preferences;

/* AP Bilgileri */
const char* AP_SSID = "ESP32-AYAR";
const char* AP_PASS = "12345678";

/* NTP */
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3 * 3600; // Türkiye
const int daylightOffset_sec = 0;

String sta_ssid = "";
String sta_pass = "";

/* ================= HTML SAYFALAR ================= */

String apPage() {
  return R"rawliteral(
<!DOCTYPE html><html>
<head>
<meta charset="utf-8">
<title>ESP32 WiFi Ayar</title>
<style>
body{font-family:Arial;text-align:center;background:#111;color:#0f0;}
input,button{padding:10px;margin:8px;width:80%;font-size:16px;}
button{background:#0f0;border:none;}
</style>
</head>
<body>
<h2>WiFi Ayarlari</h2>
<form action="/save" method="POST">
<input name="ssid" placeholder="WiFi SSID" required><br>
<input name="pass" type="password" placeholder="WiFi Sifre"><br>
<button>Baglan</button>
</form>
</body>
</html>
)rawliteral";
}

String staPage() {
  return R"rawliteral(
<!DOCTYPE html><html>
<head>
<meta charset="utf-8">
<title>ESP32 Saat</title>
<style>
body{font-family:Arial;text-align:center;background:#000;color:#0f0;}
#clock{font-size:40px;margin-top:40px;}
</style>
</head>
<body>
<h2>Turkiye Saati</h2>
<div id="clock">--:--:--</div>
<script>
setInterval(()=>{
 fetch("/time")
 .then(r=>r.text())
 .then(t=>document.getElementById("clock").innerHTML=t);
},1000);
</script>
</body>
</html>
)rawliteral";
}

/* ================= YARDIMCI FONKSİYONLAR ================= */

bool isFromAP() {
  IPAddress ip = server.client().remoteIP();
  return (ip[0] == 192 && ip[1] == 168 && ip[2] == 4);
}

String getTimeStr() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "Saat yok";

  char buf[30];
  strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", &timeinfo);
  return String(buf);
}

/* ================= WiFi ================= */

bool connectSTA(String ssid, String pass) {
  WiFi.disconnect(true);
  delay(500);

  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.print("STA baglaniyor");

  unsigned long t = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t < 15000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nSTA baglandi!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    return true;
  }

  Serial.println("\nSTA baglanamadi!");
  return false;
}

/* ================= WEB HANDLER ================= */

void handleRoot() {
  if (isFromAP()) {
    server.send(200, "text/html", apPage());
  } else {
    server.send(200, "text/html", staPage());
  }
}

void handleSave() {
  String newSSID = server.arg("ssid");
  String newPASS = server.arg("pass");

  bool ok = connectSTA(newSSID, newPASS);

  if (ok) {
    preferences.begin("wifi", false);
    preferences.putString("ssid", newSSID);
    preferences.putString("pass", newPASS);
    preferences.end();

    server.send(200, "text/html",
      "<h2>Baglanti Basarili!</h2><p>Yeni WiFi aktif.</p>");
  } else {
    server.send(200, "text/html",
      "<h2>Baglanti Basarisiz!</h2><p>Tekrar deneyin.</p>");
  }
}

void handleTime() {
  server.send(200, "text/plain", getTimeStr());
}

/* ================= SETUP & LOOP ================= */

void setup() {

  
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(AP_SSID, AP_PASS);

  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  preferences.begin("wifi", true);
  sta_ssid = preferences.getString("ssid", "");
  sta_pass = preferences.getString("pass", "");
  preferences.end();

  if (sta_ssid != "") {
    connectSTA(sta_ssid, sta_pass);
  }

  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.on("/time", handleTime);
  server.begin();
}

void loop() {
  server.handleClient();
}
