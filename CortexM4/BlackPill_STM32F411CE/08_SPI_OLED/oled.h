#ifndef _OLED_H
#define _OLED_H

#define OL_FNT_SMALL
#define OL_FNT_LARGE
#define OL_FNT_BIG
  
#define OL_LINE
#define OL_CIRCLE 

#define OL_SPI_PORT     SPI_1 //SPI1 veya SPI2 seciyoruz. 
#define SPI_Start(m)    HSPI_Start(OL_SPI_PORT, m)
#define SPI_Data(v)     HSPI_Data(OL_SPI_PORT, v)

typedef enum {
    FNT_SMALL,
    FNT_LARGE,
    FNT_BIG
} FNT_t;

typedef enum {
  CLR_PIXEL,
  SET_PIXEL,
  INV_PIXEL
} COLOR_t;

void OLED_Start(int bRotate);
void OLED_SetPage(unsigned char page);
void OLED_SetSegment(unsigned char segment);
void OLED_Data(unsigned char data);
void OLED_SetPage(unsigned char page);
void OLED_SetSegment(unsigned char segment);
void OLED_ClearDisplay(void);

void OLED_UpdateDisplay(void);
void OLED_Rotate(int bRotate);

COLOR_t OLED_GetPixel(int x, int y);
void OLED_SetPixel(int x, int y, COLOR_t c);
void OLED_Line(int x0, int y0, int x1, int y1, COLOR_t c);
void OLED_Circle(int x, int y, int r, COLOR_t c);

FNT_t OLED_GetFont(void);
void OLED_SetFont(FNT_t font);

void OLED_SetCursor(unsigned char row, unsigned char col);
void OLED_GetCursor(int *pRow, int *pCol);
void OLED_PutChar(char ch);

void OLED_putch(unsigned char c);

#endif
