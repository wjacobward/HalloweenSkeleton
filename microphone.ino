#define MIC_PIN (0)
#define AUDIO_THRESHOLD (100)
#define LED_PIN (13)

void setup()
{
  Serial.begin(38400);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  int mic_value = analogRead(MIC_PIN);
  
  if(mic_value > AUDIO_THRESHOLD)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }
  Serial.println(mic_value);
}
