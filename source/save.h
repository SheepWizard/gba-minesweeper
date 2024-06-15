#pragma once
#include "tonc.h"
#include <stddef.h>

#define MAX_SCORES 5

enum ErrorCode
{
  E_SUCCESS = 0,
  E_INVALID_PARAM,
  E_OUT_OF_RANGE,
  E_VERIFY_FAIL,
  E_UNSUPPORTED_DEVICE,
  E_TIMEOUT,
};

typedef struct SaveData
{
  u8 beginnerScores[MAX_SCORES * 2];
  u8 intermediateScores[MAX_SCORES * 2];
  u8 expertScores[MAX_SCORES * 2];
} SaveData;

int sram_read(SaveData *data, size_t size);
int sram_write(SaveData *data, size_t size);
