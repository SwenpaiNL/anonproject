//If u have questions regarding this SPECIFIC code then u can contact me on instagram @Swenpai_nl
//I wrote this code with some help of a friend a few months back, so I may have to look back into what I did at that time...
//Will try to add more arduino in my cosplays projects in the future! I dont have all the resources to do that at the moment
//This code is by no means perfect lol, I just posted this in the hope to help someone :)
//https://github.com/SwenpaiNL <----- Here you will find more of my code in the future (28/10/2019)

//WHAT DOES THIS CODE DO????
//U can find that on my instagram page under my highlights!


//the fastled library is probably the most well known libarary if u want to work with WS2812B LED strips
#include <FastLED.h>
const int buttonPin = 11;
const int switchPin = 10;
int i;
int d;
// if(digitalRead(switchPin)
// How many leds in your strip?
#define NUM_LEDS 16
int ALL_LEDS = ((NUM_LEDS) * 2) - 1;
// For led chips like Neopixels, which have a data line, ground, and power, you just need to define DATA_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS * 2];
#define DATA_PIN2 4
#define RINGNUM 16
CRGB ledsR[RINGNUM];

#define DATA_PIN3 13
#define RINGNUM2 8
CRGB ledsR2[RINGNUM2];

int delay_ = 30;
int fade = 12;
int speed_;
int iteration_;
int kleur = 177;

void setup() {
  Serial.begin(57600);
  Serial.println("resetting");
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, ALL_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN2, RGB>(ledsR, RINGNUM);
  FastLED.addLeds<WS2812B, DATA_PIN3, RGB>(ledsR2, RINGNUM2);
  pinMode(buttonPin, INPUT);
  pinMode(switchPin, INPUT);
  LEDS.setBrightness(100);

}

void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(150);
    leds[ALL_LEDS - i].nscale8(150);
    ledsR[i].nscale8(150);
    ledsR2[i].nscale8(150);
//    ledsR[i].nscale8(150);
    //leds[i].fadeToBlackBy( 64 );
  }
}

void changeColor() {
  if (digitalRead(buttonPin)) {
    if (kleur == 177) {
      kleur = 25;
    }
  }
  else {
    if (kleur == 25) {
      kleur = 177;
    }
  }
}

void ringAnimation() {
   
  for (int i = 0; i < RINGNUM; i++) {
    changeColor();
    ledsR[i] = CHSV(kleur, 255, 255);
    FastLED.show();
  }
 
}

void loop() {
  static uint8_t hue = 0;
  static uint8_t val = 0; //kan ik brightness mee ++
  //aan uit
  //  if (digitalRead(switchPin)) {
  //    LEDS.setBrightness(100);
  //   // Serial.println(digitalRead(switchPin));
  //  }
  //  else {
  //    LEDS.setBrightness(0);
  //   // Serial.println(digitalRead(switchPin));
  //  }

  //  if (digitalRead(buttonPin)) {
  //charge

  for (d = 80; d > 4; d -= speed_) {
    Serial.println(d);
    if (d > 20) {
      speed_ = 5;
      iteration_ = 3;
    } else if (d > 5) {
      speed_ = 1;
      iteration_ = 4;
    } else if (d <= 5) {
      speed_ = 1;
      iteration_ = 75;
    }

    Serial.println((String)"delay: " + d);
    Serial.println((String)"iteration: " +  iteration_);
    Serial.println((String)"speed: " +  speed_);
    Serial.println(buttonPin);

    for (int i = 0; i < iteration_; i++) {
      for (int i = 0; i < NUM_LEDS; i++) {
        changeColor();
        // Set the i'th led to red
        //leds[i] = CHSV(hue++, 255, 255);
        leds[i] = CHSV(kleur, 255, 255);
        leds[ALL_LEDS - i] = CHSV(kleur, 255, 255);

        if (i >= RINGNUM) {
          ledsR[i % RINGNUM] = CHSV(kleur, 255, 255);
        } else {
          ledsR[i] = CHSV(kleur, 255, 255);
        }

        if (i >= RINGNUM2) {
          ledsR2[i % RINGNUM2] = CHSV(kleur, 255, 255);
        } else {
          ledsR2[i] = CHSV(kleur, 255, 255);
        }


        // Show the leds
        FastLED.show();
        // now that we've shown the leds, reset the i'th led to black
        fadeall();
        //leds[i] = CRGB::Black;
        // Wait a little bit before we loop around and do it again
        delay(d);
      }
    }

  }
  //  end charge
  //          fading
   for (i = 0 ; i < 3; i++) {
     for (int v = 0; v <= 255; v += fade) {
       for (int i = 0; i < ALL_LEDS; i++) {
         changeColor();
         leds[i] = CHSV(kleur, 255, v);
         ledsR[i] = CHSV(kleur, 255, v);
         ledsR2[i] = CHSV(kleur, 255, v);
         FastLED.show();
       }
     }
     delay(500);
     for (int v = 255; v >= 0; v -= fade) {
       for (int i = 0; i < ALL_LEDS; i++) {
         changeColor();
         leds[i] = CHSV(kleur, 255, v);
         ledsR[i] = CHSV(kleur, 255, v);
         ledsR2[i] = CHSV(kleur, 255, v);

         FastLED.show();
       }
     }
     d = 80;
   }
  //  end fading

  // } else {
  //ze gebruiken hier NUM_LEDS -1 dus dat hele stuk in een variabel?
  //    for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
  //      // Set the i'th led to red
  //      //leds[i] = CHSV(hue++, 255, 255);
  //      leds[i] = CHSV(155, 255, 255);
  //      // Show the leds
  //      FastLED.show();
  //      // now that we've shown the leds, reset the i'th led to black
  //      fadeall();
  //      //leds[i] = CRGB::Black;
  //      // Wait a little bit before we loop around and do it again
  //      delay(delay_);
  //
  //    }

  //  }




}
