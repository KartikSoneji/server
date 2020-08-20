#include "compression_libs.h"
#include <mariadb.h>
#include <mysqld.h>

void init_compression(struct compression_service_bzip2_st *bzip2_handler){
    if(enabled_compression_libraries & COMPRESSION_ALL)
        enabled_compression_libraries = (COMPRESSION_ALL) - 1;

    init_bzip2(bzip2_handler, (enabled_compression_libraries & COMPRESSION_BZIP2) != 0);
}
