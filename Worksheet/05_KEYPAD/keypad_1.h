#include <LPC214x.h>


// Row and column pins
#define R0 (1<<0)
#define R1 (1<<1)
#define R2 (1<<2)
#define R3 (1<<3)

#define C0 (1<<5)
#define C1 (1<<6)
#define C2 (1<<7)
#define C3 (1<<8)

unsigned char key_scan(void);

unsigned char key[4][4] = {
    {'7','8','9','A'},
    {'4','5','6','B'},
    {'1','2','3','C'},
    {'*','0','#','D'}
};

unsigned char key_scan(void)
{
    unsigned char row=0, col=0;
    unsigned char key_found = 0;

    // Rows = output
    IODIR0 |= R0|R1|R2|R3;
    // Columns = input
    IODIR0 &= ~(C0|C1|C2|C3);

    while(!key_found)
    {
        IOSET0 = R0|R1|R2|R3;  // Set all rows HIGH

        // Wait for key press
        if (!(IOPIN0 & (C0|C1|C2|C3)))
        {
            for(row=0; row<4; row++)
            {
                IOSET0 = R0|R1|R2|R3;
                IOCLR0 = (1<<row);  // Drive current row LOW

                if (!(IOPIN0 & C0)) { col=0; key_found=1; break; }
                if (!(IOPIN0 & C1)) { col=1; key_found=1; break; }
                if (!(IOPIN0 & C2)) { col=2; key_found=1; break; }
                if (!(IOPIN0 & C3)) { col=3; key_found=1; break; }
            }
        }
    }

    // Wait until key release
    while (!(IOPIN0 & (C0|C1|C2|C3)));

    return key[row][col];
}



