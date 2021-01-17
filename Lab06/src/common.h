/*
 * common.h
 *
 * Macros definition for setting up the I/O register
 *
 * Author:  Pratchaya Khansomboon
 *
 * Date:    2020-12-08
 */

#ifndef COMMON_H_
#define COMMON_H_

/**
 * This macro is used to set a specific bit in a register.
 *
 * @param reg traget register
 * @param pos bit position
 */
#define SET_BIT(reg, pos) (reg) |= (1 << pos)

/**
 * This macro is used to clear a specific bit in a register.
 *
 * @param reg target register
 * @param pos bit position
 */
#define CLR_BIT(reg, pos) (reg) &= ~(1 << pos)

/**
 * This macro is used to modify several bits of a register.
 *
 * Example:
 * Bit 7-4 of PORTD should be set to 1010, while the
 * rest of the register should NOT be modified!
 *
 * Usage:
 * SET_BIT_LEVELS(PORTD, 0b00001111, 0b10100000);
 *
 * The bit mask is used to clear the bits that should be modified.
 *
 * @param reg target register
 * @param bit_mask masked for the target register
 * @param bit_data data value
 */
#define SET_BIT_LEVELS(reg, bit_mask, bit_data) \
    (reg) = (((reg) & (bit_mask)) | ((bit_data) & ~(bit_mask)))

#endif /* COMMON_H_ */