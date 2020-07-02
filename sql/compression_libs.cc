#include "compression_libs.h"
#include <stdio.h>

lzma_ret DUMMY_lzma_stream_buffer_decode(
		uint64_t *, uint32_t,
		const lzma_allocator *,
		const uint8_t *, size_t *, size_t,
		uint8_t *, size_t *, size_t){
            printf("Inside DUMMY_lzma_stream_buffer_decode\n");
            return LZMA_OK;
        }

lzma_ret DUMMY_lzma_easy_buffer_encode(
		uint32_t, lzma_check,
		const lzma_allocator *,
		const uint8_t *, size_t,
		uint8_t *, size_t *, size_t){
            printf("Inside DUMMY_lzma_easy_buffer_encode\n");
            return LZMA_OK;
        }

void init_compression(struct compression_service_lzma_st *handler){
    printf("Inside init_compression\n");

    //point struct to right place for static plugins
    compression_service_lzma = handler;

    compression_service_lzma->lzma_stream_buffer_decode_ptr = DUMMY_lzma_stream_buffer_decode;
    compression_service_lzma->lzma_easy_buffer_encode_ptr = DUMMY_lzma_easy_buffer_encode;

    //TODO: Load library dynamically
    if(0 /*library is loaded*/){
        //lzma_handler.lzma_stream_buffer_decode_ptr = load_library->lzma_stream_buffer_decode_ptr;
		//lzma_handler.lzma_easy_buffer_encode_ptr = load_library->lzma_easy_buffer_encode_ptr;
    }
}