#include "io.h"
#include "system.h"
#include "lcd.h"

// LCD mod�le 4-bit veri g�nderir
// (komut ya da karakter)
// Parametre de�erinin low 4-bitini g�nderir
// Low nibble
static void LCD_SendDataL(unsigned char c)
{
  // Senkron 4-bit paralel haberle�me
  
  // 1) Data Setup: Verinin haz�rlanmas�
  // DB4 = c<0>
  // DB5 = c<1>
  // DB6 = c<2>
  // DB7 = c<3>
  
  IO_Write(IOP_LCD_DB4, (c & 1) != 0);
  IO_Write(IOP_LCD_DB5, (c & 2) != 0);
  IO_Write(IOP_LCD_DB6, (c & 4) != 0);
  IO_Write(IOP_LCD_DB7, (c & 8) != 0);
  // Veriyi haz�rlad�ktan sonra verinin stabil hale gelmesi
  // i�in (veri yollar�nda) bekleme gerekebilir
  // Data setup hold time
  // DelayUs(5)
  
  // 2) Clock Generation: Verinin onaylanmas�
  // Clock hatt� 1 - 0 yap�lacak
  IO_Write(IOP_LCD_E, 1);
  DelayUs(3);   // Clock high time
  IO_Write(IOP_LCD_E, 0);
  
  DelayUs(100);   // Clock low time
}

// LCD mod�le 4-bit komut g�nderir
// Parametredeki de�eri low 4-biti komut
// olarak g�nderilir
static void LCD_SendCmdL(unsigned char c)
{
  IO_Write(IOP_LCD_RS, 0); // RS = 0 (komut modu)
  
  LCD_SendDataL(c);
}

// LCD mod�le 8-bit veri g�nderir
// Parametredeki de�eri 8-bit olarak g�nderilir
// G�nderilen veri karakter kodu ya da komut olabilir
// RS daha �nce set edilmeli
static void LCD_SendData(unsigned char c)
{
  LCD_SendDataL(c >> 4);        // High nibble
  LCD_SendDataL(c);             // Low nibble
}

// LCD mod�le 8-bit komut g�nderir
// Parametredeki de�eri 8-bit komut
// olarak g�nderilir
void LCD_SendCmd(unsigned char c)
{
  IO_Write(IOP_LCD_RS, 0); // RS = 0 (komut modu)
  
  LCD_SendData(c);
  DelayUs(100);
}

// LCD mod�le 8-bit karakter kodu g�nderir
// Parametredeki de�eri 8-bit ASCII karakter
// olarak g�nderilir
void LCD_PutChar(unsigned char c)
{
  IO_Write(IOP_LCD_RS, 1); // RS = 1 (karakter modu)
  
  LCD_SendData(c);
}

////////////////////////////////////////////////////////

// Ekran� temizler
void LCD_Clear(void)
{
  LCD_SendCmd(0x01);
  DelayMs(5);
}

void LCD_SetCursor(unsigned char curPos)
{
  LCD_SendCmd(0x80 | curPos);
}

void LCD_Enable(unsigned char ctl)
{
  ctl &= 0x07;
  LCD_SendCmd(0x08 | ctl);
}

// LCD mod�l� 4-bit aray�zle ba�lat�r
void LCD_Init(void)
{
  IO_Init(IOP_LCD_RS, IO_MODE_OUTPUT);
  IO_Init(IOP_LCD_E, IO_MODE_OUTPUT);
  IO_Init(IOP_LCD_DB4, IO_MODE_OUTPUT);
  IO_Init(IOP_LCD_DB5, IO_MODE_OUTPUT);
  IO_Init(IOP_LCD_DB6, IO_MODE_OUTPUT);
  IO_Init(IOP_LCD_DB7, IO_MODE_OUTPUT);
  
  DelayMs(100);  // !! Startup problemleri i�in gerekiyor!
  
  LCD_SendCmdL(0x03);   // 0011
  DelayMs(5);
  LCD_SendCmdL(0x03);   // 0011
  //DelayUs(101);
  
  LCD_SendCmd(0x32);
  LCD_SendCmd(0x28);    // N=1 F=0
  LCD_Enable(0);        // Display off
  
  // D�k�manda bir eksiklik var!
  // Asl�nda komut 0x01 g�nderildikten sonra 
  // 2 ms bekleme gerekiyor
  LCD_Clear();
  
  LCD_SendCmd(0x06);
  LCD_Enable(LCD_DISPLAY_ON);
}

// LCD mod�l printf destek fonksiyonu
void LCD_putch(unsigned char c)
{
  // Baz� �zel karakterlere �zel anlam kazand�raca��z
  
  switch (c) {
  case '\r':
    LCD_SetCursor(0);
    break;

  case '\n':
    LCD_SetCursor(0x40);
    break;

  case '\f':
    LCD_Clear();
    break;
    
  default:
    LCD_PutChar(c);
    break;
  }
}

