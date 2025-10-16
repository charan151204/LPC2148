// Delay in seconds
void delay_sec(unsigned int sec) {
    T0PR = 15000000 - 1;        // Set prescaler to generate 1-second tick (15 MHz / 15,000,000 = 1 Hz)
    T0TCR = 0x01;               // Enable timer and prescaler
    while (T0TC < sec);         // Wait until timer counter reaches 'sec'
    T0TCR = 0x03;               // Reset timer and counter
    T0TCR = 0x00;               // Disable timer
}

// Delay in milliseconds
void delay_millisec(unsigned int millisec) {
    T0PR = 15000 - 1;           // Set prescaler to generate 1 ms tick (15 MHz / 15,000 = 1 kHz)
    T0TCR = 0x01;               // Start timer
    while (T0TC < millisec);    // Wait until timer reaches 'millisec'
    T0TCR = 0x03;               // Reset timer
    T0TCR = 0x00;               // Stop timer
}

// Delay in microseconds
void delay_ms(unsigned int ms) {	
    T0PR = 15 - 1;              // Set prescaler for 1 ?s tick (15 MHz / 15 = 1 MHz)
    T0TCR = 0x01;               // Start timer
    while (T0TC < ms);          // Wait until timer reaches 'ms'
    T0TCR = 0x03;               // Reset timer
    T0TCR = 0x00;               // Stop timer
}

