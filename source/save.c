// Taken from https://github.com/laqieer/libsavgba/tree/main

#include "save.h"

EWRAM_CODE volatile SaveData *save_data_get(void)
{
  return (SaveData *)MEM_SRAM;
}

EWRAM_CODE volatile SaveData *sram_read()
{
  volatile SaveData *saveData = save_data_get();
  return saveData;
}
