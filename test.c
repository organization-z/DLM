
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

#ifndef ddfH
#define ddfH
#include "dl-data-fetcher.h"
#endif


int main(void)
{
  Download d;
  d.url = "http://example.com";
  fetch_dl_data_http(&d);

  return 0;
}