#include "fonts.h"
#include "stm32f413h_discovery.h"
#include "stm32f413h_discovery_ts.h"
#include "stm32f413h_discovery_lcd.h"
#include <cstdio>
#include <cmath>
using namespace std;

TS_StateTypeDef  TS_State = {0};

void mainScreen(){
    /* Clear the LCD */
        BSP_LCD_Clear(LCD_COLOR_BLACK);
        BSP_LCD_SetFont(&Font24);
        /* Set Touchscreen Demo1 description */
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_FillRect(38.75, 70, 30, 30);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(45, 75, (uint8_t *)"1", LEFT_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_FillRect(107.5, 70, 30, 30);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(5, 75, (uint8_t *)"2", CENTER_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_FillRect(176.25, 70, 30, 30);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(37, 75, (uint8_t *)"3", RIGHT_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_FillRect(38.75, 110, 30, 30);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(45, 115, (uint8_t *)"4", LEFT_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_FillRect(107.5, 110, 30, 30);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(5, 115, (uint8_t *)"5", CENTER_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_FillRect(176.25, 110, 30, 30);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(37, 115, (uint8_t *)"6", RIGHT_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);   
        BSP_LCD_FillRect(38.75, 150, 30, 30);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(45, 155, (uint8_t *)"7", LEFT_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);   
        BSP_LCD_FillRect(107.5, 150, 30, 30);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(5, 155, (uint8_t *)"8", CENTER_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_FillRect(176.25, 150, 30, 30);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(37, 155, (uint8_t *)"9", RIGHT_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_FillRect(107.5, 190, 30, 30);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(5, 195, (uint8_t *)"0", CENTER_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_FillRect(176.25, 190, 30, 30);
        BSP_LCD_SetFont(&Font16);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
        BSP_LCD_DisplayStringAt(30, 197, (uint8_t *)"->", RIGHT_MODE);
}

int main()
{
    uint16_t x1, y1;

    BSP_LCD_Init();

    /* Touchscreen initialization */
    if (BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize()) == TS_ERROR) {
        printf("BSP_TS_Init error\n");
    }    

    mainScreen();
    int pageNum = 1;
    int password = 0;
    int pass = 1234;
    int i = 0;
    int c = 3;

    while (1) {
        BSP_TS_GetState(&TS_State);
        printf("PageNum: %d\n",pageNum);
        for( i=0;i<900000;i++){}
        if(TS_State.touchDetected) {
            /* Get X and Y position of the first touch post calibrated */
            x1 = TS_State.touchX[0];
            y1 = TS_State.touchY[0];
            printf("Touch Detected x=%d y=%d\n", x1, y1);

            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_FillCircle(x1, y1, 5);

            if(pageNum == 1){
                mainScreen();
                if(x1 > 35 && x1 < 70 && y1 > 70 && y1 < 100){
                    printf("1\t");
                    BSP_LCD_SetFont(&Font24);
                    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
                    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                    BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"1", CENTER_MODE);
                    BSP_LCD_ReadPixel(0, 25);
                    password = password + pow(10.0, c) * 1;
                    c--;
                    printf("Password: %d", password);
                }else if(x1 > 120 && x1 < 135 && y1 > 70 && y1 < 100){
                    printf("2\t");
                    BSP_LCD_SetFont(&Font24);
                    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
                    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                    BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"2", CENTER_MODE);
                    password = password + pow(10.0, c) * 2;
                    c--;
                    printf("Password: %d", password);
                }else if(x1 > 170 && x1 < 220 && y1 > 70 && y1 < 100){
                    printf("3\t");
                    BSP_LCD_SetFont(&Font24);
                    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
                    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                    BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"3", CENTER_MODE);
                    password = password + pow(10.0, c) * 3;
                    c--;
                    printf("Password: %d", password);
                }else if(x1 > 35 && x1 < 70 && y1 > 105 && y1 < 135){
                    printf("4\t");
                    BSP_LCD_SetFont(&Font24);
                    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
                    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                    BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"4", CENTER_MODE);
                    password = password + pow(10.0, c) * 4;
                    c--;
                    printf("Password: %d", password);
                }else if(x1 > 120 && x1 < 135 && y1 > 105 && y1 < 135){
                    printf("5\t");
                    BSP_LCD_SetFont(&Font24);
                    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
                    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                    BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"5", CENTER_MODE);
                    password = password + pow(10.0, c) * 5;
                    c--;
                    printf("Password: %d", password);
                }else if(x1 > 170 && x1 < 220 && y1 > 105 && y1 < 135){
                    printf("6\t");
                    BSP_LCD_SetFont(&Font24);
                    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
                    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                    BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"6", CENTER_MODE);
                    password = password + pow(10.0, c) * 6;
                    c--;
                    printf("Password: %d", password);
                }else if(x1 > 35 && x1 < 70 && y1 > 135 && y1 < 180){
                    printf("7\t");
                    BSP_LCD_SetFont(&Font24);
                    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
                    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                    BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"7", CENTER_MODE);
                    password = password + pow(10.0, c) * 7;
                    c--;
                    printf("Password: %d", password);
                }else if(x1 > 120 && x1 < 135 && y1 > 135 && y1 < 180){
                    printf("8\t");
                    BSP_LCD_SetFont(&Font24);
                    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
                    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                    BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"8", CENTER_MODE);
                    password = password + pow(10.0, c) * 8;
                    c--;
                    printf("Password: %d", password);
                }else if(x1 > 170 && x1 < 220 && y1 > 135 && y1 < 180){
                    printf("9\t");
                    BSP_LCD_SetFont(&Font24);
                    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
                    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                    BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"9", CENTER_MODE);
                    password = password + pow(10.0, c) * 9;
                    c--;
                    printf("Password: %d", password);
                }else if(x1 > 120 && x1 < 135 && y1 > 180 && y1 < 225){
                    printf("0\t");
                    BSP_LCD_SetFont(&Font24);
                    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
                    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);            
                    BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"0", CENTER_MODE);
                    password = password + pow(10.0, c) * 0;
                    c--;
                    printf("Password: %d", password);
                }else if(x1 > 170 && x1 < 210 && y1 > 180 && y1 < 225){
                    printf("ENTER\t");
                    BSP_LCD_Clear(LCD_COLOR_BLACK);
                    pageNum = 2;
                }
            }
            if(pageNum == 2){
                BSP_LCD_SetFont(&Font20);
                BSP_LCD_Clear(LCD_COLOR_BLACK);
                BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
                BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
                if(pass == password){
                    BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"Sifre Dogru!", CENTER_MODE);
                    printf("Password: %d", password);
                }else{
                    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
                    BSP_LCD_SetBackColor(LCD_COLOR_RED);
                    BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"Tekrar Deneyin!", CENTER_MODE);
                    printf("Password: %d", password);
                }
                BSP_LCD_SetTextColor(LCD_COLOR_RED);
                BSP_LCD_FillCircle(120, 150, 20);
                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
                BSP_LCD_SetBackColor(LCD_COLOR_RED);
                BSP_LCD_SetFont(&Font20);
                BSP_LCD_DisplayStringAt(0, 142, (uint8_t *)"<-", CENTER_MODE);   
                password = 0;
                c = 3;
            }
            if(x1 > 100 && x1 < 140 && y1 > 130 && y1 < 175){
                pageNum = 1;
            }
        }
    }
}
