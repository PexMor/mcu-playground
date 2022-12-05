#define ENABLE_GxEPD2_GFX 0
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <bitmaps/Bitmaps400x300.h> // 4" b/w

#if defined(ESP32)
//GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEH0154D67, LaskaKit: Waveshare 1.54"
GxEPD2_BW<GxEPD2_420_M01, GxEPD2_420_M01::HEIGHT> display(GxEPD2_420_M01(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW042M01, LaskaKit: Waveshare 4.2"
//GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW075T7 800x480,  LaskaKit: Waveshare 7.5"
//GxEPD2_3C<GxEPD2_154_Z90c, GxEPD2_154_Z90c::HEIGHT> display(GxEPD2_154_Z90c(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEH0154Z90, LaskaKit: Colour Waveshare 1.54"
#endif

#define SLEEP_SEC 15         // Measurement interval (seconds)

void goToSleep(){
  Serial.println("going to sleep " + String(SLEEP_SEC) + " sek");
  // ESP Deep Sleep 
  digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
  Serial.println("Display power OFF");
  Serial.println("ESP in sleep mode");
  Serial.flush(); 
  esp_sleep_enable_timer_wakeup(SLEEP_SEC * 1000000);
  esp_deep_sleep_start();
}

const char HelloWorld[] = "Hello World!";

void helloWorld()
{
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  if (display.epd2.WIDTH < 104) display.setFont(0);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Setup UART");
  delay(100);
  // turn on power to display
  pinMode(2, OUTPUT);
  delay(1000);
  Serial.println("Power ON, via pin 2");
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("Wait for 2s");
  delay(2000);
  Serial.println("Initialize display without init of serial port");
  // You have to intialize the library with bitrate 0 = do not re-initialize
  display.init(0); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  // first update should be full refresh
  Serial.println("helloWorld()");
  helloWorld();
  Serial.println("display.powerOff()");
  display.powerOff();
  Serial.println("goToSleep()");
  goToSleep();
}

void loop()
{
}
