/**
  @file include/compression/lzo/lzo1x.h
  This service provides dynamic access to LZO.
*/

#ifndef SERVICE_LZO_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#ifndef MYSQL_ABI_CHECK
#endif

#define LZO_E_OK 0
#define LZO1X_1_15_MEM_COMPRESS ((unsigned int) (32768L * ((unsigned) sizeof(unsigned char *))))

typedef unsigned long lzo_uint;

#define DEFINE_lzo1x_1_15_compress(NAME) int NAME(  \
    const unsigned char *src,                       \
    unsigned long src_len,                          \
    unsigned char *dst,                             \
    unsigned long *dst_len,                         \
    void *wrkmem                                    \
)

#define DEFINE_lzo1x_decompress_safe(NAME) int NAME(    \
    const unsigned char *src,                           \
    unsigned long src_len,                              \
    unsigned char *dst,                                 \
    unsigned long *dst_len,                             \
    void *wrkmem                                        \
)

typedef DEFINE_lzo1x_1_15_compress((*PTR_lzo1x_1_15_compress));
typedef DEFINE_lzo1x_decompress_safe((*PTR_lzo1x_decompress_safe));

DEFINE_lzo1x_1_15_compress(lzo1x_1_15_compress);
DEFINE_lzo1x_decompress_safe(lzo1x_decompress_safe);

#ifdef __cplusplus
}
#endif

#define SERVICE_LZO_INCLUDED
#endif