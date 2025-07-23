#include<dsk6713.h>
#include<dsk6713_led.h>
#include<dsk6713_dip.h>

int main() {
    DSK6713_init();
    DSK6713_LED_init();
    DSK6713_DIP_init();

    while(1){
        DSK6713_LED_toggle(2);

        if(DSK6713_DIP_get(3) == 0){
            DSK6713_LED_on(3);
        }else {
            DSK6713_LED_off(3);
        }
        DSK6713_waitusec(200000);
    }
}
