// MTG Life Counter by Ben
// Built on Arduino Nano

#include <SPI.h>
#include <RGBLed.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <JC_Button.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
// declare rgb led pins and create 2 led objects (jc_button)
RGBLed led1(2, 3, 4, RGBLed::COMMON_CATHODE);
RGBLed led2(8, 6, 7, RGBLed::COMMON_CATHODE);

// declare key switch pins
Button oneUp(10);
Button oneDown(9);
Button twoUp(12);
Button twoDown(11);

// these are starting life, but also keep track of both life titles
int startingLife1 = 20;
int startingLife2 = 20;


// these will keep track of numbers to display the correct rgb color
int colorPos1 = 0;
int colorPos2 = 0;

// keeps track of text position based on digits present
int oneLifePos = 0;
int twoLifePos = 0; 


// keeps track of digit text size
int oneLifeSize = 3;
int twoLifeSize = 3;

void setup() {
    Serial.begin(9600);

    // just a nice starting color
    led1.crossFade(RGBLed::BLUE, RGBLed::MAGENTA, 10, 300);
    led2.crossFade(RGBLed::BLUE, RGBLed::MAGENTA, 10, 300);

    // setup oled and display "splash screen"
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
    display.setRotation(3); // set this since we're using our oled in "portrait mode"
    display.setCursor(oneLifePos, 90);
    display.println(startingLife1);

    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setRotation(1); // set this since we're using our oled in "portrait mode"
    display.setCursor(twoLifePos, 90);
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

  // change color if both keys are pressed
  if (oneUp.isPressed() and oneDown.isPressed()) {
      colorPos2++;
      Serial.println("both 1");
      if (oneUp.pressedFor(2000) and oneDown.pressedFor(2000)) {
        startingLife1 = 20;  
        oneLifeSize = 3;
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

  // change color if both keys are pressed
  else if (twoUp.isPressed() and twoDown.isPressed()) {
    colorPos1++;
    Serial.println("both 1");
    if (twoUp.pressedFor(2000) and twoDown.pressedFor(2000)) {
      startingLife2 = 20;
      twoLifeSize = 3;
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

  // whenever a key is pressed, update our oled
  if (oneUp.isPressed() or oneDown.isPressed() or twoUp.isPressed() or twoDown.isPressed()) {
    if (startingLife1 < 10) {
      oneLifePos = 10;
    } else {
        oneLifePos = 0;
      }
    if (startingLife2 < 10) {
      twoLifePos = 7; 
    } else {
        twoLifePos = 0;
      }

    if (startingLife1 < 0) {
      oneLifePos = 0;
    }
    if (startingLife2 < 0) {
      twoLifePos = 0;
    }

    if (startingLife1 < -10) {
      oneLifeSize = 2;
      oneLifePos = -2;
    }
    if (startingLife2 < -10) {
      twoLifeSize = 2;
      twoLifePos = -1;
    }
    
    display.clearDisplay();
    display.setTextSize(oneLifeSize);
    display.setTextColor(WHITE);
    display.setRotation(3);
    display.setCursor(oneLifePos, 90);
    display.println(startingLife1);

    display.setTextSize(twoLifeSize);
    display.setTextColor(WHITE);
    display.setRotation(1);
    display.setCursor(twoLifePos, 90);
    display.println(startingLife2);
    display.display();
  }
}
