/**************************************************************************************************
    (C) COPYRIGHT, Himax Technologies, Inc. ALL RIGHTS RESERVED
    ------------------------------------------------------------------------
    File        : main.c
    Project     : WEI
    DATE        : 2018/10/01
    AUTHOR      : 902452
    BRIFE       : main function
    HISTORY     : Initial version - 2018/10/01 created by Will
    			: V1.0			  - 2018/11/13 support CLI
**************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "embARC.h"
#include "embARC_debug.h"
#include "board_config.h"
#include "arc_timer.h"
#include "hx_drv_spi_s.h"
#include "spi_slave_protocol.h"
#include "hardware_config.h"

#include "hx_drv_uart.h"
#define uart_buf_size 100

DEV_UART * uart0_ptr;
char uart_buf[uart_buf_size] = {0};

#include "tflitemicro_algo.h"
#include "model_settings.h"
#include "test_samples.h"

#include "tools.h"

char uart_buf[100];
//int8_t input_buf[kImageSize] = {0};
uint32_t arr_std[480] = {0};
uint32_t idx[11] = {0};
uint8_t tt[3] = {123, 132, 213};

int main(void)
{    
    //UART 0 is already initialized with 115200bps
	printf("This is myProject\r\n");

    uart0_ptr = hx_drv_uart_get_dev(USE_SS_UART_0);

    int test_i = 0;
    int test_j = 0;
    int test_correct = 0;
    // int test_result = 0;
    int8_t* test_result;
    
    sprintf(uart_buf, "TFLM Start\r\n");    
    uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
        board_delay_ms(10);

    //tflitemicro_algo_init();
    /*
    for(test_j = 0; test_j < kImageSize; test_j ++)
        input_buf[test_j] = test_samples[0].image[test_j];
    test_result = tflitemicro_algo_run(&input_buf[0]);
    */
    sprintf(uart_buf, "test_result: %2d\r\n", *test_result);
    uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
        board_delay_ms(10);

    sprintf(uart_buf, "test_std: %u\r\n", std(&tt[0], 3));
    uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
        board_delay_ms(10);
    
    sprintf(uart_buf, "test_std: %u\r\n", row_std(&image[479*640], 640, 3));
    uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
        board_delay_ms(10);
    
    uint16_t j;
    for(j = 0; j < 480; j++) {
        arr_std[j] = row_std(&image[j*640], 640, 3);
        /*
        sprintf(uart_buf, "arr_std[%u]: %u\r\n", j, arr_std[j]);
        uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
            board_delay_ms(10);
        */
    }

    find_local_minimum(&arr_std[0], &idx[0], 480);

    sprintf(uart_buf, "idx = [");
    uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
        board_delay_ms(10);
    for(j = 0; j < 9; j++) {
        sprintf(uart_buf, "%u, ", idx[j]);
        uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
            board_delay_ms(10);
    }
    sprintf(uart_buf, "%u]\r\n", idx[j]);
    uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
        board_delay_ms(10);

    /*
    for(test_i = 0; test_i < kNumSamples; test_i ++)
    {
        for(test_j = 0; test_j < kImageSize; test_j ++)
            input_buf[test_j] = (test_samples[test_i].image[test_j] <= 210) ? -128 : 127;

        sprintf(uart_buf, "Test Number: %2d\r\n", test_i);
        uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
            board_delay_ms(10);

        test_result = tflitemicro_algo_run(&input_buf[0]);

        sprintf(uart_buf, "Ans_Num: %2d, TFLM_Num: %2d\r\n", test_samples[test_i].label, test_result);
        uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
            board_delay_ms(10);

        sprintf(uart_buf, "Ans_Char: %s, TFLM_Char: %s\r\n\n", kCategoryLabels[test_samples[test_i].label], kCategoryLabels[test_result]);
        uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
            board_delay_ms(10);
        
        if(test_samples[test_i].label == test_result)
            test_correct ++;

        board_delay_ms(300); 
    }
    
    sprintf(uart_buf, "\nCorrect Rate: %2d / %2d\r\n", test_correct, test_i);
    uart0_ptr->uart_write(uart_buf, strlen(uart_buf));
        board_delay_ms(10);
    */
    while(1);

	return 0;
}

