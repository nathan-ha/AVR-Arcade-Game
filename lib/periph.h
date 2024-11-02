/*        Your Name & E-mail: Nathan Ha    nha023@ucr.edu

*          Discussion Section: 22

 *         Assignment: Final Project

 *         Description: Functions for physical devices go here

 *

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 */
#include <avr/interrupt.h>
#include <avr/io.h>
// #include <avr/signal.h>
#include <util/delay.h>

#include "spiAVR.h"

#ifndef PERIPH_H
#define PERIPH_H

////////// SONAR UTILITY FUNCTIONS ///////////

void init_sonar() {
  sei();                 /* Enable global interrupt */
  TIMSK1 = (1 << TOIE1); /* Enable Timer1 overflow interrupts */
  TCCR1A = 0;
}

// read_sonar function implmentation moved to timerISR.h file
// double read_sonar()

////////// ADC UTILITY FUNCTIONS ///////////

void ADC_init() {
  ADMUX = (1 << REFS0);
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  // ADEN: setting this bit enables analog-to-digital conversion.
  // ADSC: setting this bit starts the first conversion.
  // ADATE: setting this bit enables auto-triggering. Since we are
  //        in Free Running Mode, a new conversion will trigger whenever
  //        the previous conversion completes.
}

unsigned int ADC_read(unsigned char chnl) {
  uint8_t low, high;

  ADMUX = (ADMUX & 0xF8) | (chnl & 7);
  ADCSRA |= 1 << ADSC;
  while ((ADCSRA >> ADSC) & 0x01) {
  }

  low = ADCL;
  high = ADCH;

  return ((high << 8) | low);
}

////////// ADC AND SONAR UTILITY FUNCTIONS ///////////

// ****************************************************************************************************
// ******************************** PASSIVE BUZZER FUNCTIONS ******************************************
// ****************************************************************************************************

void pbuzzer_init() {
  TCCR1A |= (1 << WGM11) | (1 << COM1A1);               // COM1A1 sets it to channel A
  TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);  // CS11 sets the prescaler to be 8
  // WGM11, WGM12, WGM13 set timer to fast pwm mode
}

void pbuzzer_change_freq(short f) {
  ICR1 = 16000000 / (8 * f);  // 20ms pwm period
  OCR1A = ICR1 * 0.5;         // 50% duty cycle
}

// ****************************************************************************************************
// ******************************** IR REMOTE FUNCTIONS ******************************************
// ****************************************************************************************************



// ****************************************************************************************************
// ****************************************************************************************************
// ****************************************************************************************************
// ********************************* TFT DISPLAY COMMANDS *********************************************
// ****************************************************************************************************
// ****************************************************************************************************
// ****************************************************************************************************

// Function to send command to display
void TFT_SEND_COMMAND(char command) {
  PORTD &= ~(1 << PIN_A0);  // set A0 (DC) low for command mode
  // PORTB &= ~(1 << PIN_SS);  // select the tft display
  SPI_SEND(command);  // send command
  // PORTB |= (1 << PIN_SS);   // deselect the tft display
  PORTD |= (1 << PIN_A0);  // set A0 back to data mode
}

// Function to send data to display
void TFT_SEND_DATA(char data) {
  PORTD |= (1 << PIN_A0);  // set A0 (DC) high for data mode
  // PORTB &= ~(1 << PIN_SS);  // select the tft display
  SPI_SEND(data);  // send data
  // PORTB |= (1 << PIN_SS);   // deselect the tft display
}

// clears the display memory faster than writing one pixel at a time
void TFT_FLUSH() {
  TFT_SEND_COMMAND(0x2A);  // Set column address
  TFT_SEND_DATA(0x00);     // start column high byte
  TFT_SEND_DATA(0x00);     // start column low byte
  TFT_SEND_DATA(0x00);     // end column high byte
  TFT_SEND_DATA(131);      // end column low byte

  TFT_SEND_COMMAND(0x2B);  // Set row address
  TFT_SEND_DATA(0x00);     // start row high byte
  TFT_SEND_DATA(0x00);     // start row low byte
  TFT_SEND_DATA(0x00);     // end row high byte
  TFT_SEND_DATA(131);      // end row low byte

  TFT_SEND_COMMAND(0x2C);  // Memory write
  for (short i = 0; i < 131 * 131; i++) {
    TFT_SEND_DATA(0x00);  // Write black color data to clear the screen
    TFT_SEND_DATA(0x00);
  }
}

