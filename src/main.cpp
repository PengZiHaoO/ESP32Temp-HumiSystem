#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DFRobot_DHT11.h>
#include <DabbleESP32.h>
#include <string>

//OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 16
#define OLED_CS 5
#define OLED_RESET 17


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define DHT11_PIN 13
DFRobot_DHT11 DHT;


void TempAndHumiDisplay(int pixel_x, int pixel_y, std::string text1, std::string text2, int temp, int humi) ;
void SendTempAndHumi(char temp, char humi);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello! there!");
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  Dabble.begin("Temp&HumiSystem");
  
  delay(1000);
}

void loop() {
  DHT.read(13);
  delay(2000);
  TempAndHumiDisplay(0, 16, "temperature:", "humidity:", DHT.temperature, DHT.humidity);
  SendTempAndHumi(DHT.temperature, DHT.humidity);
}

void TempAndHumiDisplay(int pixel_x, int pixel_y, std::string text1, std::string text2, int temp, int humi) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(pixel_x, pixel_y);
  display.print(text1.c_str());
  display.print(temp);
  display.print('C');
  display.print("\n\n");
  display.print(text2.c_str());
  display.print(humi);
  display.print('%');
  display.display();
}

void SendTempAndHumi(char temp, char humi){
  Dabble.appWrite(temp);
  Dabble.appWrite(humi);
}
