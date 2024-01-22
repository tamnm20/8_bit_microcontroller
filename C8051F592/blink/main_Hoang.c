#include <8051.h>

void delay(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 500; j++);
}

void main() {
    while (1) {
        P1 = P1 | 0x01;  // Bật LED (P1.0)
        //delay(1000);     // Trễ 1 giây

        P1 = P1 & 0xFE;  // Tắt LED
        //delay(1000);     // Trễ 1 giây
    }
}
