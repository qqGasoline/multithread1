/*
 * Copyright (C) 2016 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Test for the on-board LED macros
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <stdint.h>
#include "xtimer.h"
#include "board.h"
#include "periph_conf.h"
#include "periph/gpio.h"
#include "thread.h"
//#include <string.h>

#ifdef CLOCK_CORECLOCK
#define DELAY_SHORT         (CLOCK_CORECLOCK / 50)
#else
#define DELAY_SHORT         (100000UL)
#endif
#define DELAY_LONG          (DELAY_SHORT * 4)
#define INTERVAL ((1U * US_PER_SEC))

void dumb_delay(uint32_t delay)
{
    for (uint32_t i = 0; i < delay; i++) {
        __asm__("nop");
    }
}

char stack[THREAD_STACKSIZE_MAIN/4];
char stack2[THREAD_STACKSIZE_MAIN/4];
/*
static void btn_handler(void *arg)

{

 (void)arg;
 
 gpio_write(GPIO_PIN(PORT_C, 8),1);
 dumb_delay(DELAY_LONG);
 gpio_write(GPIO_PIN(PORT_C, 8),0);
 dumb_delay(DELAY_LONG);
}
*/

void *thread1_handler(void *arg)
{
    (void)arg;
    xtimer_ticks32_t last_wakeup_one = xtimer_now();
    while(1){

        gpio_toggle(GPIO_PIN(PORT_C,8));
        xtimer_periodic_wakeup(&last_wakeup_one, 400000);


    }

    return NULL;
}

void *thread2_handler(void *arg)
{
    (void)arg;
    xtimer_ticks32_t last_wakeup_one = xtimer_now();
    while(1){

        gpio_toggle(GPIO_PIN(PORT_C,9));
        xtimer_periodic_wakeup(&last_wakeup_one, 1000000);

    }

    return NULL;
}


int main(void)
{
    

gpio_init(GPIO_PIN(PORT_C, 8), GPIO_OUT);
gpio_init(GPIO_PIN(PORT_C, 9), GPIO_OUT);
//gpio_init(GPIO_PIN(PORT_A,0),GPIO_IN);
//gpio_init(GPIO_PIN(PORT_A,0),GPIO_IN);
//gpio_init_int(GPIO_PIN(PORT_A, 0), GPIO_IN, GPIO_FALLING, btn_handler, NULL);

thread_create(stack,sizeof(stack),THREAD_PRIORITY_MAIN - 1,THREAD_CREATE_STACKTEST,thread1_handler,NULL,"thread1");
thread_create(stack2,sizeof(stack2),THREAD_PRIORITY_MAIN - 1,THREAD_CREATE_STACKTEST,thread2_handler,NULL,"thread2");



    //while (1) {
        /*
        if (gpio_read(GPIO_PIN(PORT_A,0)) == 1)
        {
            gpio_write(GPIO_PIN(PORT_C, 9),1);
            gpio_write(GPIO_PIN(PORT_C, 8),1);
        }
        else {
            gpio_write(GPIO_PIN(PORT_C, 9),0);
            gpio_write(GPIO_PIN(PORT_C, 8),0);
        }
        */
	//LED1_ON;
    //dumb_delay(DELAY_LONG);
	//gpio_toggle(GPIO_PIN(PORT_C, 8));
	//xtimer_periodic_wakeup(&last_wakeup, INTERVAL);
	//LED1_OFF;
	//gpio_clear(GPIO_PIN(PORT_C, 8));
	//xtimer_periodic_wakeup(&last_wakeup, INTERVAL);
	//}

    return 0;
}
