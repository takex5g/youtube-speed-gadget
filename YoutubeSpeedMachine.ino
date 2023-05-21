#include "Keyboard.h"

#define VOLUME_PIN A2
void setup()
{
  Keyboard.begin();
  pinMode(VOLUME_PIN, INPUT);
  Serial.begin(9600);
  delay(2000);
}

int currentSpeed = 0;
int targetSpeed = 0;
void loop()
{
  // input A2 serial
  int volumeValue = analogRead(VOLUME_PIN);
  delay(100);

  // volumeValueの閾値は変更の必要あり
  if (volumeValue <= 364)
  {
    targetSpeed = 0;
  }
  else if (volumeValue <= 473)
  {
    targetSpeed = 1;
  }
  else if (volumeValue <= 583)
  {
    targetSpeed = 2;
  }
  else if (volumeValue <= 695)
  {
    targetSpeed = 3;
  }
  else
  {
    targetSpeed = 4;
  }
  Serial.print(targetSpeed);
  Serial.print(" ");
  Serial.print(currentSpeed);
  Serial.print(" ");
  Serial.println(volumeValue);

  // targetSpeedがcurrentSpeedより大きいとき
  if (targetSpeed > currentSpeed)
  {
    // targetSpeedとcurrentSpeedの差分だけspeedUpKeyboardを実行する
    for (int i = 0; i < targetSpeed - currentSpeed; i++)
    {
      speedUpKeyboard();
    }
  }
  // targetSpeedがcurrentSpeedより小さいとき
  else if (targetSpeed < currentSpeed)
  {
    // targetSpeedとcurrentSpeedの差分だけspeedDownKeyboardを実行する
    for (int i = 0; i < currentSpeed - targetSpeed; i++)
    {
      speedDownKeyboard();
    }
  }
  // currentSpeedをtargetSpeedに更新する
  currentSpeed = targetSpeed;
}

void speedUpKeyboard()
{
  Keyboard.press(KEY_LEFT_SHIFT);
  delay(10);
  Keyboard.write('.');
  delay(80);
  Keyboard.releaseAll();
  delay(50);
}

void speedDownKeyboard()
{
  Keyboard.press(KEY_LEFT_SHIFT);
  delay(10);
  Keyboard.press(',');
  delay(80);
  Keyboard.releaseAll();
  delay(50);
}