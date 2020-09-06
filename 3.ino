#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "kf3BOKdNfg3zY6JpkXzQ_09SAD5h3Av9";
char ssid[] = "U+NetFE93";
char pass[] = "4000005443";
///////////////////ESP

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define NEOPIXEL D1
#define NUMPIXELS 8
Adafruit_NeoPixel strip(NUMPIXELS, NEOPIXEL, NEO_GRB + NEO_KHZ800);

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
///////////////////NEOPIXEL D1

#include <Servo.h>
Servo myServo;
///////////////////SERVO D2

#include "pitches.h"
#define Melody   D3
/*
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
*/
#define NOTE_G4  392
#define NOTE_C5 523 //도 
#define NOTE_D5 587 //레 
#define NOTE_E5 659 //미 
#define NOTE_F5 698 //파 
#define NOTE_G5 784 //솔 
#define NOTE_A5 880 //라 
#define NOTE_B5 988 //시 
#define NOTE_C6 1047 //도 

int melody[] = { NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5, NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5, NOTE_G5,NOTE_G5,NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5, NOTE_C5,NOTE_C5,NOTE_C5, NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5, NOTE_G5,NOTE_G5,NOTE_G5, NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5, NOTE_G5,NOTE_G5,NOTE_G5, NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5, NOTE_G5,NOTE_G5,NOTE_G5,NOTE_A5,NOTE_G5, NOTE_C6,NOTE_G5,NOTE_C6,NOTE_G5, NOTE_E5,NOTE_D5,NOTE_C5 }; 
int noteDurations[]={ 4,8,8,4,4, 4,8,8,4,4, 8,8,4,8,8,4, 4,4,2, 4,4,4,4, 4,4,2, 4,4,4,4, 4,4,2, 4,4,4,4, 8,8,8,8,2, 4,4,4,4, 4,4,2 };

///////////////////PIEZO D3



void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  myServo.attach(D2);
  
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  pinMode(Melody, OUTPUT);
}

BLYNK_WRITE(V0){ //Hi
  int pinValue1 = param.asInt();
  if (pinValue1 == 1) {
    tone(Melody, NOTE_C5); //pin, 음계, 음계의 음길이
    delay(200);
    tone(Melody, NOTE_E5); //pin, 음계, 음계의 음길이
    delay(300);
    tone(Melody, NOTE_G5); //pin, 음계, 음계의 음길이
    delay(300);
    noTone(Melody);
    
    myServo.write(0);
    delay(500);
    myServo.write(120);
    delay(300);
    myServo.write(90);
    delay(300);
    myServo.write(120);
    delay(300);
    myServo.write(90);
    delay(300);
  //tone()
    
    colorWipe(strip.Color(255, 255, 255), 50); // White
  } else {
    tone(Melody, NOTE_G5); //pin, 음계, 음계의 음길이
    delay(300);
    tone(Melody, NOTE_E5); //pin, 음계, 음계의 음길이
    delay(200);
    tone(Melody, NOTE_G4); //pin, 음계, 음계의 음길이
    delay(200);
    noTone(Melody);  
    
    myServo.write(120);
    delay(300);
    myServo.write(90);
    delay(300);
    myServo.write(0); 
    
    colorWipe(strip.Color(0, 0, 0), 50); // White
    
  }
}
/*
BLYNK_WRITE(V1){ //Bye
  int pinValue1 = param.asInt();
  if (pinValue1 == 1) {   
    colorWipe(strip.Color(0,0,0), 50); // White
    //tone()
    
    myServo.write(120);
    delay(300);
    myServo.write(90);
    delay(300);
    myServo.write(0);  
    
  } else {
    colorWipe(strip.Color(255,255,255), 50); // White
    myServo.write(90);
  }
}*/

BLYNK_WRITE(V2){ //sing
  int pinValue2 = param.asInt (); //V0에서 들어오는 값을 변수에 할당
  if (pinValue2 == 1){
    for (int i = 0; i < 49; i++) { 
    int Durations = 1000/noteDurations[i]; // 음계의 음길이 계산 
    tone(Melody, melody[i], Durations); 
    int pauseBetweenNotes = Durations *1.3 ; 
    delay(pauseBetweenNotes); 
    noTone(Melody); 
    } 
  } else noTone(Melody);
  
}

BLYNK_WRITE(V3){ //Highfive
  int pinValue3 = param.asInt ();
  if(pinValue3 == 1){
   myServo.write(135);
    delay(2000);
    myServo.write(90);
    delay(1000);
    myServo.write(100);
    delay(1000);
    myServo.write(90);
  }
}
/*
BLYNK_WRITE(V1) { //NEOPIXEL
  int pinValue1 = param.asInt (); //V0에서 들어오는 값을 변수에 할당
  if (pinValue1 == 1) {
    colorWipe(strip.Color(255, 255, 255), 50); // White
  } else {
    colorWipe(strip.Color(0, 0, 0), 50); // White
  }
}

BLYNK_WRITE(V2){ //Servo
  int pinValue2 = param.asInt ();
  if(pinValue2 == 1){
    myServo.write(180);
  delay(1000);
  myServo.write(90);
  delay(1000); //각도
  } 
}



*/

void loop() {
  Blynk.run();
}
