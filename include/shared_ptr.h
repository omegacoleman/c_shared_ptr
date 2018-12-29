#pragma once

#include <stddef.h>

#ifndef CSPTR_REF_COUNT_TYPE
#define CSPTR_REF_COUNT_TYPE long
#endif

typedef struct _c_shared_ptr
{
	void *ptr;
	CSPTR_REF_COUNT_TYPE use_count;
	void (*deleter)(struct _c_shared_ptr *); // void f(c_shared_ptr *) to be called upon deletion
} c_shared_ptr;

void CSPTR_reset(c_shared_ptr *csptr);
void CSPTR_reset_with_ptr(c_shared_ptr *csptr, void *ptr);
void CSPTR_reset_with_ptr_and_deleter(c_shared_ptr *csptr, void *ptr, void *deleter);

c_shared_ptr *CSPTR_make_null_shared(); // create empty c_shared_ptr with NULL as ptr
c_shared_ptr *CSPTR_make_shared(void *ptr);
c_shared_ptr *CSPTR_make_shared_with_deleter(void *ptr, void *deleter);

c_shared_ptr *CSPTR_allocate_shared(size_t len);
c_shared_ptr *CSPTR_allocate_shared_with_deleter(size_t len, void *deleter);

void CSPTR_swap(c_shared_ptr *a, c_shared_ptr *b);

void CSPTR_ref(c_shared_ptr *csptr);
void CSPTR_unref(c_shared_ptr *csptr);

void *CSPTR_get(c_shared_ptr *csptr);
CSPTR_REF_COUNT_TYPE CSPTR_use_count(c_shared_ptr *csptr);

// after a procedure called CSPTR_unref on the csptr, the csptr SHALL BE ASSUME DELETED
// it may happen when ur the last owner, so you should assume that
