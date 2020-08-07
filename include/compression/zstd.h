/**
  @file include/compression/zstd.h
  This service provides dynamic access to ZStandard.
*/

#ifndef SERVICE_ZSTD_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#ifndef MYSQL_ABI_CHECK
#include <stdbool.h>
#include <stddef.h>
#endif

extern bool COMPRESSION_LOADED_ZSTD;

// TODO: See if we should use a higher version to get newer functions,
// or not define this to reduce number of functions loaded
// But versions > 10103 use an additional header, <zdict.h>
// Also need to look at the defines:
//    ROCKSDB_ZSTD_CUSTOM_MEM
//    ROCKSDB_ZSTD_DDICT
#define ZSTD_VERSION_NUMBER     800

/*
Mroonga

ZSTD_compress
ZSTD_compressBound
ZSTD_decompress
ZSTD_getErrorName
ZSTD_isError
*/

/*
RocksDB

Undefined ZSTD_VERSION_NUMBER

ZSTD_compress
ZSTD_compressBound
ZSTD_decompress
ZSTD_versionNumber

With ZSTD_VERSION_NUMBER = 800

ZSTD_compressBound
ZSTD_compress_usingCDict
ZSTD_compress_usingDict
ZSTD_createCCtx
ZSTD_createCDict
ZSTD_createDCtx
ZSTD_decompress_usingDict
ZSTD_freeCCtx
ZSTD_freeCDict
ZSTD_freeDCtx
ZSTD_versionNumber

With ROCKSDB_ZSTD_CUSTOM_MEM
ZSTD_createCCtx_advanced
ZSTD_createDCtx_advanced

With ROCKSDB_ZSTD_DDICT
ZSTD_createDDict_byReference
ZSTD_decompress_usingDDict
ZSTD_freeDDict
ZSTD_sizeof_DDict
*/

typedef struct ZSTD_CCtx_s ZSTD_CCtx;
typedef struct ZSTD_CDict_s ZSTD_CDict;
typedef struct ZSTD_DCtx_s ZSTD_DCtx;
typedef struct ZSTD_DDict_s ZSTD_DDict;

typedef void* (*ZSTD_allocFunction) (void* opaque, size_t size);
typedef void  (*ZSTD_freeFunction) (void* opaque, void* address);

typedef struct {
    ZSTD_allocFunction customAlloc;
    ZSTD_freeFunction customFree;
    void* opaque;
} ZSTD_customMem;

#define DEFINE_ZSTD_compress(NAME) size_t NAME(\
   void *dst,                                  \
   size_t dstCapacity,                         \
   const void *src,                            \
   size_t srcSize,                             \
   int compressionLevel                        \
)

#define DEFINE_ZSTD_compress_usingCDict(NAME) size_t NAME( \
   ZSTD_CCtx *cctx,                                        \
   void *dst,                                              \
   size_t dstCapacity,                                     \
   const void *src,                                        \
   size_t srcSize,                                         \
   const ZSTD_CDict *cdict                                 \
)

#define DEFINE_ZSTD_compress_usingDict(NAME) size_t NAME(  \
   ZSTD_CCtx *ctx,                                         \
    void *dst,                                             \
   size_t dstCapacity,                                     \
   const void *src,                                        \
   size_t srcSize,                                         \
   const void *dict,                                       \
   size_t dictSize,                                        \
   int compressionLevel                                    \
)

#define DEFINE_ZSTD_compressBound(NAME) size_t NAME(   \
   size_t srcSize                                      \
)

#define DEFINE_ZSTD_createCCtx(NAME) ZSTD_CCtx * NAME()

#define DEFINE_ZSTD_createCCtx_advanced(NAME) ZSTD_CCtx * NAME( \
   ZSTD_customMem customMem                                     \
)

#define DEFINE_ZSTD_createCDict(NAME) ZSTD_CDict * NAME(   \
   const void *dictBuffer,                                 \
   size_t dictSize,                                        \
   int compressionLevel                                    \
)

#define DEFINE_ZSTD_createDCtx(NAME) ZSTD_DCtx * NAME()

#define DEFINE_ZSTD_createDCtx_advanced(NAME) ZSTD_DCtx * NAME( \
   ZSTD_customMem customMem                                     \
)

#define DEFINE_ZSTD_createDDict_byReference(NAME) ZSTD_DDict * NAME(   \
   const void *dictBuffer,                                             \
   size_t dictSize                                                     \
)

