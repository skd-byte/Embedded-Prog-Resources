/**
 * @file      two_dim_cbuff.h
 * @authors   skd
 * @brief     This file is for interface for module.
 */
#ifndef CBUFF2D_H_
#define CBUFF2D_H_

#define FALSE 0
#define TRUE  1

#define MAXM_COLUMN_SIZE  300

typedef enum
{
  CBUFF_SUCCESS =0,
  CBUFF_FULL,
  CBUFF_NOT_FULL,
  CBUFF_EMPTY,
  CBUFF_NOT_EMPTY,
}CB_Status;

struct Cbuff2D_st
{
  uint32_t size;
  uint32_t length;
  uint32_t overflow;
  uint8_t (*base)[MAXM_COLUMN_SIZE];
  uint8_t (*head)[MAXM_COLUMN_SIZE];
  uint8_t (*tail)[MAXM_COLUMN_SIZE];
};
typedef struct Cbuff2D_st *cbuffHandle;

typedef struct Cbuff2D_st Cbuff2D_t;

extern CB_Status Cbuff2D_init(cbuffHandle cbuff, uint8_t (*buffer)[MAXM_COLUMN_SIZE], uint8_t flag, uint32_t size);
extern CB_Status Cbuff2D_get(cbuffHandle cbuff, uint8_t *buffer,uint32_t size);
extern CB_Status Cbuff2D_add(cbuffHandle cbuff, uint8_t *buffer,uint32_t size);
extern CB_Status Cbuff2D_IsEmpty(cbuffHandle cbuff);
extern CB_Status Cbuff2D_IsFull(cbuffHandle cbuff);
extern void Cbuff2D_flush(cbuffHandle cbuff);
extern uint32_t Cbuff2D_GetLength(cbuffHandle cbuff);



#endif //CBUFF2D_H_
