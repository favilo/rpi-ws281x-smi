//
// Created by psy on 07-08-21.
//

#include <stdbool.h>
#include <stdint.h>

#ifndef RPI_WS281X_SMI_SMILEDS_H
#define RPI_WS281X_SMI_SMILEDS_H

#if PHYS_REG_BASE == PI_4_REG_BASE // Timings for RPi v4 (1.5 GHz)
#define SMI_TIMING 10, 15, 30, 15  // 400 ns cycle time
#else                              // Timings for RPi v0-3 (1 GHz)
#define SMI_TIMING 10, 10, 20, 10  // 400 ns cycle time
#endif

#define LED_D0_PIN 8     // GPIO pin for D0 output
#define LED_NCHANS 16    // Number of LED channels (8 or 16)
#define LED_NBITS 24     // Number of data bits per LED
#define LED_PREBITS 4    // Number of zero bits before LED data
#define LED_POSTBITS 4   // Number of zero bits after LED data
#define BIT_NPULSES 3    // Number of O/P pulses per LED bit
#define CHAN_MAXLEDS 512 // Maximum number of LEDs per channel
#define REQUEST_THRESH 2 // DMA request threshold
#define DMA_CHAN 10      // DMA channel to use

// Length of data for 1 row (1 LED on each channel)
#define LED_DLEN (LED_NBITS * BIT_NPULSES)

// Transmit data type, 8 or 16 bits
#if LED_NCHANS > 8
#define TXDATA_T uint16_t
#else
#define TXDATA_T uint8_t
#endif

union color_t {
  uint32_t packed; // packed presentation
  struct           // component-wise representation
  {
    uint8_t b;
    uint8_t r;
    uint8_t g;
    uint8_t a;
  } component;
};

#ifdef __cplusplus
extern "C" {
#endif

void fail(char *s);
void terminate(int sig);

bool leds_init(int init_led_count);

TXDATA_T *leds_get_buffer();

void leds_set_pixel(uint8_t channel, uint16_t pixel, union color_t color);

void leds_send();

void leds_clear();

void test();

#ifdef __cplusplus
}
#endif

#endif // RPI_WS281X_SMI_SMILEDS_H
