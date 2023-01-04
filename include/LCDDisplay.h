#include "mbed.h"
#include "SoftwareI2C.h" 
   
class LCDDisplay {   
private:
    uint8_t Adresse;//=0x3F;
    //DigitalOut *ok;
    //DigitalOut *nok;
    //PortOut *po;
    //DigitalIn *t;
    SoftwareI2C *i2c;
    uint8_t wert;
    public:
    /** Create LCD Instance
    */
    LCDDisplay(void);
    
    /** löscht das Display
    */
    void clear(void);

    /** Positioniert den Cursor
    * @param pos 0.. 0xF 1. Zeile, 0x40..0x4F 2. Zeile
    */
    void cursorpos(uint8_t pos);

    /** Print formattet
    * @param *format Formatstring
    * @param ... Variablenliste
    */
    int printf(const char *format, ...);
    
      /** Locate to a screen column and row
   *
   * @param column  The horizontal position from the left, indexed from 0
   * @param row     The vertical position from the top, indexed from 0
   */
    void locate(int column, int row);

    /** Clear the screen and locate to 0,0 */
    void cls();
    /** Write a character to the LCD
    *
    * @param c The character to write to the display
    */
    void putc(int c);


private:
    void warte(void);
    void sendeByte(char b,uint8_t rw, uint8_t rs );
    void sendeNippel(char b,uint8_t rw, uint8_t rs );
    void init(void);

};
