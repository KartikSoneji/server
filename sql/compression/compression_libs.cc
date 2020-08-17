#include "compression_libs.h"
#include <dlfcn.h>
#include <mariadb.h>
#include <mysqld.h>

void init_compression(struct compression_service_lzo_st *lzo_handler){
    if(enabled_compression_libraries & COMPRESSION_ALL)
        enabled_compression_libraries = (COMPRESSION_ALL) - 1;

    init_lzo(lzo_handler, (enabled_compression_libraries & COMPRESSION_LZO) != 0);
}
