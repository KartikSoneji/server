#include "compression_libs.h"
#include <dlfcn.h>

DEFINE_lzma_stream_buffer_decode(DUMMY_lzma_stream_buffer_decode){
    return LZMA_OK;
}

DEFINE_lzma_easy_buffer_encode(DUMMY_lzma_easy_buffer_encode){
    return LZMA_OK;
}

bool MARIADB_IS_LZMA_LOADED = false;

void init_lzma(struct compression_service_lzma_st *handler, bool link_library){
    //point struct to right place for static plugins
    compression_service_lzma = handler;

    compression_service_lzma->lzma_stream_buffer_decode_ptr = DUMMY_lzma_stream_buffer_decode;
    compression_service_lzma->lzma_easy_buffer_encode_ptr = DUMMY_lzma_easy_buffer_encode;
	MARIADB_IS_LZMA_LOADED = false;

	if(!link_library)
		return;
	
    //Load LZMA library dynamically
    void *lzma_library_handle = dlopen("/workspace/mariadb/liblzma.so", RTLD_LAZY | RTLD_GLOBAL);
    if(!lzma_library_handle || dlerror())
		return;
	
	void *lzma_stream_buffer_decode_ptr = safe_dlsym(lzma_library_handle, "lzma_stream_buffer_decode");
	void *lzma_easy_buffer_encode_ptr = safe_dlsym(lzma_library_handle, "lzma_easy_buffer_encode");
	if(
		lzma_stream_buffer_decode_ptr &&
		lzma_easy_buffer_encode_ptr
	){
		compression_service_lzma->lzma_stream_buffer_decode_ptr = (PTR_lzma_stream_buffer_decode) lzma_stream_buffer_decode_ptr;
		compression_service_lzma->lzma_easy_buffer_encode_ptr = (PTR_lzma_easy_buffer_encode) lzma_easy_buffer_encode_ptr;
	}
	
	MARIADB_IS_LZMA_LOADED = true;
	
    // TODO: See if we should use RTLD_NODELETE on dlopen
    // From the dlopen man page:
    // RTLD_NODELETE (since glibc 2.2)
    // Do not unload the library during dlclose().
    // Consequently, the library's static variables are not reinitialized if the library is reloaded with dlopen() at a later time. This flag is not specified in POSIX.1-2001.

	//dlclose(lzma_library_handle);
}