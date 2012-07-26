#include "stm32f4xx.h"
#include "utility.h"



Coordinate * position;
uint8_t Pen_Pressed;
uint8_t tmp[10];
uint8_t LCD_Direccion = Apaisada; 	//PMode=1;  /* Variable Pmode=1 Portrait Vertical,
//Pmode=1 Landscape Apaisada*/



int main(void)
{

    SystemStart();
    Delay(0x3FFFFF);
    TouchPanel_Calibrate();
    LCD_Clear(MAGENTA);
    while(1)
    {
        //Delay(0x3FFFFF);
        //LCD_Button(10, 10, 100, 100, 0,"TEST BOTON", RED, BLUE);
        //LCD_RadioButton(200, 200, 0, BLUE);
        //LCD_Clear(BLUE);
        //getDisplayPoint(&display, Read_Ads7846(), &matrix ) ;
        //Pen_Pressed=LCD_TouchRead(&display);//lee la posición del puntero sobre la pantalla
        //TP_DrawPoint(display.x,display.y);
    }
}


