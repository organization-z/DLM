#ifndef DLM_DL_H
#define DLM_DL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "dl_engine.h"

// TODO add enum status

enum {
    DL_STATUS_FINISHED,
    DL_STATUS_ERROR,
    DL_STATUS_RESUMED,
    DL_STATUS_NOT_STARTED,
    DL_STATUS_STOPPED,
};

typedef struct {
    uint64_t content_length;
    // TODO: content_MD5
    bool accept_ranges;
    // TODO: content_type
} dl_header;

typedef struct {
    dl_part *next;
    uint64_t start_byte;
    uint64_t end_byte;
    uint64_t downloaded;
    uint16_t cached;
    FILE  *file_data;
    uint8_t *cache_data;
} dl_part;

typedef struct {
    char *url;
    char *auth;
    char *proxy;
    char *proxy_auth;
    uint8_t proxy_type; // TODO add enum PROXY_TYPE

    char *save_location;
    char *file_name;

    dl_engine *engine;

    // http header data
    dl_header header;

    uint16_t timeout; // in secs
    uint8_t max_connections_allowed;
    uint16_t speed_limit; // Kb/s
    uint8_t max_parts;
    uint8_t num_of_retries;

    time_t datetime_added;
    time_t datetime_finished;

    uint8_t status;
    dl_part *first_part;
} dl;

/* requires:
 * get_header_data(dl *)
 * returns status code
 */
uint8_t init_dl(dl *);

/* requires:
 * make_parts(dl *)
 * dl.dl_engine.download(dl *,dl_part *)
 * returns status code
 */
uint8_t start_download(dl *);


uint8_t stop_download(dl *);

uint8_t pause_download(dl *);

uint8_t resume_download(dl *);

/* required by download
uint8_t guess_dl_engine(dl *);

/* requires dl.dl_engine.get_header
 * required by start_download(dl *)
 * returns status code
 */
uint8_t get_header_data(dl *);

/* succeeds get_header_data(dl *)
 * required by start_download(dl *)
 * returns status code
 */
uint8_t make_parts(dl *);

/* required by start_download(dl *)
 * returns status code
 */
uint8_t split_part(dl_part *);

#endif //DLM_DL_H
