
#lcdProgressBar

This is a simple library that adds a timer with a progress bar. This timer can be anywhere from 1 hour or less. The bar scales with the time.


## Usage/Examples

```c++
#include <timer.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
timer countDown(&lcd, true) //lcd object, message bool.

void setup()
{
    //Default lcd functions to initialize.
    lcd.init();
    lcd.backlight();

    //Functions from library
    countDown.setMessage("Time is up"); //Message to display at end. This is optional and will only play if message bool is true.
    countDown.setDelay(3000); //Sets the length of time the complete message displays until it clears from the screen.
    countDown.setMinutes(1); //Set the time in minutes. Can go up to 1 hour.
    countDown.setSeconds(40); //Sets the time in seconds. If only 59 seconds are needed, use setMinutes instead.
    bool isDone = countDown.updateTime(); //This is the main method for updating the lcd with the time and progress bar.

}