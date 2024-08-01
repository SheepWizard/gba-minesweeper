#pragma once
#include "tonc.h"
#include <stddef.h>
#include <stdlib.h>

#define MAX_SCORES 20

enum ErrorCode
{
  E_SUCCESS = 0,
  E_INVALID_PARAM,
  E_OUT_OF_RANGE,
  E_VERIFY_FAIL,
  E_UNSUPPORTED_DEVICE,
  E_TIMEOUT,
};

typedef struct WinScore
{
  u32 time;
  int _3bv;
  int flags;
} WinScore;

typedef struct SaveData
{
  u16 seed;
  WinScore beginnerScores[MAX_SCORES];
  WinScore intermediateScores[MAX_SCORES];
  WinScore expertScores[MAX_SCORES];
} SaveData;

EWRAM_CODE void sram_write(SaveData *saveData);
EWRAM_CODE SaveData *sram_read();
