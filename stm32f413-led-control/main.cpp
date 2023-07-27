#include "fonts.h"
#include "mbed.h"
#include "stm32f413h_discovery.h"
#include "stm32f413h_discovery_ts.h"
#include "stm32f413h_discovery_lcd.h"


TS_StateTypeDef TS_State = {0};

DigitalOut redLed(A0);
DigitalOut blueLed(A1);

int main()
{
    
    redLed = 0;
    blueLed = 0;

    uint16_t x1, y1;

    BSP_LCD_Init();

    /* Touchscreen initialization */
    if (BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize()) == TS_ERROR) {
        printf("BSP_TS_Init error\n");
    }

    /* Clear the LCD */
    BSP_LCD_Clear(LCD_COLOR_BLACK);

    /* Set Touchscreen Demo1 description */
    BSP_LCD_SetFont(&Font24);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_DisplayStringAt(0, 40, (uint8_t *)"Mavi Led", CENTER_MODE);
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(50, 85, (uint8_t *)"ON", LEFT_MODE);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(50, 85, (uint8_t *)"OFF", RIGHT_MODE);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(0, 135, (uint8_t *)"Kirmizi Led", CENTER_MODE);
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(50, 180, (uint8_t *)"ON", LEFT_MODE);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(50, 180, (uint8_t *)"OFF", RIGHT_MODE);


    while (1) {
        BSP_TS_GetState(&TS_State);

         if(TS_State.touchDetected){

            x1 = TS_State.touchX[0];
            y1 = TS_State.touchY[0];
            printf("Touch Detected x=%d y=%d\n", x1, y1);

            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_FillCircle(x1, y1, 5);

            if(x1 > 50 && x1 < 100 && y1 > 85 && y1 < 105){
                redLed = 1;
                printf("RED LED IS ON!");
            }else if(x1 > 140 && x1 < 195 && y1 > 85 && y1 < 105){
                redLed = 0;
                printf("RED LED IS OFF!");
            }else if(x1 > 50 && x1 < 85 && y1 > 180 && y1 < 200){
                blueLed = 1;
                printf("BLUE LED IS ON!");
            }else if(x1 > 130 && x1 < 185 && y1 > 180 && y1 < 200){
                blueLed = 0;
                printf("BLUE LED IS OFF!");
            }
        }
    }
}
