int sensorPin = 0;
int buzzerPin = 8;
int buttonPin = 12;

boolean wasPressed = false;

//262 - 523 frequency for C4 - C5

int buttonState;
int ledPins[] = {11, 10, 9, 6, 5, 3};

int buzzerTone, lightLevel, ledIntensity, lightsOn = 1, mode = 0, lowFreq = 262, highFreq = 523, highLight = 0, lowLight = 1023;
//lightsOn keeps track of the number of lights that should be on

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  for(int i = 0; i < 6; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  lightLevel = analogRead(sensorPin);
  autoTune();
  buzzerStuff();
  buttonStuff();
  lightStuff();
  
  //buzzerTone = map(lightLevel, highLight, lowLight, lowFreq, highFreq);
  //buzzerTone = constrain(buzzerTone, lowFreq, highFreq);
  /*if(mode < 2){    
    tone(buzzerPin, buzzerTone);
  }
  else{
    noTone(buzzerPin);
  }*/
  
  
}

void autoTune()
{
  if (lightLevel < lowLight)
  {
    lowLight = lightLevel;
  }
  if (lightLevel > highLight)
  {
    highLight = lightLevel;
  }  
}

void buzzerStuff()
{
  if(mode < 2){    
    buzzerTone = map(lightLevel, highLight-30, lowLight+30, lowFreq, highFreq);
    buzzerTone = constrain(buzzerTone, lowFreq, highFreq);
    tone(buzzerPin, buzzerTone);
  }
  else if(mode < 4){
    noTone(buzzerPin);
  }
  else if (mode < 6){
    buzzerTone = map(lightLevel, lowLight-30, highLight+30, lowFreq, highFreq); //opposite sound
    buzzerTone = constrain(buzzerTone, lowFreq, highFreq);
    tone(buzzerPin, buzzerTone);
  }
  else{
    noTone(buzzerPin);
  }
}

void buttonStuff(){  
  buttonState = digitalRead(buttonPin);
  if(buttonState == LOW)
  {
      wasPressed = true;
  }
  if(wasPressed && buttonState == HIGH)
  {
      mode = (mode  + 1) % 8;
      wasPressed = false;
  }
}

void lightStuff()
{
  if(mode == 0 || mode == 2){
    lightsOn = map(lightLevel, highLight-30, lowLight+30, 1, 6);
    lightsOn = constrain(lightsOn, 1, 6); 
    for(int i = 0; i < 6; i++)
    {
      
      if(i < lightsOn)
      {
        digitalWrite(ledPins[i], HIGH);
      }
      else
      {
        digitalWrite(ledPins[i], LOW);
      }
    }
  }
  else if(mode == 1 || mode == 3){
    ledIntensity = map(lightLevel, highLight-30, lowLight+30, 0, 255);//0-255 is range for PWM
    ledIntensity = constrain(ledIntensity, 0, 255);
    for(int i = 0; i < 6; i++)
    {
        analogWrite(ledPins[i], ledIntensity);
      
    }
    
  }
  
  else if(mode == 4 || mode == 6)
  {
    lightsOn = map(lightLevel, highLight-30, lowLight+30, 1, 6);
    lightsOn = constrain(lightsOn, 1, 6); 
    for(int i = 0; i < 6; i++)
    {
      
      if(i < 7 - lightsOn)
      {
        digitalWrite(ledPins[i], HIGH);
      }
      else
      {
        digitalWrite(ledPins[i], LOW);
      }
    }
  }
  else if(mode == 5 || mode == 7){
    ledIntensity = map(lightLevel, highLight-30, lowLight+30, 0, 255);//0-255 is range for PWM
    ledIntensity = constrain(ledIntensity, 0, 255);
    for(int i = 0; i < 6; i++)
    {
        analogWrite(ledPins[i], 255-ledIntensity);
      
    }
    
  }
  
  
}
