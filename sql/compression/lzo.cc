#include "compression_libs.h"
#include <dlfcn.h>

bool COMPRESSION_LOADED_LZO = false;

DEFINE_lzo1x_1_15_compress(DUMMY_lzo1x_1_15_compress){
    return LZO_E_INTERNAL_ERROR;
}

DEFINE_lzo1x_decompress_safe(DUMMY_lzo1x_decompress_safe){
    return LZO_E_INTERNAL_ERROR;
}

struct {
    PTR_lzo1x_1_15_compress lzo1x_1_15_compress_ptr;
    PTR_lzo1x_decompress_safe lzo1x_decompress_safe_ptr;
}
lzo_handler = {
    DUMMY_lzo1x_1_15_compress,
    DUMMY_lzo1x_decompress_safe
};


DEFINE_lzo1x_1_15_compress(lzo1x_1_15_compress){
    return lzo_handler.lzo1x_1_15_compress_ptr(src, src_len, dst, dst_len, wrkmem);
}

DEFINE_lzo1x_decompress_safe(lzo1x_decompress_safe){
    return lzo_handler.lzo1x_decompress_safe_ptr(src, src_len, dst, dst_len, wrkmem);
}


void init_lzo(){
    //Load LZO library dynamically
    void *library_handle = dlopen("liblzo2.so", RTLD_LAZY | RTLD_GLOBAL);
    if(!library_handle || dlerror())
		return;

	void *lzo1x_1_15_compress_ptr = safe_dlsym(library_handle, "lzo1x_1_15_compress");
	void *lzo1x_decompress_safe_ptr = safe_dlsym(library_handle, "lzo1x_decompress_safe");
	if(
		!lzo1x_1_15_compress_ptr ||
		!lzo1x_decompress_safe_ptr
	)
        return;
    
    lzo_handler.lzo1x_1_15_compress_ptr = (PTR_lzo1x_1_15_compress) lzo1x_1_15_compress_ptr;
    lzo_handler.lzo1x_decompress_safe_ptr = (PTR_lzo1x_decompress_safe) lzo1x_decompress_safe_ptr;

    COMPRESSION_LOADED_LZO = true;
}