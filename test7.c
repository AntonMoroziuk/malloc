#include "includes/malloc.h"

int main ()
{
	char *ptr1, *ptr2, *ptr3;
ptr1 = malloc (1024 * 1024 * 128);
ptr2 = malloc (1024 * 1024 * 128);
ptr3 = malloc (1024 * 1024 * 128);
ptr1[1] = 42;
ptr2[1] = 42;
ptr3[1] = 42;
free(ptr2);
free(ptr2);
ptr2 = malloc (1024 * 1024 * 128);
ptr2[1] = 42;
free(ptr1);
free(ptr2);
free(ptr3);
ptr2 = malloc (1024 * 1024 * 128);
ptr2[1] = 42;
ptr2 = malloc (1024 * 1024 * 128);
ptr2[1] = 42;
ptr2 = malloc (1024 * 1024 * 128);
ptr2[1] = 42;
ptr2 = malloc (1024 * 1024 * 128);
ptr2[1] = 42;
ptr2 = malloc (1024 * 1024 * 128);
ptr2[1] = 42;
ptr2 = malloc (1024 * 1024 * 128);
return (0);
}
