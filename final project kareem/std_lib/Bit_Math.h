/*************************************************************/
/************ Auther : kareem hagag ******************/
/************ date : 29/7/2026 ******************/
/************ Title: Utility Library ********************/
/**************************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H
/***************** main function ************************8*/
#define SET_BIT(REG,BIT_NUM)        REG |=  (1 << (BIT_NUM))
#define CLR_BIT(REG,BIT_NUM)        REG &= ~(1 << (BIT_NUM))
#define TOG_BIT(REG,BIT_NUM)        REG ^=  (1 << (BIT_NUM))
#define GET_BIT(REG,BIT_NUM)       ((REG >> (BIT_NUM)) & 0x01)
/************** control all port ********************/
#define SET_PORT(REG)               REG = 0xFF
#define CLR_PORT(REG)               REG = 0x00
#define ASG_PORT(REG,VALUE)         REG = (VALUE)

#endif /* Bit_Math.h */