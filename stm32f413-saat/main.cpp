#include "fonts.h"
#include "mbed.h"
#include "stm32f413h_discovery.h"
#include "stm32f413h_discovery_ts.h"
#include "stm32f413h_discovery_lcd.h"
#include <cstdint>
#include <cstdio>

TS_StateTypeDef  TS_State = {0};
Timer timer;
int saniye = 55;
int pageNum = 1;

void saniye_artir(){
    saniye++;
}

int main()
{
    uint16_t x1, y1;

    BSP_LCD_Init();
    timer.start();

    char* saat_ptr;
    char* dakika_ptr;
    char* saniye_ptr;

    int saat = 23;
    int dakika = 59;

    char h[2];
    char m[2];
    char s[2];

    sprintf(h, "%d", saat);
    saat_ptr = h;
    sprintf(m, "%d", dakika);
    dakika_ptr = m;
    sprintf(s, "%d", saniye);
    saniye_ptr = s;

    /* Touchscreen initialization */
    if (BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize()) == TS_ERROR) {
        printf("BSP_TS_Init error\n");
    }

    /* Clear the LCD */
    BSP_LCD_Clear(LCD_COLOR_WHITE);

    while (1) {

        printf("%d\n", pageNum);
        BSP_LCD_SetFont(&Font16);
        BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
        BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)"<SetClock>", CENTER_MODE);

        if(timer.read_ms() >= 1000){
            saniye_artir();
            timer.reset();
        }

        if(dakika < 10){
            BSP_LCD_SetFont(&Font24);
            if(saat < 10){
                BSP_LCD_DisplayStringAt(50, 110, (uint8_t *)"0", LEFT_MODE);
                BSP_LCD_DisplayStringAt(65, 110, (uint8_t *)saat_ptr, LEFT_MODE);
            }else{
                BSP_LCD_DisplayStringAt(50, 110, (uint8_t *)saat_ptr, LEFT_MODE);
            }
            BSP_LCD_DisplayStringAt(84, 110, (uint8_t *)":", LEFT_MODE);
            BSP_LCD_DisplayStringAt(100, 110, (uint8_t *)"0", LEFT_MODE);
            BSP_LCD_DisplayStringAt(115, 110, (uint8_t *)dakika_ptr, LEFT_MODE);
            BSP_LCD_DisplayStringAt(134, 110, (uint8_t *)":", LEFT_MODE);
            if(saniye<10){
                BSP_LCD_DisplayStringAt(150, 110, (uint8_t *)"0", LEFT_MODE);
                BSP_LCD_DisplayStringAt(165, 110, (uint8_t *)saniye_ptr, LEFT_MODE);
            }
            else{
                BSP_LCD_DisplayStringAt(150, 110, (uint8_t *)saniye_ptr, LEFT_MODE);
            }
        }else{
            BSP_LCD_SetFont(&Font24);
            if(saat < 10){
                BSP_LCD_DisplayStringAt(50, 110, (uint8_t *)"0", LEFT_MODE);
                BSP_LCD_DisplayStringAt(65, 110, (uint8_t *)saat_ptr, LEFT_MODE);
            }else{
                BSP_LCD_DisplayStringAt(50, 110, (uint8_t *)saat_ptr, LEFT_MODE);
            }
            BSP_LCD_DisplayStringAt(84, 110, (uint8_t *)":", LEFT_MODE);
            BSP_LCD_DisplayStringAt(100, 110, (uint8_t *)dakika_ptr, LEFT_MODE);
            BSP_LCD_DisplayStringAt(134, 110, (uint8_t *)":", LEFT_MODE);
            if(saniye<10){
                BSP_LCD_DisplayStringAt(150, 110, (uint8_t *)"0", LEFT_MODE);
                BSP_LCD_DisplayStringAt(165, 110, (uint8_t *)saniye_ptr, LEFT_MODE);
            }else{
                BSP_LCD_DisplayStringAt(150, 110, (uint8_t *)saniye_ptr, LEFT_MODE);
            }
        }

        BSP_LCD_SetFont(&Font16);
        BSP_LCD_DisplayStringAt(0, 200, (uint8_t *)"Kaydet", CENTER_MODE);

       if(pageNum == 2 ){
            BSP_LCD_SetFont(&Font24);
            BSP_LCD_DisplayStringAt(57,  80, (uint8_t *)"^", LEFT_MODE);
            BSP_LCD_DisplayStringAt(107,  80, (uint8_t *)"^", LEFT_MODE);
            BSP_LCD_SetFont(&Font20);
            BSP_LCD_DisplayStringAt(60,  150, (uint8_t *)"v", LEFT_MODE);
            BSP_LCD_DisplayStringAt(110,  150, (uint8_t *)"v", LEFT_MODE);
        }
        if(saniye == 60){
            BSP_LCD_Clear(LCD_COLOR_WHITE);
            dakika++;
            sprintf(m, "%d", dakika);
            dakika_ptr = m;
            saniye = 1;
        }
        if(dakika == 60){
            BSP_LCD_Clear(LCD_COLOR_WHITE);
            saat++;
            dakika = 0;
        }
        if(saat == 24){
            BSP_LCD_Clear(LCD_COLOR_WHITE);
            saat = 0;
        }
        if(saat == -1){
            BSP_LCD_Clear(LCD_COLOR_WHITE);
            saat = 23;
        }
        if(dakika == -1){
            BSP_LCD_Clear(LCD_COLOR_WHITE);
            dakika = 59;
            saat--;
        }

        sprintf(s, "%d", saniye);
        saniye_ptr = s;
        sprintf(m, "%d", dakika);
        dakika_ptr = m;
        sprintf(h, "%d", saat);
        saat_ptr = h;

        BSP_TS_GetState(&TS_State);
        if(TS_State.touchDetected) {
            /* Get X and Y position of the first touch post calibrated */
            x1 = TS_State.touchX[0];
            y1 = TS_State.touchY[0];
            printf("Touch Detected x=%d y=%d\n", x1, y1);

            BSP_LCD_FillCircle(x1, y1, 5);
            BSP_LCD_SetTextColor(LCD_COLOR_BLUE);

            if(x1 > 55 && x1 < 170 && y1 > 25 && y1 < 60){
                pageNum = 2;
                wait_ms(300);
                BSP_LCD_SetFont(&Font24);
            }

            if(x1 > 60 && x1 < 180 && y1 > 190 && y1 < 230){
                pageNum = 1;
                BSP_LCD_Clear(LCD_COLOR_WHITE);
            }
     
            if(pageNum == 2 && x1 > 60 && x1 < 75 && y1 > 75 && y1 < 110){
                //saati artır
                printf("saat 1 artirildi");
                wait_ms(100);
                saat++;
            }else if(pageNum == 2 && y1 > 140 && y1 < 175 && x1 > 60 && x1 <75){
                //saati azalt
                printf("saat 1 azaltildi");
                wait_ms(100);
                saat--;
            }else if(pageNum == 2 && x1> 110 && x1 < 125 && y1 > 75 && y1 < 110){
                //dakikayı artır
                printf("dakika 1 artirildi");
                wait_ms(100);
                dakika++;
            }else if(pageNum == 2 && x1 > 110 && x1 < 125 && y1 > 140 && y1 < 175){
                //dakikayı azalt
                printf("dakika 1 azaltildi");
                wait_ms(100);
                dakika--;
            }
        }
    }
}
