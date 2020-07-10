#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS  30 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 0 // Time (in milliseconds) to pause between pixels
const int trigPin = 11;
const int echoPin = 12;
int led_select;
long duration;
int distance;
void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
   pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(115200); // Starts the serial communication
}
void loop() {

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
pixels.clear(); // Set all pixel colors to 'off'
pixels.show();   // Send the updated pixel colors to the hardware.
  
led_select = map(distance,40,150,8,0);
Serial.println(led_select);

if((distance > 150)|| (distance < 40)){    
  Serial.println("light off ");
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
}

if((distance < 150)&&(distance > 40)){
  Serial.println("light on");
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
  for(int i=0; i<led_select; i++) { // For each pixel...
  if(i < 3){
      pixels.setPixelColor(i, pixels.Color(0,128,0));
      pixels.show();   
  } 
  if((i >= 3)&&(i < 6)){
      pixels.setPixelColor(i, pixels.Color(255,255,0));
      pixels.show();   
      } 
  
  if((i >= 6)&&(i < 9)){
      pixels.setPixelColor(i, pixels.Color(255,0,0));
      pixels.show();   
  }
  }
  delay(500);
}  
}

 
