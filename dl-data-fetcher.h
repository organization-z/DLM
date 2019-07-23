#ifndef downloadH
#define downloadH
#include "download.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

typedef struct
{
    int8_t code;
    int8_t sec_code;
    char *msg;
}res_st; // response struct
int fetch_dl_data_http(Download *);
size_t get_header(char *, size_t, size_t, void *);
res_st extract_header_data(Download *);