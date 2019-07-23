
#ifndef downloadH
#define downloadH
#include "download.h"
#endif

#ifndef ddfH
#define ddfH
#include "dl-data-fetcher.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

int main(void)
{
  Download d;
  d.url = "http://cdn.p30download.com/?b=p30dl-software&f=PowerArchiver.2019.Standard.v19.00.50_p30download.com.rar";
  fetch_dl_data_http(&d);

  return 0;
}