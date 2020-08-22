#include "compression_libs.h"
#include <mariadb.h>
#include <mysqld.h>

void init_compression(struct compression_service_lz4_st *lz4_handler){
    if(enabled_compression_libraries & COMPRESSION_ALL)
        enabled_compression_libraries = (COMPRESSION_ALL) - 1;

    init_lz4(lz4_handler, (enabled_compression_libraries & COMPRESSION_LZ4) != 0);
}
