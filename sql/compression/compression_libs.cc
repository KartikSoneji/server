#include "compression_libs.h"
#include <mariadb.h>
#include <mysqld.h>

void init_compression(struct compression_service_lzma_st *lzma_handler){
    if(enabled_compression_libraries & COMPRESSION_ALL)
        enabled_compression_libraries = (COMPRESSION_ALL) - 1;

    // TODO: See if we should use RTLD_NODELETE as dlopen flags
    // Then, we can use dlclose(library_handle) in the init_* functions
    // From the dlopen man page:
    // RTLD_NODELETE (since glibc 2.2)
    // Do not unload the library during dlclose().
    // Consequently, the library's static variables are not reinitialized
    // if the library is reloaded with dlopen() at a later time.
    // This flag is not specified in POSIX.1-2001.

    init_lzma(lzma_handler, (enabled_compression_libraries & COMPRESSION_LZMA) != 0);
}
