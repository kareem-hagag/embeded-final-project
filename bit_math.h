#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG, BIT_NUM)        ((REG) |=  (1 << (BIT_NUM)))
#define CLR_BIT(REG, BIT_NUM)        ((REG) &= ~(1 << (BIT_NUM)))
#define TOG_BIT(REG, BIT_NUM)        ((REG) ^=  (1 << (BIT_NUM)))
#define GET_BIT(REG, BIT_NUM)        (((REG) >> (BIT_NUM)) & 0x01)

#define SET_BYTE(REG, VALUE)         ((REG) = (VALUE))
#define CLR_BYTE(REG)                ((REG) = 0x00)

#define CONC_BIT_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)   0b##b7##b6##b5##b4##b3##b2##b1##b0
#define CONC_BIT(b7,b6,b5,b4,b3,b2,b1,b0)          CONC_BIT_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)

#endif
