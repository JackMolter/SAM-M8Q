#include <stdio.h>
#include <string.h> 

#include "pico/stdlib.h"

//#include "lwgps_opts.h"
#include "lwgps_opt.h"
#include "lwgps.h"
#include "GPS.h"

lwgps_t hgps;
uint8_t gps_dat[32];

/**
 * \brief           Dummy data from GPS receiver
 */
const char gps_rx_data[] = ""
                           "$GPRMC,183729,A,3907.356,N,12102.482,W,000.0,360.0,080301,015.5,E*6F\r\n"
                           "$GPRMB,A,,,,,,,,,,,,V*71\r\n"
                           "$GPGGA,183730,3907.356,N,12102.482,W,1,05,1.6,646.4,M,-24.1,M,,*75\r\n"
                           "$GPGSA,A,3,02,,,07,,09,24,26,,,,,1.6,1.6,1.0*3D\r\n"
                           "$GPGSV,2,1,08,02,43,088,38,04,42,145,00,05,11,291,00,07,60,043,35*71\r\n"
                           "$GPGSV,2,2,08,08,02,145,00,09,46,303,47,24,16,178,32,26,18,231,43*77\r\n"
                           "$PGRME,22.0,M,52.9,M,51.0,M*14\r\n"
                           "$GPGLL,3907.360,N,12102.481,W,183730,A*33\r\n"
                           "$PGRMZ,2062,f,3*2D\r\n"
                           "$PGRMM,WGS84*06\r\n"
                           "$GPBOD,,T,,M,,*47\r\n"
                           "$GPRTE,1,1,c,0*07\r\n"
                           "$GPRMC,183731,A,3907.482,N,12102.436,W,000.0,360.0,080301,015.5,E*67\r\n"
                           "$GPRMB,A,,,,,,,,,,,,V*71\r\n";



void gps_init() {
    // UART setup 
    uart_init(GPS_UART_ID, GPS_BAUD);

    gpio_set_function(GPS_UART_TX, GPIO_FUNC_UART);     // sets pins
    gpio_set_function(GPS_UART_RX, GPIO_FUNC_UART);
    uart_set_hw_flow(GPS_UART_ID, false, false);    // flow control

}

void gps_read_data(){
    uart_is_readable(GPS_UART_ID);
    uart_set_fifo_enabled(GPS_UART_ID, 1);
    while( 1 == (uart_is_readable(GPS_UART_ID))) { // either a 1 or 0
        sleep_ms(1);
    }
    while(1 != (uart_is_readable(GPS_UART_ID))) {
        uart_read_blocking(GPS_UART_ID, gps_dat, 2);
        uart_write_blocking(GPS_UART_ID, gps_dat, 2);
    }
    //uart_read_blocking(GPS_UART_ID, gps_dat, 32);

    sleep_ms(10);
    //uart_write_blocking(GPS_UART_ID, gps_dat, 32);
    printf("hi");
    printf("%x", gps_dat);
    printf("fuck");

}


int main() {
    stdio_init_all();
    sleep_ms(10000);
    gps_init();
    gps_read_data();
    /*
    lwgps_init(&hgps);

    /* Process all input data 
    lwgps_process(&hgps, gps_rx_data, strlen(gps_rx_data));

    /* Print messages 
    printf("Valid status: %d\r\n", hgps.is_valid);
    printf("Latitude: %f degrees\r\n", hgps.latitude);
    printf("Longitude: %f degrees\r\n", hgps.longitude);
    printf("Altitude: %f meters\r\n", hgps.altitude);
    */
    return 0;

}
   
