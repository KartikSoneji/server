#include <compression/lzma.h>

void init_compression(struct compression_service_lzma_st *);
void * safe_dlsym(void *, const char *);

void init_lzma(struct compression_service_lzma_st *);