#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <timer.h>

// Credits
// Progressbar code: Bob Syers @youtube


timer::timer(LiquidCrystal_I2C *lcd, bool isMessage)
{
    _lcd = lcd;
    _isMessage = isMessage;
}

void timer::lcdPrint(String text, int x, int y, bool clear=false)
{
    if(clear)
    {
        _lcd->clear();
    }

    int rowOffSet = (x > 0) ? x-=1: x;
    int elevationOffSet = (y > 0) ? y-=1: y;
    
    _lcd->setCursor(elevationOffSet, rowOffSet);
    _lcd->print(text);
}

void timer::paddInt(int integer, String &lcdString)
{
    lcdString = (integer < 10) ? "0" + String(integer): String(integer);
}

void timer::setMinutes(int minutes)
{
    _minutes = minutes;
}

void timer::setSeconds(int seconds)
{
    _seconds = seconds;
}

void timer::updateProgressBar(unsigned long currentCount, unsigned long totalCount, int lineToPrint)
{
    byte zero[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
    byte one[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};
    byte two[] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
};
    byte three[] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
};
    byte four[] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
};
    byte five[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

    double factor = totalCount / 80.0;
    int percent = (currentCount + 1) / factor;
    int number = percent / 5;
    int remainder = percent % 5;

    if(number > 0)
    {
        _lcd->setCursor(number - 1, lineToPrint);
        _lcd->write(5);
    }
    _lcd->setCursor(number, lineToPrint);
    _lcd->write(remainder);


}

void timer::setMessage(String text)
{
    _message = text;
}

void timer::endMessage(long pause)
{
    lcdPrint(_message, 1, 1, true);
    delay(pause);
}

bool timer::updateTime()
{
    _lcd->setCursor(0, 0);
    String paddedMinute, paddedSecond, paddedPercent;
    String timeString;
    int privateSeconds = _seconds;
    int privateMinutes = _minutes;
    int totalSeconds = (privateMinutes * 60) + privateSeconds;
    int currentSeconds = 0;

    unsigned long startMillis = millis();
    unsigned long currentMillis = startMillis;
    while(currentMillis - startMillis <= totalSeconds * 1000UL) {
        if(currentMillis - startMillis >= (currentSeconds + 1) * 1000UL) {
            currentSeconds++;
            privateSeconds--;
            if(privateSeconds < 0) {
                privateMinutes--;
                privateSeconds = 59;
            }
            paddInt(privateMinutes, paddedMinute);
            paddInt(privateSeconds, paddedSecond);
            timeString = paddedMinute + ":" + paddedSecond;
            lcdPrint(timeString, 1, 1);
            updateProgressBar(currentSeconds, totalSeconds, 1);
        }
        currentMillis = millis();
    }
    if(_isMessage)
    {
        endMessage(3000);
    }
    return true;
}