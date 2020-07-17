#include "compression_libs.h"
#include <dlfcn.h>
#include <mariadb.h>
#include <mysqld.h>

void * safe_dlsym(void *library_handle, const char *function_name){
    // From the dlsym man page:
    // The correct way to test for an error is to call dlerror() to clear any old
    // error conditions, then call dlsym(), and then call dlerror() again
    dlerror();
	void *function_ptr = dlsym(library_handle, function_name);
	if(dlerror())
		function_ptr = 0;
	
	return function_ptr;
}

void init_compression(struct compression_service_lzma_st *lzma_handler){
	if(enabled_compression_libraries & COMPRESSION_ALL)
		enabled_compression_libraries--;
	
    init_lzma(lzma_handler, (enabled_compression_libraries & COMPRESSION_LZMA) != 0);
}