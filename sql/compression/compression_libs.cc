#include "compression_libs.h"
#include <dlfcn.h>
#include <mariadb.h>
#include <mysqld.h>
#include <log.h>

void * safe_dlsym(void *library_handle, const char *function_name){
    // From the dlsym man page:
    // The correct way to test for an error is to call dlerror() to clear any old
    // error conditions, then call dlsym(), and then call dlerror() again
    dlerror();
	void *function_ptr = dlsym(library_handle, function_name);
    const char *error = dlerror();
	if(error){
        sql_print_warning("Could not find symbol \"%s\", error: %s", function_name, error);
		function_ptr = 0;
    }

	return function_ptr;
}

void init_compression(){
    ulonglong load_libraries = enabled_compression_libraries;
    if(enabled_compression_libraries & COMPRESSION_AUTO)
		load_libraries = 
            COMPRESSION_BZIP2   |
            COMPRESSION_LZ4     |
            COMPRESSION_LZMA    |
            COMPRESSION_LZO     |
            COMPRESSION_SNAPPY  |
            COMPRESSION_ZLIB    |
            COMPRESSION_ZSTD;

    #define LOAD_LIBRARY(init_function, CHECK_FLAG) \
        if(load_libraries & CHECK_FLAG) \
            if(init_function() && (enabled_compression_libraries & CHECK_FLAG)) \
                unireg_abort(1);

    LOAD_LIBRARY(init_lzo, COMPRESSION_LZO);
}