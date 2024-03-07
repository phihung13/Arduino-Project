#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h>  
Adafruit_SSD1306 display;  
#include <Fonts/FreeMonoBold12pt7b.h>  
#include <Fonts/FreeMono9pt7b.h>  
#include <Wire.h>
#include <DHT.h>

#define DHTPIN D3       // Chân kết nối cảm biến DHT11 với ESP8266
#define DHTTYPE DHT11   // Loại cảm biến DHT (DHT11 hoặc DHT22)

DHT dht(DHTPIN, DHTTYPE);
void setup()  
{ 
  Serial.begin(115200);
  dht.begin();    
  delay(100);  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();  // Xóa toàn bộ màn hình
  display.setTextColor(WHITE);  
  display.setRotation(0);  
  display.setTextWrap(false);  
  display.dim(0);  

  // Hiển thị chữ "Phi Hùng"
  display.setFont(&FreeMonoBold12pt7b);
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Phi Hung");
  display.display();
}

void loop()  
{
  float humidity = dht.readHumidity();    // Đọc độ ẩm
  float temperature = dht.readTemperature();  // Đọc nhiệt độ (độ C)

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Lỗi đọc dữ liệu từ cảm biến DHT!");
    return;
  }
  Serial.print("Nhiệt độ: ");
  Serial.print(temperature, 1);
  Serial.print("°C\t");

  Serial.print("Độ ẩm: ");
  Serial.print(humidity, 1);
  Serial.println("%");
  display.clearDisplay(); 
  display.setFont(&FreeMonoBold12pt7b);
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Phi Hung");
  display.display();
}
