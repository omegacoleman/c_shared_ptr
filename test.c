#include "shared_ptr.h"
#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include <windows.h>
#define sleep Sleep
#else
#include <unistd.h>
#endif

void print_it(c_shared_ptr *csptr)
{
	printf("A string is being freed : \n%s\n", *((char **)csptr));
	// Tricky part : a csptr can be forced into a readonly **type yet still works
}

c_shared_ptr *the_csptr_delayed_to_be_used;

void do_something_with_string_a(c_shared_ptr *csptr)
{
	((char *)CSPTR_get(csptr))[3] = 'x';

	CSPTR_ref(csptr); // It is registered to be used later, so ref it!
	// This is similar to what happens in a callback.
	the_csptr_delayed_to_be_used = csptr;

	CSPTR_unref(csptr);
}

void the_delayed_call()
{
	((char *)CSPTR_get(the_csptr_delayed_to_be_used))[2] = 'o';
	CSPTR_unref(the_csptr_delayed_to_be_used);
}

void do_something_with_string_b(c_shared_ptr *csptr)
{
	((char *)CSPTR_get(csptr))[2] = 'a';
	CSPTR_unref(csptr);
}

int main(void)
{
	char str_a[] = "This string was copied to memory and existed for one second.";
	char str_b[] = "This string only existed a glimpse.";
	c_shared_ptr *csptr_str_a = CSPTR_allocate_shared_with_deleter(sizeof(str_a), print_it);
	c_shared_ptr *csptr_str_b = CSPTR_allocate_shared_with_deleter(sizeof(str_b), print_it);
	memcpy(CSPTR_get(csptr_str_a), str_a, sizeof(str_a));
	memcpy(CSPTR_get(csptr_str_b), str_b, sizeof(str_b));

	CSPTR_ref(csptr_str_a);
	do_something_with_string_a(csptr_str_a);
	CSPTR_unref(csptr_str_a);

	CSPTR_ref(csptr_str_b);
	do_something_with_string_b(csptr_str_b);
	CSPTR_unref(csptr_str_b);

	sleep(1000);

	the_delayed_call();
	return 0;
}

