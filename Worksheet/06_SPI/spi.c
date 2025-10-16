#include <lpc21xx.h>
#include "lcd_16x2.h"

#define CS_LOW() IO0CLR = (1 << 10)  // P0.10 LOW for EEPROM select
#define CS_HIGH() IO0SET = (1 << 10) // P0.10 HIGH to deselect EEPROM

#define SPI_WREN 0x06  // Write enable command
#define SPI_WRITE 0x02 // Write data command
#define SPI_READ 0x03  // Read data command
#define SPI_RDSR 0x05  // Read status register
#define Mode_0 0x00    // SPI mode 0

#define LED1 (1 << 17) // LED1 at P0.17
#define LED2 (1 << 18) // LED2 at P0.18

void SPI_Init(void);
unsigned char SPI_Transfer(unsigned char data);
void EEPROM_WriteEnable(void);
void EEPROM_WriteByte(unsigned int addr, unsigned char data);
unsigned char EEPROM_ReadByte(unsigned int addr);
unsigned char EEPROM_ReadStatus(void);
void delay(unsigned int count);

int main()
{
    unsigned char readValue;
    unsigned char writeValue = 'b';

    lcd_init();
    SPI_Init();

    IODIR0 |= LED1 | LED2 | (1 << 10); // P0.17, P0.18, P0.10 as output
    CS_HIGH();
    IOSET0 = LED1 | LED2;

    EEPROM_WriteEnable();
    EEPROM_WriteByte(0x0000, writeValue);
    while (EEPROM_ReadStatus() & 0x01)
        ; // Wait for write to finish

    readValue = EEPROM_ReadByte(0x0000);
    lcd_data(readValue);

    if (readValue == writeValue)
    {
        IOCLR0 = LED1;
        IOSET0 = LED2;
        lcd_command(0xC0);
        lcd_string("Received");
    }
    else
    {
        IOCLR0 = LED2;
        IOSET0 = LED1;
        lcd_command(0xC0);
        lcd_string("Not Received");
    }

    while (1)
        ;
}

void SPI_Init(void)
{
    PINSEL0 |= (1 << 8) | (1 << 10) | (1 << 12) | (1 << 14); // P0.4, P0.5, P0.6 as SPI
    S0SPCCR = 8;                                             // SPI clock rate
    S0SPCR = (1 << 5) | Mode_0;                              // Master mode
}

unsigned char SPI_Transfer(unsigned char data)
{
    S0SPDR = data;
    while (!(S0SPSR & 0x80))
        ; // SPI Transfer complete flag
    return S0SPDR;
}

void EEPROM_WriteEnable(void)
{
    CS_LOW();
    SPI_Transfer(SPI_WREN);
    CS_HIGH();
}

void EEPROM_WriteByte(unsigned int addr, unsigned char data)
{
    CS_LOW();
    SPI_Transfer(SPI_WRITE);
    SPI_Transfer((addr >> 8) & 0xFF);
    SPI_Transfer(addr & 0xFF);
    SPI_Transfer(data);
    CS_HIGH();
    delay(5000);
}

unsigned char EEPROM_ReadByte(unsigned int addr)
{
    unsigned char value;
    CS_LOW();
    SPI_Transfer(SPI_READ);
    SPI_Transfer((addr >> 8) & 0xFF);
    SPI_Transfer(addr & 0xFF);
    value = SPI_Transfer(0x00);
    CS_HIGH();
    return value;
}

unsigned char EEPROM_ReadStatus(void)
{
    unsigned char status;
    CS_LOW();
    SPI_Transfer(SPI_RDSR);
    status = SPI_Transfer(0x00);
    CS_HIGH();
    return status;
}

void delay(unsigned int count)
{
    unsigned int i;
    for (i = 0; i < count; i++)
        ;
}
