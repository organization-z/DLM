#include "dl-data-fetcher.h"

int fetch_dl_data_http(Download *download)
{
    //getting the header of the file
    CURL *handle;
    CURLcode resp;
    download -> header = malloc(0);
    handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, download->url);
    curl_easy_setopt(handle, CURLOPT_HEADER, 1L);
    curl_easy_setopt(handle, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
    // curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, get_header);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, download);
    resp = curl_easy_perform(handle);
    curl_easy_cleanup(handle);
    
    if(resp != CURLE_OK)
    {
        fprintf(stderr, "failed to get header: %s\n", curl_easy_strerror(resp));
        return -1;
    }
    extract_header_data(download);
    printf("%ld\n-%s\n%s", download->size, download->content_type ,download->header);
    return 0;
}
size_t get_header(char *buffer, size_t size, size_t nmemb, void *download)
{
    Download *d = download;
    d->header = realloc(d->header, (strlen(d->header) + 1)*sizeof(char) + nmemb);
    strcat(d->header, buffer);
    return nmemb;
}
res_st extract_header_data(Download *download)
{
    // returns: '-1' -> HTTP response header not provided  '-2' -> header provided but response code wasn't 200

    // getting response code and skipping to the download header (if redirected)
    char *sdp; // start of data pointer
    char *tmp;
    int res_code = 0;
    res_st res; 
    u_int8_t http_header_found = 0;
    sdp = strstr(download->header, "HTTP");
    if (sdp == NULL)
    {
        download->size = -1;
        download->content_type = NULL;
        res.code = -1;
        return res;
    }

    find_next_header:
    while (*sdp != ' ' && *sdp != '\0')
        sdp++;
    if (*sdp == '\0')
    {
        download->size = -1;
        download->content_type = NULL;
        if (!http_header_found)
        {
            res.code = -1;
            return res;
        }
        res.code = -2;
        res.sec_code = res_code;
        return res; 
    }

    http_header_found = 1;
    sdp++;
    res_code = 0;
    while (*sdp >= '0' && *sdp <= '9')
    {
        res_code *= 10; res_code += (*sdp) - '0';
        sdp++;
    }
    if (res_code != 200)
    {
        sdp = strstr(sdp, "HTTP");
        if (sdp != NULL)
            goto find_next_header;
        
        download->size = -1;
        download->content_type = NULL;
        if (!http_header_found)
        {
            res.code = -1;
            return res;
        }
        res.code = -2;
        res.sec_code = res_code;
        return res; 
    }
    //


    tmp = strstr(sdp, "Content-Length: ");
    //getting content length
    long size = 0;
    if (tmp == NULL)
    {
        //if Content-Length is not provided the download size will be -1
        download->size = -1;
    }
    else
    {
        tmp += strlen("Content-Length: ");
        while (*tmp >= '0' && *tmp <= '9')
        {
            size *= 10; size += (*tmp) - '0';
            tmp++;
        }
        download->size = size;
    }
    //

    //getting content type
    char *cntntype = malloc(sizeof(char)); cntntype[0] = '\0';
    tmp = strstr(sdp, "Content-Type: ");
    if (sdp == NULL)
    {
        //if Content-type is not provided the download content_type will be NULL
        download->content_type = NULL;
    }
    else
    {
        sdp += strlen("Content-Type: ");
        int i = 0 ;
        while (*tmp != '\n' && *tmp != '\r' && *tmp != '\0' && *tmp != ';' && *tmp != ',')
        {
            cntntype = realloc(cntntype, (strlen(cntntype) + 2) * sizeof(char));
            cntntype[i] = *tmp;
            cntntype[i + 1] = '\0';
            tmp++; i++;
        }
        download->content_type = cntntype;
    }
    //
}
