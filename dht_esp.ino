#include <SSD1306Wire.h>
#include <Wire.h>
#include <DHT.h>

#define DHTPIN D3       // Chân kết nối cảm biến DHT11 với ESP8266
#define DHTTYPE DHT11   // Loại cảm biến DHT (DHT11 hoặc DHT22)

DHT dht(DHTPIN, DHTTYPE);
SSD1306Wire display(0x3C, D2, D1);  // Địa chỉ I2C của màn hình OLED và chân kết nối SDA, SCL

unsigned long previousMillis = 0;
const long interval = 2000;  // Thời gian hiển thị nhiệt độ và độ ẩm

bool displayTemperatureHumidity = true;  // Biến để chuyển đổi giữa hiển thị nhiệt độ và độ ẩm và hiển thị "Phi Hung Projects"

void setup() {
  Serial.begin(57600);
  dht.begin();
  display.init();
  display.flipScreenVertically();
}

void drawStar() {
  // Vẽ một ngôi sao đơn giản
  display.drawLine(62, 25, 67, 35);
  display.drawLine(67, 35, 72, 25);
  display.drawLine(72, 25, 62, 30);
  display.drawLine(62, 30, 72, 30);
  display.drawLine(72, 30, 62, 25);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Lưu thời điểm hiện tại
    previousMillis = currentMillis;

    if (displayTemperatureHumidity) {
      // Hiển thị nhiệt độ và độ ẩm
      float humidity = dht.readHumidity();
      float temperature = dht.readTemperature();

      if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Lỗi đọc dữ liệu từ cảm biến DHT!");
        return;
      }

      // In giá trị nhiệt độ và độ ẩm lên Serial Monitor
      Serial.print("Nhiệt độ: ");
      Serial.print(temperature, 1);
      Serial.print("°C\t");

      Serial.print("Độ ẩm: ");
      Serial.print(humidity, 1);
      Serial.println("%");

      // Hiển thị lên màn hình OLED
      display.clear();
      display.setTextAlignment(TEXT_ALIGN_CENTER);

      display.setFont(ArialMT_Plain_24);
      display.drawString(64, 0, String(temperature, 1) + "°C");
      display.drawString(64, 30, String(humidity, 1) + "%");

      display.display();
    } else {
      // Hiển thị "Phi Hung Projects"
      display.clear();
      display.setTextAlignment(TEXT_ALIGN_CENTER);

      display.setFont(ArialMT_Plain_16);
      display.drawString(64, 15, "Tra Meo");
      display.drawString(64, 30, "An cut");

      display.display();
    }

    // Chuyển đổi giữa hai chế độ hiển thị
    displayTemperatureHumidity = !displayTemperatureHumidity;
  }
}
