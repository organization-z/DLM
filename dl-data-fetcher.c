#include "dl-data-fetcher.h"

int fetch_dl_data_http(Download *download)
{
    //getting the header of the file
    CURL *handle;
    CURLcode res;
    download -> header = malloc(0);
    handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, download->url);
    curl_easy_setopt(handle, CURLOPT_HEADER, 1L);
    curl_easy_setopt(handle, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
    // curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, get_header);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, download);
    res = curl_easy_perform(handle);
    curl_easy_cleanup(handle);
    //
    // if(res != CURLE_OK)
    // {
    //     fprintf(stderr, "failed to get header: %s\n", curl_easy_strerror(res));
    //     return -1;
    // }
    extract_header_data(download);
    printf("%ld\n%s\n%s", download->size, download->content_type ,download->header);
    return 0;
}
size_t get_header(char *buffer, size_t size, size_t nmemb, void *download)
{
    Download *d = download;
    d->header = realloc(d->header, (strlen(d->header) + 1)*sizeof(char) + nmemb);
    strcat(d->header, buffer);
    return nmemb;
}
void extract_header_data(Download *download)
{
    char *sdp = strstr(download->header, "Content-Length: "); // start of data pointer
    
    //getting content length
    long size = 0;
    if (sdp == NULL)
    {
        //if Content-Length is not provided the download size will be -1
        download->size = -1;
    }
    else
    {
        sdp += strlen("Content-Length: ");
        while (*sdp >= '0' && *sdp <= '9')
        {
            size *= 10; size += (*sdp) - '0';
            sdp++;
        }
        download->size = size;
    }
    //

    //getting content type
    char *cntntype = malloc(sizeof(char)); cntntype[0] = '\0';
    sdp = strstr(download->header, "Content-Type: ");
    if (sdp == NULL)
    {
        //if Content-type is not provided the download content_type will be NULL
        download->content_type = NULL;
    }
    else
    {
        sdp += strlen("Content-Type: ");
        int i = 0 ;
        while (*sdp != '\n' && *sdp != '\r' && *sdp != '\0' && *sdp != ';' && *sdp != ',')
        {
            cntntype = realloc(cntntype, (strlen(cntntype) + 2) * sizeof(char));
            cntntype[i] = *sdp;
            cntntype[i + 1] = '\0';
            sdp++; i++;
        }
        download->content_type = cntntype;
    }
    //
}
