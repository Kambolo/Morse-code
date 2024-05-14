#include <Arduino.h>
#include <string.h>
#include <LiquidCrystal.h> //Dołączenie bilbioteki

#define BUTTON 2
#define DIODA 3
#define BUZZER A5

LiquidCrystal lcd(4, 5, 6, 7, 8, 9); //Informacja o podłączeniu nowego wyświetlacza

bool startStatus = false;
bool wasAdded = false;

String lettersInCode[] = {
    ".-",
    "-...",
    "-.-.",
    "-..",
    ".",
    "..-.",
    "--.",
    "....",
    "..",
    ".---",
    "-.-",
    ".-..",
    "--",
    "-.",
    "---",
    ".--.",
    "--.-",
    ".-.",
    "...",
    "-",
    "..-",
    "...-",
    ".--",
    "-..-",
    "-.--",
    "--..",
};
char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

String code = "";
String text = "";

int startTime;
int pressedTime;
int count = 0;

int measureUnit = 150;

void addSign();
void convertToLetter();
void setStartTime();
int getPressedTime();
void updateLCD();

void setup()
{
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  Serial.begin(9600);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(DIODA, OUTPUT);
  pinMode(BUZZER, OUTPUT); 
}

void loop()
{
  if (digitalRead(BUTTON) == LOW)
  {
    setStartTime();
  }
  if (digitalRead(BUTTON) == HIGH)
  {
    pressedTime = getPressedTime();
  }

  if (!startStatus && !wasAdded)
  {
    addSign();
  }
  if (pressedTime > 3 && pressedTime < measureUnit)
  {
    count++;
    if (count == 2)
    {
      convertToLetter();
      count = 0;
    }
  }
  
}

void setStartTime()
{
  if (!startStatus)
  {
    startTime = millis();
    startStatus = true;
    digitalWrite(DIODA, HIGH);
    digitalWrite(BUZZER, HIGH);
  }
}

int getPressedTime()
{
  if (startStatus)
  {
    startStatus = false;
    wasAdded = false;
    digitalWrite(DIODA, LOW);
    digitalWrite(BUZZER, LOW);
    return millis() - startTime;
  }
  return -1;
}

void addSign()
{
  if (pressedTime >= measureUnit)
  {
    if (pressedTime < 3 * measureUnit)
    {
      code += '.';
      Serial.println(code);
    }
    else
    {
      code += '-';
      Serial.println(code);
    }
    wasAdded = true;
  }
}

void convertToLetter()
{
  for (int i = 0; i < 25; i++)
  {
    if (code == lettersInCode[i])
    {
      text += letters[i];
      Serial.println(text);
      updateLCD();
      code = "";
      return;
    }
  }
  code="";
}

void updateLCD(){
  lcd.clear();
  delay(50);
  lcd.print(text);
  delay(50);
}