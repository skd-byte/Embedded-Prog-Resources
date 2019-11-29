/** @file smart_cbuff.c
 *  @authors   skd
 *  @brief this is module of circulr buffer which only take size in power of Two
 *
 */
#include <stdlib.h>         // for printf
#include <stdint.h>         // for portable types
#include <assert.h>         // for assertion
#include "smart_cbuff.h"  // for public domain smart circular buffer


#define IsPowerOfTwo(x) (x && (!(x&(x-1))))


/*!
 * @brief initialize cbuff and also check that size should be power of two
 *        for auto wrap the counter
 *
 * @param[in] cbuff
 * @param[in] buffer
 * @param[in] size
 * @return
 */
void Cbuff_init(cbuffHandle cbuff, uint8_t * buffer, uint8_t size)
{
  assert(cbuff && cbuff->size);
  assert(IsPowerOfTwo(cbuff->size)); // NOTE: size must be power of two

  cbuff->head     = 0;
  cbuff->tail     = 0;
  cbuff->buffer   = buffer;
}  /* Cbuff_init() */


/*!
 * @brief add data to circular buffer
 *
 * @param[in] cbuff
 * @param[in] data
 * @return
 */
CB_Status Cbuff_put(cbuffHandle cbuff,uint8_t data)
{
  if(LENGTH(cbuff) >= cbuff->size)
  {
    return CB_FULL;
  }
  cbuff->buffer[cbuff->head & (cbuff->size-1)] = data;
  cbuff->head++;

  return CB_SUCCESS;
} /* Cbuff_put() */

/*!
 * @brief pop data from circular buffer to passed pointer to data
 *
 * @param[in] cbuff
 * @param[in] getdata passed address of location where data will get
 * @return    status
 */
CB_Status Cbuff_pop(cbuffHandle cbuff,uint8_t *getData )
{
  if(LENGTH(cbuff) == 0)
  {
    return CB_EMPTY;
  }
  *getData = cbuff->buffer[cbuff->tail & (cbuff->size-1)];
  cbuff->tail++;

  return CB_SUCCESS;
} /* Cbuff_pop() */


/*!
 * @brief Check that buffer is full or not
 *
 * @param[in] cbuff
 * @return    status
 */
CB_Status Cbuff_IsFull(cbuffHandle cbuff)
{
   if(LENGTH(cbuff) >= cbuff->size)
  {
    return CB_FULL;
  }
  else
  {
    return CB_NOT_FULL;
  }
} /* Cbuff_IsFull() */

/*!
 * @brief Check that buffer is Empty or not
 *
 * @param[in] cbuff
 * @return    status
 */
CB_Status Cbuff_IsEmpty(cbuffHandle cbuff)
{
  if(LENGTH(cbuff) == 0)
  {
    return CB_EMPTY;
  }
  else
  {
    return CB_NOT_EMPTY;
  }
} /* Cbuff_IsEmpty() */

/*!
 * @brief flush all data of the buffer
 *
 * @param[in] cbuff
 * @return
 */
void Cbuff_flush(cbuffHandle cbuff)
{
  cbuff->head = 0;
  cbuff->tail = 0;
} /* Cbuff_flush() */
/*** end of file ***/











