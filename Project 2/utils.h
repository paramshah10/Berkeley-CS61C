/*
 *  File that holds miscellaneous functions that are possibly useful throughout
 *  the compiler.
 */

#ifndef UTILS_H
#define UTILS_H

#define BYTESIZE 1
#define WORDSIZE 4
#define INITIAL_CAPACITY 8
#define DEFAULT_BUFFERSIZE 80

/*
 *  Function to exit the program and report the error for when
 *  memory allocation fails.
 */
void AllocationFailed();

/*
 *  Function to compute ceil division. This is useful for aligning
 *  the offsets for padding.
 */
int CeilDiv(int dividend, int divisor);

#endif

