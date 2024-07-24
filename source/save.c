// Taken from https://github.com/laqieer/libsavgba/tree/main

#include "save.h"

IWRAM_CODE static void sram_memcpy(volatile unsigned char *dst, const volatile unsigned char *src, size_t size)
{
  for (; size > 0; --size)
    *dst++ = *src++;
}

EWRAM_CODE void sram_write(SaveData *saveData)
{
  sram_memcpy(sram_mem, (u8 *)saveData, sizeof(SaveData));
  free(saveData);
}

EWRAM_CODE SaveData *sram_read()
{
  SaveData *saveData = malloc(sizeof(SaveData));
  sram_memcpy((u8 *)saveData, sram_mem, sizeof(SaveData));

  return saveData;
}
