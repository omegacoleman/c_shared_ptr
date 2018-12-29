C Shared Ptr
============

This project aims to take std::shared_ptr from c++ and implement it the c way, 
kind of similar to what gnome glib has done in GObject.

It can allocate the memory based on length, which is similar to Allocator in 
c++, and can take a handler -- a function pointer to call before the memory is
freed, as a replica of Deleter. It is named deleter as well.

To learn how it works now, see test.c
It will output:

```
A string is being freed :
Thas string only existed a glimpse.
(The program delays for 1 sec)
A string is being freed :
Thox string was copied to memory and existed for one second.
```
As you can see, no memory leak is happening. The misspelled words are modified 
by the functions. 

It is currently non-thread-safe.

You may use it for callbacks/coroutines for now. But I recommend you to wait 
for further updates.

TODO
----

- [ ] Rewrite a better CMakeLists.txt
- [ ] Add pthread thread-safe support
- [ ] After above is done, add a test similar to the example in cppreferences
