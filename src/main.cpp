#include <Arduino.h>
#include <string.h>

#define BUTTON 2
#define TEMPBUTTON 3

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

int measureUnit = 300;

void addSign();
void convertToLetter();
void setStartTime();
int getEndTime();

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(TEMPBUTTON, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(BUTTON) == LOW)
  {
    setStartTime();
  }
  if (digitalRead(BUTTON) == HIGH)
  {
    pressedTime = getEndTime();
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
  }
}

int getEndTime()
{
  if (startStatus)
  {
    startStatus = false;
    wasAdded = false;
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
      code = "";
      return;
    }
  }
}
