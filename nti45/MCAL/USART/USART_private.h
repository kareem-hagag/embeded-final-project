#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

#define UDR     *((volatile u8*)0x2C)
#define UCSRA   *((volatile u8*)0x2B)
#define UCSRB   *((volatile u8*)0x2A)
#define UCSRC   *((volatile u8*)0x40)
#define UBRRH   *((volatile u8*)0x40)
#define UBRRL   *((volatile u8*)0x29)

#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0

#define ASYNC_MODE     0
#define SYNC_MODE      1

#define PARITY_DISABLE 0
#define EVEN_PARITY    1
#define ODD_PARITY     2

#define ONE_STOP_BIT   0
#define TWO_STOP_BIT   1

#define DATA_5_BIT     0
#define DATA_6_BIT     1
#define DATA_7_BIT     2
#define DATA_8_BIT     3
#define DATA_9_BIT     4

#define NORMAL_SPEED   0
#define DOUBLE_SPEED   1

#define FALLING_EDGE   0
#define RISING_EDGE    1

#endif
