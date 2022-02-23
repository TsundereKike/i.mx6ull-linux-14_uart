#include "imx6u.h"
#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_exti.h"
#include "bsp_epit.h"
static unsigned char led_state = OFF;
int main(void)
{
    int_init();
    imx6u_clk_init();
    clk_enable();
    delay_init();
    led_init();
    beep_init();
    key_init();
    exti_init();
    epit1_init(0,66000000/100);/*初始化定时器1,1分频66MHz,定时时间为10ms,用于按键消抖*/
    while(1)
    {
        led_state = !led_state;
        led_switch(LED0,led_state);
        delay_ms(100);
    }
    return 0;
}