#define DEFINE_ZSTD_decompress(NAME) size_t NAME(  \
   void *dst,                                      \
   size_t dstCapacity,                             \
   const void *src,                                \
   size_t compressedSize                           \
)

#define DEFINE_ZSTD_decompress_usingDDict(NAME) size_t NAME(   \
   ZSTD_DCtx *dctx,                                            \
   void *dst,                                                  \
   size_t dstCapacity,                                         \
   const void *src,                                            \
   size_t srcSize,                                             \
   const ZSTD_DDict *ddict                                     \
)

#define DEFINE_ZSTD_decompress_usingDict(NAME) size_t NAME( \
   ZSTD_DCtx *dctx,                                         \
   void *dst,                                               \
   size_t dstCapacity,                                      \
   const void *src,                                         \
   size_t srcSize,                                          \
   const void *dict,                                        \
   size_t dictSize                                          \
)

#define DEFINE_ZSTD_freeCCtx(NAME) size_t NAME(    \
   ZSTD_CCtx *cctx                             \
)

#define DEFINE_ZSTD_freeCDict(NAME) size_t NAME(   \
   ZSTD_CDict *CDict                               \
)

#define DEFINE_ZSTD_freeDCtx(NAME) size_t NAME(    \
   ZSTD_DCtx *dctx                                 \
)

#define DEFINE_ZSTD_freeDDict(NAME) size_t NAME(   \
   ZSTD_DDict *ddict                               \
)

#define DEFINE_ZSTD_getErrorName(NAME) const char* NAME(   \
   size_t code                                             \
)

#define DEFINE_ZSTD_isError(NAME) unsigned NAME(   \
   size_t code                                     \
)

#define DEFINE_ZSTD_sizeof_DDict(NAME) size_t NAME(    \
   const ZSTD_DDict *ddict                         \
)

#define DEFINE_ZSTD_versionNumber(NAME) unsigned NAME()


typedef DEFINE_ZSTD_compress                ((*PTR_ZSTD_compress));
typedef DEFINE_ZSTD_compressBound           ((*PTR_ZSTD_compressBound));
typedef DEFINE_ZSTD_compress_usingCDict     ((*PTR_ZSTD_compress_usingCDict));
typedef DEFINE_ZSTD_compress_usingDict      ((*PTR_ZSTD_compress_usingDict));
typedef DEFINE_ZSTD_createCCtx              ((*PTR_ZSTD_createCCtx));
typedef DEFINE_ZSTD_createCCtx_advanced     ((*PTR_ZSTD_createCCtx_advanced));
typedef DEFINE_ZSTD_createCDict             ((*PTR_ZSTD_createCDict));
typedef DEFINE_ZSTD_createDCtx              ((*PTR_ZSTD_createDCtx));
typedef DEFINE_ZSTD_createDCtx_advanced     ((*PTR_ZSTD_createDCtx_advanced));
typedef DEFINE_ZSTD_createDDict_byReference ((*PTR_ZSTD_createDDict_byReference));
typedef DEFINE_ZSTD_decompress              ((*PTR_ZSTD_decompress));
typedef DEFINE_ZSTD_decompress_usingDDict   ((*PTR_ZSTD_decompress_usingDDict));
typedef DEFINE_ZSTD_decompress_usingDict    ((*PTR_ZSTD_decompress_usingDict));
typedef DEFINE_ZSTD_freeCCtx                ((*PTR_ZSTD_freeCCtx));
typedef DEFINE_ZSTD_freeCDict               ((*PTR_ZSTD_freeCDict));
typedef DEFINE_ZSTD_freeDCtx                ((*PTR_ZSTD_freeDCtx));
typedef DEFINE_ZSTD_freeDDict               ((*PTR_ZSTD_freeDDict));
typedef DEFINE_ZSTD_getErrorName            ((*PTR_ZSTD_getErrorName));
typedef DEFINE_ZSTD_isError                 ((*PTR_ZSTD_isError));
typedef DEFINE_ZSTD_sizeof_DDict            ((*PTR_ZSTD_sizeof_DDict));
typedef DEFINE_ZSTD_versionNumber           ((*PTR_ZSTD_versionNumber));


