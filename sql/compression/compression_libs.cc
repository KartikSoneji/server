#include "compression_libs.h"
#include <mariadb.h>
#include <mysqld.h>

void init_compression(struct compression_service_snappy_st *snappy_handler){
    if(enabled_compression_libraries & COMPRESSION_ALL)
        enabled_compression_libraries = (COMPRESSION_ALL) - 1;
    
    init_snappy(snappy_handler, (enabled_compression_libraries & COMPRESSION_SNAPPY) != 0);
}
