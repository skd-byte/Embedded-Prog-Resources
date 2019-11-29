/** @file smart_cbuff.h
 *  @authors   skd
 *  @brief this is interface of circulr buffer which only take size in power of Two
 *
 */
#ifndef SMART_CBUFF_H_
#define SMART_CBUFF_H_

#include <stdint.h>         // for portable types

typedef enum
{
  CB_SUCCESS =0,
  CB_FULL,
  CB_NOT_FULL,
  CB_EMPTY,
  CB_NOT_EMPTY,
}CB_Status;

struct Cbuff_st
{
  size_t  size;
  size_t  head;
  size_t  tail;
  uint8_t *buffer;
};

typedef struct Cbuff_st *cbuffHandle;
typedef struct Cbuff_st Cbuff_t;

#define LENGTH(x)       (x->head - x->tail)

void Cbuff_init(cbuffHandle cbuff, uint8_t * buffer, uint8_t size);
CB_Status Cbuff_put(cbuffHandle cbuff,uint8_t data);
CB_Status Cbuff_pop(cbuffHandle cbuff,uint8_t *getData);
CB_Status Cbuff_IsFull(cbuffHandle cbuff);
CB_Status Cbuff_IsEmpty(cbuffHandle cbuff);
void Cbuff_flush(cbuffHandle cbuff);

#endif // SMART_CBUFF_H_
/*** end of file ***/