#include <SPI.h>
#include <RGBLed.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <JC_Button.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

RGBLed led1(2, 3, 4, RGBLed::COMMON_CATHODE);
RGBLed led2(8, 6, 7, RGBLed::COMMON_CATHODE);

Button oneUp(10);
Button oneDown(9);
Button twoUp(12);
Button twoDown(11);


int startingLife1 = 20;
int startingLife2 = 20;

int colorPos1 = 0;
int colorPos2 = 0;

void setup() {
    Serial.begin(9600);
    
    led1.crossFade(RGBLed::BLUE, RGBLed::MAGENTA, 10, 300);
    led2.crossFade(RGBLed::BLUE, RGBLed::MAGENTA, 10, 300);
    
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextWrap(false);

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setRotation(2);
    display.setCursor(0, 0);
    display.println("MTG Life Counter");
    display.setCursor(0, 15);
    display.println("by Ben");
    display.display();
    delay(1500);

    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setRotation(3);
    display.setCursor(0, 90);
    display.println(startingLife1);

    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setRotation(1);
    display.setCursor(0, 90);
    display.println(startingLife2);
    display.display();
  
    oneUp.begin();
    oneDown.begin();
    twoUp.begin();
    twoDown.begin();

    colorPos1 = 0;
    colorPos2 = 0;
}

void loop() {
  oneUp.read();
  oneDown.read();
  twoUp.read();
  twoDown.read();
    
  if (oneUp.isPressed() and oneDown.isPressed()) {
      colorPos2++;
      Serial.println("both 1");
      if (oneUp.pressedFor(2000) and oneDown.pressedFor(2000)) {
        startingLife1 = 20;  
      }
  } 
  
  else if (oneUp.isPressed() and !oneDown.isPressed()) {
      startingLife1++;
      Serial.println("up 1");
  }

  else if (!oneUp.isPressed() and oneDown.isPressed()) {
      startingLife1--;
      Serial.println("down 1");
  }

  else if (twoUp.isPressed() and twoDown.isPressed()) {
    colorPos1++;
    Serial.println("both 1");
    if (twoUp.pressedFor(2000) and twoDown.pressedFor(2000)) {
      startingLife2 = 20;
    }
  }

  else if (twoUp.isPressed() and !twoDown.isPressed()) {
    startingLife2--;
    Serial.println("down 2");
  }

  else if (!twoUp.isPressed() and twoDown.isPressed()) {
    startingLife2++;
    Serial.println("up 2");
  }

  else if (oneUp.pressedFor(5000) or twoUp.pressedFor(5000)) {
    startingLife1 = 20;
    startingLife2 = 20;

    Serial.println("RESET");
  }

  else {
    //Serial.println("An error has occurred...");  
  }

  if (colorPos1 >= 7) { 
    colorPos1 = 0;
  }

  if (colorPos2 >= 7) {
    colorPos2 = 0;
  }

  if (colorPos1 == 0) {
      led1.off();
    }
  if (colorPos2 == 0) {
      led2.off();
  }
  if (colorPos1 == 1) {
    led1.setColor(RGBLed::RED);
  }
  if (colorPos2 == 1) {
    led2.setColor(RGBLed::RED);
  }
  if (colorPos1 == 2) {
    led1.setColor(RGBLed::GREEN);
  }
  if (colorPos2 == 2) {
    led2.setColor(RGBLed::GREEN);
  }
  if (colorPos1 == 3) {
    led1.setColor(RGBLed::BLUE);
  }
  if (colorPos2 == 3) {
    led2.setColor(RGBLed::BLUE);
  }
  if (colorPos1 == 4) {
    led1.setColor(RGBLed::MAGENTA);
  }
  if (colorPos2 == 4) {
    led2.setColor(RGBLed::MAGENTA);
  }
  if (colorPos1 == 5) {
    led1.setColor(250, 227, 155);
  }
  if (colorPos2 == 5) {
    led2.setColor(250, 227, 155);
  }

  if (oneUp.isPressed() or oneDown.isPressed() or twoUp.isPressed() or twoDown.isPressed()) {
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setRotation(3);
    display.setCursor(0, 90);
    display.println(startingLife1);

    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setRotation(1);
    display.setCursor(0, 90);
    display.println(startingLife2);
    display.display();
  }
}
