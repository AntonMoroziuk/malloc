#include "includes/malloc.h"
#include <string.h>

int main ()
{
	void *ptr1, *ptr2;
malloc(32);
malloc(32);
malloc(32);
ptr1 = malloc(256);
ptr2 = malloc(768);
free(ptr1);
free(ptr2);
ptr1 = malloc(256);
free(ptr1);
ptr1 = malloc(256);
ptr2 = malloc(768);
free(ptr1);
free(ptr2);
malloc(16);
malloc(45);
malloc(172);
malloc(45);
malloc(50);
malloc(47);
malloc(8);
malloc(64);
malloc(49);
malloc(67);
malloc(52);
malloc(54);
malloc(95);
malloc(16);
malloc(64);
malloc(14);
ptr1 = malloc(256);
free(ptr1);
malloc(131072);
ptr1 = malloc(1024);
ptr2 = malloc(4096);
free(ptr1);
ptr1 = malloc(4096);
free(ptr2);
malloc(4096);
free(ptr1);
ptr1 = malloc(4096);
ptr2 = malloc(4096);
free(ptr1);
ptr1 = malloc(4096);
free(ptr2);
malloc(4096);
free(ptr1);
}
