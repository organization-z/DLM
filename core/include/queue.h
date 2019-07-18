#ifndef DLM_QUEUE_H
#define DLM_QUEUE_H

#include "dl.h"

#define MAX_QUEUE_CAP 1000

enum {
    QUEUE_TYPE_SYNC,
    QUEUE_TYPE_ASYNC
};

typedef struct {
    uint8_t type;
    bool is_running;

    char *default_proxy;
    char *default_proxy_auth;
    uint8_t default_proxy_type; // TODO add enum PROXY_TYPE

    char *default_save_location;

    uint16_t default_timeout; // in secs
    uint8_t default_max_connections_allowed;
    uint16_t default_speed_limit; // Kb/s
    uint8_t default_max_parts;
    uint8_t default_num_of_retries;

    FILE *dl_history;

    time_t start_date;
    time_t start_time;

    time_t stop_date;
    time_t stop_time;

    bool run_every_day;
    bool run_evey_week;
    uint8_t week_mask;

    bool start_at_startup;

    char *cmd_to_run_at_stop;

    dl downloads[MAX_QUEUE_CAP];
} queue;

extern queue queues[100];

// add_queue(...);

// delete_queue(queue *);


// start_queue(queue *);
// stop_queue(queue *);

// run_sync_queue(queue *);
// run_async_queue(queue *);

void add_dl_to_queue(queue *,dl *);
void remove_dl_from_queue(queue *,dl *);

void archive_dl(queue *,dl *);
void archive_queue(queue *);


#endif //DLM_QUEUE_H
