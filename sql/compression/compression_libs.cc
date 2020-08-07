#include "compression_libs.h"
#include <dlfcn.h>
#include <mariadb.h>
#include <mysqld.h>

void init_compression(){
    if(enabled_compression_libraries & COMPRESSION_ALL)
        enabled_compression_libraries = (COMPRESSION_ALL) - 1;

    if(enabled_compression_libraries & COMPRESSION_ZSTD)
        init_zstd();
}