// draws rectangles faster than a nested for loop
// input is the two corners of the rectangle
// same logic as flush
void TFT_DRAW_RECTANGLE(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, short color) {
  TFT_SEND_COMMAND(0x2A);  // Set column address
  SPI_SEND(0x00);          // start column high byte
  SPI_SEND(x1);            // start column low byte
  SPI_SEND(0x00);          // end column high byte
  SPI_SEND(x2);            // end column low byte

  TFT_SEND_COMMAND(0x2B);  // Set row address
  SPI_SEND(0x00);          // start row high byte
  SPI_SEND(y1);            // start row low byte
  SPI_SEND(0x00);          // end row high byte
  SPI_SEND(y2);            // end row low byte

  TFT_SEND_COMMAND(0x2C);  // Memory write
  for (short i = 0; i < (x2 - x1) * (y2 - y1); i++) {
    SPI_SEND(color >> 4);  // honestly don't know why i have to shift it like this
    SPI_SEND(color << 4);  // datasheet doesn't mention it, but it's the only way it works
  }
}

// Function to initialize ST7735
void TFT_INIT() {
  SPI_INIT();

  DDRD |= 1 << PIN_A0;  // pin d7 output (A0)
  PORTD &= ~(1 << PIN_A0);
  // Reset the display
  PORTB &= ~(1 << PIN_RST);  // Reset low
  _delay_ms(10);             // Delay for reset
  PORTB |= (1 << PIN_RST);   // Reset high
  _delay_ms(10);             // Delay for reset

  // Initialize display
  // honestly not sure if we need but it can't hurt
  TFT_SEND_COMMAND(0x01);  // Software reset
  _delay_ms(10);

  TFT_SEND_COMMAND(0x11);  // wake up from slep
  _delay_ms(10);

  TFT_SEND_COMMAND(0x3A);  // pixel format
  TFT_SEND_DATA(0x03);     // 12-bit colors

  TFT_FLUSH();  // erase previous memory

  TFT_SEND_COMMAND(0x36);     // Memory Access Control
  TFT_SEND_DATA(0b01001000);  // MY = 0, MX (mirror x) = 1, MV = 0, ML = 0, RGB (instead of bgr) = 1, MH = 0

  // Set display on
  TFT_SEND_COMMAND(0x29);  // Display on
}

// draws pixels at the x y coords
void TFT_DRAW_PIXEL(unsigned char x, unsigned char y, short color) {
  TFT_SEND_COMMAND(0x2A);  // Set column address
  SPI_SEND(0x00);          // start column high byte
  SPI_SEND(x);             // start column low byte
  SPI_SEND(0x00);          // end column high byte
  SPI_SEND(x);             // end column low byte

  TFT_SEND_COMMAND(0x2B);  // Set row address
  SPI_SEND(0x00);          // start row high byte
  SPI_SEND(y);             // start row low byte
  SPI_SEND(0x00);          // end row high byte
  SPI_SEND(y);             // end row low byte

  // Set pixel color
  TFT_SEND_COMMAND(0x2C);  // Memory write
  SPI_SEND(color >> 4);    // honestly don't know why i have to shift it like this
  SPI_SEND(color << 4);    // I just used trial and error, but it has something to do with 12 bit rgb
}

// slow but actually uses the right color
void TFT_DRAW_RECTANGLE_SLOW(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, short color) {
  for (short x = x1; x < x2; x++) {
    for (short y = y1; y < y2; y++) {
      TFT_DRAW_PIXEL(x, y, color);
    }
  }
}

// ****************************************************************************************************

#endif /* PERIPH_H */