#include "shared_ptr.h"
#include <stdlib.h>

void CSPTR_reset(c_shared_ptr *csptr)
{
	csptr->ptr = NULL;
	csptr->use_count = 0;
	csptr->deleter = NULL;
}

void CSPTR_reset_with_ptr(c_shared_ptr *csptr, void *ptr)
{
	CSPTR_reset(csptr);
	csptr->ptr = ptr;
	csptr->use_count++;
}

void CSPTR_reset_with_ptr_and_deleter(c_shared_ptr *csptr, void *ptr, void *deleter)
{
	CSPTR_reset_with_ptr(csptr, ptr);
	csptr->deleter = deleter;
}

// create empty c_shared_ptr with NULL as ptr
c_shared_ptr *CSPTR_make_null_shared()
{
	c_shared_ptr *csptr = malloc(sizeof(c_shared_ptr));
	CSPTR_reset(csptr);
	return csptr;
}

c_shared_ptr *CSPTR_make_shared(void *ptr)
{
	c_shared_ptr *csptr = malloc(sizeof(c_shared_ptr));
	CSPTR_reset_with_ptr(csptr, ptr);
	return csptr;
}

c_shared_ptr *CSPTR_make_shared_with_deleter(void *ptr, void *deleter)
{
	c_shared_ptr *csptr = malloc(sizeof(c_shared_ptr));
	CSPTR_reset_with_ptr_and_deleter(csptr, ptr, deleter);
	return csptr;
}

c_shared_ptr *CSPTR_allocate_shared(size_t len)
{
	void *mem = malloc(len);
	return CSPTR_make_shared(mem);
}

c_shared_ptr *CSPTR_allocate_shared_with_deleter(size_t len, void *deleter)
{
	void *mem = malloc(len);
	return CSPTR_make_shared_with_deleter(mem, deleter);
}

void CSPTR_swap(c_shared_ptr *a, c_shared_ptr *b)
{
	void *ptr = a->ptr;
	a->ptr = b->ptr;
	b->ptr = ptr;
}

void CSPTR_delete_shared(c_shared_ptr *csptr)
{
	(*csptr->deleter)(csptr);
	free(csptr->ptr);
	free(csptr);
}

void CSPTR_ref(c_shared_ptr *csptr)
{
	csptr->use_count++;
}

void CSPTR_unref(c_shared_ptr *csptr)
{
	csptr->use_count--;
	if(csptr->use_count <= 0){
		CSPTR_delete_shared(csptr);
	}
}

void *CSPTR_get(c_shared_ptr *csptr)
{
	return csptr->ptr;
}

CSPTR_REF_COUNT_TYPE CSPTR_use_count(c_shared_ptr *csptr)
{
	return csptr->use_count;
}
