/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0.0                                           *
 ~ Date          05.12.22                                        ~
 ~ Description   Fixed Size Queue Header                         ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __FSQ__
#define __FSQ__

#include <stddef.h>

#include "queue.h" /* implementation using sll */

typedef struct fsq fsq_t;

fsq_t *FSQCreate(size_t capacity);

void *FSQPeek(const fsq_t *fsq);

int FSQEnqueue(fsq_t *fsq, const void *value);

void *FSQDequeue(fsq_t *fsq);

size_t FSQSize(const fsq_t *fsq);

void FSQDestroy(fsq_t *fsq);

int FSQIsEmpty(const fsq_t *fsq);

#endif /* __FSQ__ */
