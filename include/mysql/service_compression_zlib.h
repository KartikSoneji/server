/**
  @file include/mysql/service_compression_zlib.h
  This service provides dynamic access to ZLib.
*/

#ifndef SERVICE_COMPRESSION_ZLIB_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*alloc_func) (void *opaque, unsigned int items, unsigned int size);
typedef void   (*free_func)  (void *opaque, void *address);

struct internal_state;

typedef struct z_stream_s {
    const void   *next_in;   /* next input byte */
    unsigned int  avail_in;  /* number of bytes available at next_in */
    unsigned long total_in;  /* total number of input bytes read so far */

    void           *next_out;  /* next output byte will go here */
    unsigned int   avail_out; /* remaining free space at next_out */
    unsigned long  total_out; /* total number of bytes output so far */

    const char *msg;  /* last error message, NULL if no error */
    struct internal_state *state; /* not visible by applications */

    alloc_func zalloc;  /* used to allocate the internal state */
    free_func  zfree;   /* used to free the internal state */
    void *opaque;       /* private data object passed to zalloc and zfree */

    int     data_type;  /* best guess about the data type: binary or text
                           for deflate, or the decoding state for inflate */
    unsigned long   adler;      /* Adler-32 or CRC-32 value of the uncompressed data */
    unsigned long   reserved;   /* reserved for future use */
} z_stream;

typedef z_stream *z_streamp;

extern struct compression_service_zlib_st {
  int (*deflateInit2_ptr)(z_streamp, int, int, int, int, int);
  int (*inflateInit2_ptr)(z_streamp, int);
} *compression_service_zlib;


#ifdef MYSQL_DYNAMIC_PLUGIN

#define deflateInit2(a, b, c, d, e, f, g) compression_service_zlib->deflateInit2_ptr(a, b, c, d, e, f, g)
#define inflateInit2(a, b) compression_service_zlib->inflateInit2_ptr(a, b)

#else

int deflateInit2(z_streamp, int, int, int, int, int);
int inflateInit2(z_streamp, int);

#endif

#ifdef __cplusplus
}
#endif

#define SERVICE_COMPRESSION_ZLIB_INCLUDED
#endif