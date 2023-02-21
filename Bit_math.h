/*
 * Bit_math.h
 *
 *  Created on: Aug 16, 2019
 *      Author: Na
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT) (REG|=(1<<BIT)) /* makes the "BIT"-th bit =1*/
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))  /* makes the "BIT"-th bit =0*/
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))	 /* turns the "BIT-th from 0 to 1 or from 1 to 0*/
#define GET_BIT(REG,BIT) ((REG>>BIT)&0x01)
#endif /* BIT_MATH_H_ */
