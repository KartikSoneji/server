#include <compression/lzo/lzo1x.h>

#define COMPRESSION_BZIP2   1 << 0
#define COMPRESSION_LZ4     1 << 1
#define COMPRESSION_LZMA    1 << 2
#define COMPRESSION_LZO     1 << 3
#define COMPRESSION_SNAPPY  1 << 4
#define COMPRESSION_ZLIB    1 << 5
#define COMPRESSION_ZSTD    1 << 6
#define COMPRESSION_AUTO    1 << 7


void init_compression();
void * safe_dlsym(void *, const char *);

int init_lzo(); 