struct zstd_handler_st{
   PTR_ZSTD_compress                   ZSTD_compress_ptr;
   PTR_ZSTD_compressBound              ZSTD_compressBound_ptr;
   PTR_ZSTD_compress_usingCDict        ZSTD_compress_usingCDict_ptr;
   PTR_ZSTD_compress_usingDict         ZSTD_compress_usingDict_ptr;
   PTR_ZSTD_createCCtx                 ZSTD_createCCtx_ptr;
   PTR_ZSTD_createCCtx_advanced        ZSTD_createCCtx_advanced_ptr;
   PTR_ZSTD_createCDict                ZSTD_createCDict_ptr;
   PTR_ZSTD_createDCtx                 ZSTD_createDCtx_ptr;
   PTR_ZSTD_createDCtx_advanced        ZSTD_createDCtx_advanced_ptr;
   PTR_ZSTD_createDDict_byReference    ZSTD_createDDict_byReference_ptr;
   PTR_ZSTD_decompress                 ZSTD_decompress_ptr;
   PTR_ZSTD_decompress_usingDDict      ZSTD_decompress_usingDDict_ptr;
   PTR_ZSTD_decompress_usingDict       ZSTD_decompress_usingDict_ptr;
   PTR_ZSTD_freeCCtx                   ZSTD_freeCCtx_ptr;
   PTR_ZSTD_freeCDict                  ZSTD_freeCDict_ptr;
   PTR_ZSTD_freeDCtx                   ZSTD_freeDCtx_ptr;
   PTR_ZSTD_freeDDict                  ZSTD_freeDDict_ptr;
   PTR_ZSTD_getErrorName               ZSTD_getErrorName_ptr;
   PTR_ZSTD_isError                    ZSTD_isError_ptr;
   PTR_ZSTD_sizeof_DDict               ZSTD_sizeof_DDict_ptr;
   PTR_ZSTD_versionNumber              ZSTD_versionNumber_ptr;
};


extern struct zstd_handler_st zstd_handler;
extern struct zstd_handler_st *zstd_handler_ptr;


#define ZSTD_compress(...)                 zstd_handler.ZSTD_compress_ptr(__VA_ARGS__)
#define ZSTD_compressBound(...)            zstd_handler.ZSTD_compressBound_ptr(__VA_ARGS__)
#define ZSTD_compress_usingCDict(...)      zstd_handler.ZSTD_compress_usingCDict_ptr(__VA_ARGS__)
#define ZSTD_compress_usingDict(...)       zstd_handler.ZSTD_compress_usingDict_ptr(__VA_ARGS__)
#define ZSTD_createCCtx(...)               zstd_handler.ZSTD_createCCtx_ptr(__VA_ARGS__)
#define ZSTD_createCCtx_advanced(...)      zstd_handler.ZSTD_createCCtx_advanced_ptr(__VA_ARGS__)
#define ZSTD_createCDict(...)              zstd_handler.ZSTD_createCDict_ptr(__VA_ARGS__)
#define ZSTD_createDCtx(...)               zstd_handler.ZSTD_createDCtx_ptr(__VA_ARGS__)
#define ZSTD_createDCtx_advanced(...)      zstd_handler.ZSTD_createDCtx_advanced_ptr(__VA_ARGS__)
#define ZSTD_createDDict_byReference(...)  zstd_handler.ZSTD_createDDict_byReference_ptr(__VA_ARGS__)
#define ZSTD_decompress(...)               zstd_handler.ZSTD_decompress_ptr(__VA_ARGS__)
#define ZSTD_decompress_usingDDict(...)    zstd_handler.ZSTD_decompress_usingDDict_ptr(__VA_ARGS__)
#define ZSTD_decompress_usingDict(...)     zstd_handler.ZSTD_decompress_usingDict_ptr(__VA_ARGS__)
#define ZSTD_freeCCtx(...)                 zstd_handler.ZSTD_freeCCtx_ptr(__VA_ARGS__)
#define ZSTD_freeCDict(...)                zstd_handler.ZSTD_freeCDict_ptr(__VA_ARGS__)
#define ZSTD_freeDCtx(...)                 zstd_handler.ZSTD_freeDCtx_ptr(__VA_ARGS__)
#define ZSTD_freeDDict(...)                zstd_handler.ZSTD_freeDDict_ptr(__VA_ARGS__)
#define ZSTD_getErrorName(...)             zstd_handler.ZSTD_getErrorName_ptr(__VA_ARGS__)
#define ZSTD_isError(...)                  zstd_handler.ZSTD_isError_ptr(__VA_ARGS__)
#define ZSTD_sizeof_DDict(...)             zstd_handler.ZSTD_sizeof_DDict_ptr(__VA_ARGS__)
#define ZSTD_versionNumber(...)            zstd_handler.ZSTD_versionNumber_ptr(__VA_ARGS__)


#ifdef __cplusplus
}
#endif

#define SERVICE_ZSTD_INCLUDED
#endif