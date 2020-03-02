/**
 * @file      two_dim_cbuff.c
 * @authors   skd
 * @brief     This circular buffer implementation for
 *            two dimensional array.
 */

 /*******************************************************************************
* Includes
*******************************************************************************/
#include <stdlib.h>         // for printf
#include <stdint.h>         // for portable types
#include <assert.h>         // for assertion
#include <string.h>
#include "two_dim_cbuff.h"  // for public domain two dimensional circular buffer

/*******************************************************************************
* Functions
*******************************************************************************/

CB_Status Cbuff2D_init(cbuffHandle cbuff, uint8_t (*buffer)[MAXM_COLUMN_SIZE], uint8_t flag, uint32_t size)
{
  assert(cbuff && buffer && size);

  cbuff->size     = size;
  cbuff->length   = 0;
  cbuff->overflow = flag;   // overflow flag
  cbuff->base     = buffer;
  cbuff->head     = cbuff->base;
  cbuff->tail     = cbuff->base;
  return CBUFF_SUCCESS;
}

CB_Status Cbuff2D_add(cbuffHandle cbuff, uint8_t *buffer,uint32_t size)
{
  assert(cbuff); // check cbuff initialize or created
  if((Cbuff2D_IsFull(cbuff) == CBUFF_FULL) && cbuff->overflow == FALSE)
  {
    return CBUFF_FULL;
  }
  else
  {
    memcpy((uint8_t *)*(cbuff->head),(uint8_t *)buffer,size);

    if(cbuff->head == ( cbuff->base + (cbuff->size-1)))
    {
      cbuff->head = cbuff->base;
    }
    else
    {
      cbuff->head++;
    }
  }
  return CBUFF_SUCCESS;
}

CB_Status Cbuff2D_get(cbuffHandle cbuff, uint8_t *buffer,uint32_t size)
{
  assert(cbuff);
  if(Cbuff2D_IsEmpty(cbuff) == CBUFF_EMPTY)
  {
    return CBUFF_EMPTY;
  }
  else
  {
    memcpy((uint8_t *)buffer,(uint8_t *)(*cbuff->tail),size);

    if(cbuff->tail == (cbuff->base + (cbuff->size - 1)))
    {
      cbuff->tail = cbuff->base;
    }
    else
    {
      cbuff->tail++;
    }
  }
  return CBUFF_SUCCESS;
}

CB_Status Cbuff2D_IsEmpty(cbuffHandle cbuff)
{
  if(cbuff->head == cbuff->tail)
  {
    return CBUFF_EMPTY;
  }
  else
  {
    return CBUFF_NOT_EMPTY;
  }
}

CB_Status Cbuff2D_IsFull(cbuffHandle cbuff)
{
  if((cbuff->head == cbuff->tail + cbuff->size - 1) ||
    ((cbuff->head + 1) == cbuff->tail))
  {
    return CBUFF_FULL;
  }
  else
  {
    return CBUFF_NOT_FULL;
  }
}

uint32_t Cbuff2D_GetLength(cbuffHandle cbuff)
{
  if(cbuff->head > cbuff->tail)
  {
    return (cbuff->head - cbuff->tail);   
  }                                                    
  else
  {
    return ((cbuff->head - cbuff->base) + ((cbuff->base + cbuff->size) - cbuff->tail));
  }
}

void Cbuff2D_flush(cbuffHandle cbuff)
{
  assert(cbuff);
  cbuff->head = cbuff->base;
  cbuff->tail = cbuff->base;
}
/*** end of file ***/
