/**
  @file include/mysql/lzma.h
  This service provides dynamic access to LZMA.
*/

#ifndef SERVICE_LZMA_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef enum {
	LZMA_OK                 = 0,
	LZMA_STREAM_END         = 1,
	LZMA_NO_CHECK           = 2,
	LZMA_UNSUPPORTED_CHECK  = 3,
	LZMA_GET_CHECK          = 4,
	LZMA_MEM_ERROR          = 5,
	LZMA_MEMLIMIT_ERROR     = 6,
	LZMA_FORMAT_ERROR       = 7,
	LZMA_OPTIONS_ERROR      = 8,
	LZMA_DATA_ERROR         = 9,
	LZMA_BUF_ERROR          = 10,
	LZMA_PROG_ERROR         = 11,
} lzma_ret;

typedef struct {
	void *(*alloc)(void *opaque, size_t nmemb, size_t size);
	void (*free)(void *opaque, void *ptr);
	void *opaque;
} lzma_allocator;

typedef enum {
	LZMA_CHECK_NONE     = 0,
	LZMA_CHECK_CRC32    = 1,
	LZMA_CHECK_CRC64    = 4,
	LZMA_CHECK_SHA256   = 10
} lzma_check;

struct compression_service_lzma_st {
  lzma_ret (*lzma_stream_buffer_decode_ptr)(uint64_t *, uint32_t, 
       const lzma_allocator *, const uint8_t *, size_t *,
	   size_t, uint8_t *, size_t *, size_t);
  
  lzma_ret (*lzma_easy_buffer_encode_ptr)(uint32_t, lzma_check,
		const lzma_allocator *,
		const uint8_t *, size_t,
		uint8_t *, size_t *, size_t);
};

extern struct compression_service_lzma_st *compression_service_lzma;

#define lzma_stream_buffer_decode(...) compression_service_lzma->lzma_stream_buffer_decode_ptr(__VA_ARGS__)
#define lzma_easy_buffer_encode(...) compression_service_lzma->lzma_easy_buffer_encode_ptr(__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#define SERVICE_LZMA_INCLUDED
#endif