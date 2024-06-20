#ifndef timer_h
#define timer_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class timer
{

public:
    timer(LiquidCrystal_I2C *lcd, bool isMessage);

    void setMinutes(int minutes);

    void setSeconds(int seconds);

    bool updateTime();

    void setMessage(String text);

    void setPause(long time);

private:
    LiquidCrystal_I2C* _lcd;
    void endMessage(long pause);
    void paddInt(int integer, String &lcdString);
    void updateProgressBar(unsigned long currentCount, unsigned long totalCount, int lineToPrint);
    void lcdPrint(String text, int x, int y, bool clear);    
    int _minutes = 0;
    bool _isMessage = false;
    String _message = "";
    int _seconds = 0;




};








#endif
