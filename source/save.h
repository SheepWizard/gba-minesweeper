#pragma once
#include "tonc.h"
#include <stddef.h>

#define MAX_SCORES 5

enum ErrorCode
{
  E_SUCCESS = 0,        ///< No error.
  E_INVALID_PARAM,      ///< Invalid input parameter.
  E_OUT_OF_RANGE,       ///< Address is out of range.
  E_VERIFY_FAIL,        ///< Failed to verify written data.
  E_UNSUPPORTED_DEVICE, ///< Device type is not supported.
  E_TIMEOUT,            ///< Operation timeout.
};

typedef struct SaveData
{
  u8 beginnerScores[MAX_SCORES * 2];
  u8 intermediateScores[MAX_SCORES * 2];
  u8 expertScores[MAX_SCORES * 2];
} SaveData;

int sram_read(SaveData *data, size_t size);
int sram_write(SaveData *data, size_t size);
