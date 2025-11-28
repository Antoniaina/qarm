#include <stdint.h>

#define SYSCTL_BASE 0x400FE000
#define GPIOA_BASE 0x40004000
#define UART0_BASE 0x4000C000

#define SYSCTL_RCGC1 (*(volatile uint32_t *)(SYSCTL_BASE + 0x104))
#define SYSCTL_RCGC2 (*(volatile uint32_t *)(SYSCTL_BASE + 0X108))

#define GPIO_PORTA_AFSEL (*(volatile uint32_t *)(GPIOA_BASE + 0x420))
#define GPIO_PORTA_DEN (*(volatile uint32_t *)(GPIOA_BASE + 0x51C))

#define UART0_CTL (*(volatile uint32_t *)(UART0_BASE + 0x030))
#define UART0_IBRD (*(volatile uint32_t *)(UART0_BASE + 0x024))
#define UART0_FBRD (*(volatile uint32_t *)(UART0_BASE + 0x028))
#define UART0_DR (*(volatile uint32_t *)(UART0_BASE + 0x000))
#define UART0_FR (*(volatile uint32_t *)(UART0_BASE + 0x018))
#define UART0_LCRH (*(volatile uint32_t *)(UART0_BASE + 0x02C))

void uart_gpio_clock_enable(void) {
  SYSCTL_RCGC1 |= (1 << 0);
  SYSCTL_RCGC2 |= (1 << 0);

  for (volatile int i = 0; i < 100; i++) {
  }
}

void uart_gpio_init(void) {
  GPIO_PORTA_AFSEL |= (1 << 0) | (1 << 1);
  GPIO_PORTA_DEN |= (1 << 0) | (1 << 1);
}

void uart_init_registers(void) {
  UART0_CTL &= ~(1 << 0);

  UART0_IBRD = 27;
  UART0_FBRD = 8;

  UART0_LCRH = 0b01100000;

  UART0_CTL = (1 << 0) | (1 << 8) | (1 << 9);
}

void uart_putc(char c) {
  while (UART0_FR & (1 << 5)) {
  }

  UART0_DR = c;
}

void uart_print(const char *msg) {
  while (*msg != '\0') {
    uart_putc(*msg);
    msg++;
  }
}

int main(void) {
  uart_gpio_clock_enable();
  uart_gpio_init();
  uart_init_registers();

  uart_print("Hello world lty eeeh");

  while (1) {
  }
  return 0;
}
