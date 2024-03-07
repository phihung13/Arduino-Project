#include <Arduino.h>
#include <time.h>
#include <sys/time.h>
#include <ESPWiFi.h>

const char* WIFI_SSID = "CARROT";
const char* WIFI_PWD = "Carrot11042015";

void setup() {
  Serial.begin(115200);
  delay(2000);

  // Kết nối WiFi
  WiFi.begin(WIFI_SSID, WIFI_PWD);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
  }

  // Cài đặt múi giờ từ mạng
  const int TZ = 7;       // UTC+7
  const int DST_MN = 0;   // No DST
  const int TZ_SEC = TZ * 3600;
  const int DST_SEC = DST_MN * 60;
  configTime(TZ_SEC, DST_SEC, "pool.ntp.org");
}

void loop() {
  time_t now;
  struct tm timeInfo;

  // Lấy thời gian hiện tại
  time(&now);

  // Chuyển đổi thời gian sang múi giờ địa phương
  localtime_r(&now, &timeInfo);

  // Hiển thị thời gian trên Serial Monitor
  Serial.print("Current time: ");
  Serial.print(timeInfo.tm_hour);
  Serial.print(":");
  Serial.print(timeInfo.tm_min);
  Serial.print(":");
  Serial.println(timeInfo.tm_sec);

  delay(1000); // Chờ 1 giây
}
