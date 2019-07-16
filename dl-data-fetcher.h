#ifndef downloadH
#define downloadH
#include "download.h"
#endif

#ifndef stdioH
#define stdioH
#include <stdio.h>
#endif

#ifndef stringH
#define stringH
#include <string.h>
#endif

#ifndef stdlibH
#define stdlibH
#include <stdlib.h>
#endif

#ifndef curlH
#define curlH
#include <curl/curl.h>
#endif

int fetch_dl_data_http(Download *);
size_t get_header(char *, size_t, size_t, void *);
void extract_header_data(Download *);