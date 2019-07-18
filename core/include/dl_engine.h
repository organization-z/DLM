#ifndef DLM_DL_ENGINE_H
#define DLM_DL_ENGINE_H

#include <stdint.h>

#include "dl.h"

typedef struct {
    uint8_t (*download)(dl *download);
    uint8_t (*get_header)(dl *download);

} dl_engine;

#endif //DLM_DL_ENGINE_H
