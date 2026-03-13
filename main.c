void uart_puts(char *s); //函数声明

void main(void) {
    uart_puts("hello my first kernel");

    while(1){
        ;
    }
}