#include <LPC214X.H>

void delay(unsigned int ms); // Function to Generate delay

void pinWrite(int pinNo, int pinVal); // Function to write pin  

void portWrite(int portNo, unsigned char portVal); // Function to write port pin

int pinRead(int pinNo);  // Function to read state of pin
