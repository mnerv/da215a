/*
 * common.h
 *
 * Macros definition for setting up the I/O register
 *
 * Author:  Pratchaya Khansomboon
 *
 * Date:    08-12-2020
 */

#ifndef COMMON_H_
#define COMMON_H_

/*
 * This macro is used to set a specific bit in a register.
 */
#define SET_BIT(reg, pos) (reg) |= (1 << pos)

/*
 * This macro is used to clear a specific bit in a register.
 */
#define CLR_BIT(reg, pos) (reg) &= ~(1 << pos)

/*
 * This macro is used to modify several bits of a register.
 * Example:
 *	Bit 7-4 of PORTD should be set to 1010, while the
 *	rest of the register should NOT be modified! Usage:
 *		SET_BIT_LEVELS(PORTD, 0b00001111, 0b10100000);
 * The bit mask is used to clear the bits that should be modified.
 */
#define SET_BIT_LEVELS(reg, bit_mask, bit_data) \
    (reg) = (reg & bit_mask) | bit_data

#endif /* COMMON_H_ */