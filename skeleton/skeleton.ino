/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

#define CLOSED_POSITION (150)
#define OPEN_POSITION (100)

#define SERVO_DELAY_MS (0)

#define AUDIO_THRESHOLD (100)

#define AUDIO_THRESHOLD_PIN (2)
#define EYES_PIN (3)

Servo myservo;  // create servo object to control a servo
volatile bool threshold_reached;
bool mouth_opened;

void setup() {
  threshold_reached = false;
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(CLOSED_POSITION);
  mouth_opened = false;

  pinMode(AUDIO_THRESHOLD_PIN, INPUT_PULLUP);
  pinMode(EYES_PIN, OUTPUT);
  eyes_off();
  enable_interrupt();
}

void loop() {
  if(threshold_reached)
  {
//    eyes_on();
    open_mouth();
    threshold_reached = false;
    delay(250);
  }

  
  if(!threshold_reached && mouth_opened)
  {
    eyes_off();
    close_mouth();
  }
}

void eyes_on()
{
  digitalWrite(EYES_PIN, HIGH);
}

void eyes_off()
{
  digitalWrite(EYES_PIN, LOW);
}

void open_mouth()
{
  disable_interrupt();
  myservo.write(OPEN_POSITION);
  mouth_opened = true;
  delay(SERVO_DELAY_MS);
  enable_interrupt();
}

void close_mouth()
{
  disable_interrupt();
  myservo.write(CLOSED_POSITION);
  mouth_opened = false;
  delay(SERVO_DELAY_MS);
  enable_interrupt();
}

void enable_interrupt()
{
  attachInterrupt(digitalPinToInterrupt(AUDIO_THRESHOLD_PIN), sound_int, FALLING);
}

void disable_interrupt()
{
  detachInterrupt(digitalPinToInterrupt(AUDIO_THRESHOLD_PIN));
}

void sound_int()
{
  threshold_reached = true;
}
