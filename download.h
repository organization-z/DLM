typedef struct DownloadStrct
{
    unsigned int type;
    void *dl_engine;
    char *url;
    char *auth;
    char *proxy;
    char *proxy_auth;
    char *header;
    char *content_type;
    unsigned int resumable:1;
    int max_cons_allowed;
    unsigned int spd_lmt;
    unsigned int progrees;
    int size;

} Download;
