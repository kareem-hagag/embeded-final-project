/*************************************************************/
/************ Auther : kareem hagag ******************/
/************ date : 29/7/2026 ******************/
/************ Title: configration file ********************/
/**************************************************************/
#ifndef DIO_CONFIG_H
#define DIO_CONFIG_H
#define CONC(B7,B6,B5,B4,B3,B2,B1,B0)        0b##B7##B6##B5##B4##B3##B2##B1##B0
#define CONC_BIT(B7,B6,B5,B4,B3,B2,B1,B0)    CONC(B7,B6,B5,B4,B3,B2,B1,B0)
/****************** all ports of A  ***********************/
#define DIO_PORTA_PIN0_DIR   OUTPUT
#define DIO_PORTA_PIN1_DIR   OUTPUT
#define DIO_PORTA_PIN2_DIR   OUTPUT
#define DIO_PORTA_PIN3_DIR   OUTPUT
#define DIO_PORTA_PIN4_DIR   OUTPUT
#define DIO_PORTA_PIN5_DIR   OUTPUT
#define DIO_PORTA_PIN6_DIR   OUTPUT
#define DIO_PORTA_PIN7_DIR   OUTPUT
#define DIO_PORTA_DIRECTIONS   CONC_BIT(DIO_PORTA_PIN7_DIR,DIO_PORTA_PIN6_DIR,DIO_PORTA_PIN5_DIR,DIO_PORTA_PIN4_DIR,DIO_PORTA_PIN3_DIR,DIO_PORTA_PIN2_DIR,DIO_PORTA_PIN1_DIR,DIO_PORTA_PIN0_DIR)
/****************** all ports of B  ***********************/
#define DIO_PORTB_PIN0_DIR   OUTPUT
#define DIO_PORTB_PIN1_DIR   OUTPUT
#define DIO_PORTB_PIN2_DIR   OUTPUT
#define DIO_PORTB_PIN3_DIR   OUTPUT
#define DIO_PORTB_PIN4_DIR   OUTPUT
#define DIO_PORTB_PIN5_DIR   OUTPUT
#define DIO_PORTB_PIN6_DIR   OUTPUT
#define DIO_PORTB_PIN7_DIR   OUTPUT
#define DIO_PORTB_DIRECTIONS   CONC_BIT(DIO_PORTB_PIN7_DIR,DIO_PORTB_PIN6_DIR,DIO_PORTB_PIN5_DIR,DIO_PORTB_PIN4_DIR,DIO_PORTB_PIN3_DIR,DIO_PORTB_PIN2_DIR,DIO_PORTB_PIN1_DIR,DIO_PORTB_PIN0_DIR)
/****************** all ports of C  ***********************/
#define DIO_PORTC_PIN0_DIR   INPUT
#define DIO_PORTC_PIN1_DIR   INPUT
#define DIO_PORTC_PIN2_DIR   INPUT
#define DIO_PORTC_PIN3_DIR   INPUT
#define DIO_PORTC_PIN4_DIR   INPUT
#define DIO_PORTC_PIN5_DIR   INPUT
#define DIO_PORTC_PIN6_DIR   INPUT
#define DIO_PORTC_PIN7_DIR   INPUT
#define DIO_PORTC_DIRECTIONS   CONC_BIT(DIO_PORTC_PIN7_DIR,DIO_PORTC_PIN6_DIR,DIO_PORTC_PIN5_DIR,DIO_PORTC_PIN4_DIR,DIO_PORTC_PIN3_DIR,DIO_PORTC_PIN2_DIR,DIO_PORTC_PIN1_DIR,DIO_PORTC_PIN0_DIR)
/****************** all ports of D  ***********************/
#define DIO_PORTD_PIN0_DIR   INPUT
#define DIO_PORTD_PIN1_DIR   INPUT
#define DIO_PORTD_PIN2_DIR   INPUT
#define DIO_PORTD_PIN3_DIR   INPUT
#define DIO_PORTD_PIN4_DIR   INPUT
#define DIO_PORTD_PIN5_DIR   INPUT
#define DIO_PORTD_PIN6_DIR   INPUT
#define DIO_PORTD_PIN7_DIR   INPUT
#define DIO_PORTD_DIRECTIONS   CONC_BIT(DIO_PORTD_PIN7_DIR,DIO_PORTD_PIN6_DIR,DIO_PORTD_PIN5_DIR,DIO_PORTD_PIN4_DIR,DIO_PORTD_PIN3_DIR,DIO_PORTD_PIN2_DIR,DIO_PORTD_PIN1_DIR,DIO_PORTD_PIN0_DIR)
#endif
