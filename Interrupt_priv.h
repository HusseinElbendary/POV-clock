/*
 * Interrupt_priv.h
 *
 *  Created on: Nov 15, 2019
 *      Author: Na
 */

#ifndef INTERRUPT_PRIV_H_
#define INTERRUPT_PRIV_H_



#define SREG  ( * ((volatile u8*)  0x5F))
#define MCUCR ( * ((volatile u8*)  0x55))
#define GICR  ( * ((volatile u8*)  0x5B))


#endif /* INTERRUPT_PRIV_H_ */
