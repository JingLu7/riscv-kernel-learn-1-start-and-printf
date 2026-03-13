#define UART 0x10000000
#define LSR (UART + 5)

void uart_putc(char c) {
    volatile unsigned char *lsr = (unsigned char *)LSR;
    volatile unsigned char *thr = (unsigned char *)UART;

    while ((*lsr & 0x20) == 0) {
        /*八位的位运算*/
    }
    *thr = (unsigned char)c; //把字符发给0x10000000内存地址
}

void uart_puts(char *s) {
    while(*s){
        uart_putc(*s++);
    }
}