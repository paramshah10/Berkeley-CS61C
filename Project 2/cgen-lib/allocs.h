/* Function which allocates the specified number of bytes to the bottom of the
   calling stack frame. Since the stack must be word aligned we will pad the
   allocation to be a multiple of 4.
*/

char *alloca (unsigned int bytes);
