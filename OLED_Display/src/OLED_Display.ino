/*
 * Project OLED_Display
 * Description:
 * Author:
 * Date:
 */

#include <oled-wing-adafruit.h>
#include <OLED_Display_128X64.h>
// OledWingAdafruit oled;
SeeedOLED oled;


void setup() {
  Wire.begin();  
  oled.init();                      // Initialze SSD 
  
  1306 OLED display
  oled.clearDisplay();              // Clear screen
  oled.clearDisplay();              // Clear screen
  oled.setTextXY(0,0);              // Set cursor position, start of line 0
  oled.putString("IoT Classroo






  
  oled.setTextXY(1,0);              // Set cursor position, start of line 1
  oled.putString("Soil Monitor");
  oled.setTextXY(2,0);              // Set cursor position, start of line 2
  oled.putString("Moisture = ");
  oled.setTextXY(2,12);             // Set cursor position, line 2 10th character
  oled.putString("TEST");
}

void loop() {}

/*void setup()
{
   oled.setup(); 
    // Clear the buffer.
    oled.clearDisplay();
    oled.display();
}
void loop()
{
    displayVoltage();
    delay(3*1000);
}
void displayVoltage(){
    oled.clearDisplay();
    oled.setTextSize(0);
    oled.setTextColor(WHITE);
    oled.setCursor(0,0);
    float voltage = analogRead(BATT) * 0.0011224;
    oled.print(voltage);
    oled.display();
} */