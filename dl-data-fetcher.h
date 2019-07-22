#ifndef downloadH
#define downloadH
#include "download.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

int fetch_dl_data_http(Download *);
size_t get_header(char *, size_t, size_t, void *);
void extract_header_data(Download *);