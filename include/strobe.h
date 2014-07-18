#define LED_R GPIO_PIN_1
#define LED_B GPIO_PIN_2
#define LED_G GPIO_PIN_3
#define LED_PURPLE (LED_R | LED_B & ~LED_G)
#define LED_CYAN (LED_B | LED_G & ~LED_R)
#define LED_YELLOW (LED_R | LED_G & ~LED_B)
#define LED_WHITE (LED_R | LED_B | LED_G)
#define LED_BLACK ~(LED_WHITE)

#define STROBE_SEQ_LEN 14
//#define STROBE_ENABLE ((SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5) | (GPIO_PORTF_DIR_R |= LED_WHITE) | (GPIO_PORTF_DR2R_R |= LED_WHITE) | (GPIO_PORTF_DEN_R |= LED_WHITE) | (GPIO_PORTF_LOCK_R |= GPIO_LOCK_KEY) | (GPIO_PORTF_CR_R |= LED_WHITE))	//Enable port F1-F3 for strobe status

void strobe(void);
void strobe_enable(void);
void strobe_disable(void);
void strobe_set_interval(unsigned long interval);
void strobe_pattern(int pattern_num);