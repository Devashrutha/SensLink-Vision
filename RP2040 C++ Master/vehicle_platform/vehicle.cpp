#include <math.h>
#include <vector>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/uart.h"

#include "drivers/st7735/st7735.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"


using namespace pimoroni;
using namespace std;

#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define MAX_BUFFER_SIZE 64

char buffer[MAX_BUFFER_SIZE];
volatile size_t buffer_index = 0;
volatile bool reception_complete = false;
char * altitude;
char * temperature;
char * IMU_PTH;
char * IMU_ROL;
size_t alt_index_start = 0;
size_t alt_length = 10;
size_t tmp_index_start = 11;
size_t tmp_length = 9;
size_t IMU_PTH_index_start = 21;
size_t IMU_PTH_length = 8;
size_t IMU_ROL_index_start = 30;
size_t IMU_ROL_length = 11;

void uart_rx_interrupt_handler();
void uart_irq_handler(){
  uart_rx_interrupt_handler();
}

void uart_rx_interrupt_handler(){
  while(uart_is_readable(UART_ID)){
    char received_char = uart_getc(UART_ID);

    if(!reception_complete && buffer_index < MAX_BUFFER_SIZE -1 ){
      buffer[buffer_index++]= received_char;
    }
  }

    if(!reception_complete && buffer_index >= MAX_BUFFER_SIZE -1 ){
      buffer[buffer_index]= '\0';
      reception_complete = true;
  } 

}

ST7735 st7735(160, 80, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenP8 graphics(st7735.width, st7735.height, nullptr);
Point pos_ALT(0,0);
Point pos_TMP(0,15);
Point pos_PTH(0,30);
Point pos_ROL(0,45);
Point pos_LOGO_MAIN(5,25);
Point pos_LOGO_SUB(45,55);
int main() {

stdio_init_all();

uart_init(UART_ID, BAUD_RATE);
gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
gpio_pull_up(UART_RX_PIN);
uart_set_irq_enables(UART_ID, true, false);
irq_set_exclusive_handler(UART_ID == uart0 ? UART0_IRQ : UART1_IRQ, reinterpret_cast<irq_handler_t>(uart_irq_handler));
irq_set_enabled(UART_ID == uart0 ? UART0_IRQ : UART1_IRQ, true);

uint8_t WHITE = graphics.create_pen(255, 255, 255);
uint8_t RED   = graphics.create_pen(255,0,0);
uint8_t BLACK = graphics.create_pen(0,0,0);

graphics.set_pen(BLACK);
Rect box(0,0,160,80);
graphics.rectangle(box);
graphics.set_pen(RED);
graphics.text("VISION",pos_LOGO_MAIN,10,5);
graphics.text("SENS",pos_LOGO_SUB,10,3);
st7735.update(&graphics);
sleep_ms(4000);

  while(true) {
        graphics.set_pen(BLACK);
        Rect box(0,0,160,80);
        graphics.rectangle(box);
        graphics.set_pen(RED);
        if(reception_complete){
          string str(buffer, sizeof(buffer)-1);
          string str_altitude = str.substr(alt_index_start,alt_length);
          string str_temperature = str.substr(tmp_index_start,tmp_length);
          string str_IMU_PTH = str.substr(IMU_PTH_index_start,IMU_PTH_length);
          string str_IMU_ROL = str.substr(IMU_ROL_index_start,IMU_ROL_length);
          altitude = str_altitude.data();
          temperature = str_temperature.data();
          IMU_PTH = str_IMU_PTH.data();
          IMU_ROL = str_IMU_ROL.data();
          graphics.text(altitude,pos_ALT,20,2);
          graphics.text(temperature,pos_TMP,20,2);
          graphics.text(IMU_PTH,pos_PTH,20,2);
          graphics.text(IMU_ROL,pos_ROL,20,2);
          buffer_index = 0;
          reception_complete = false;
          sleep_ms(500);
          st7735.update(&graphics);
          
        }
        tight_loop_contents();
    
  }

  return 0;
}