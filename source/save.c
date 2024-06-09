// https://github.com/laqieer/libsavgba/tree/main

#include "save.h"
#include <stddef.h>

IWRAM_CODE static void sram_memcpy(volatile unsigned char *dst, const volatile unsigned char *src, size_t size)
{
  for (; size > 0; --size)
    *dst++ = *src++;
}

IWRAM_CODE static unsigned int sram_absmemcmp(const volatile unsigned char *dst, const volatile unsigned char *src, size_t size)
{
  while (size-- > 0)
  {
    unsigned int a = *dst++;
    unsigned int b = *src++;
    if (a != b)
      return 1;
  }

  return 0;
}

int sram_read(SaveData *data, size_t size)
{
  if (data == NULL)
    return E_INVALID_PARAM;

  if (size > SRAM_SIZE)
    return E_OUT_OF_RANGE;

  sram_memcpy((u8 *)data, sram_mem, size);

  return 0;
}

int sram_write(SaveData *data, size_t size)
{
  if (data == NULL)
    return E_INVALID_PARAM;

  if (size > SRAM_SIZE)
    return E_OUT_OF_RANGE;

  sram_memcpy(sram_mem, (u8 *)data, size);

  if (sram_absmemcmp(sram_mem, (u8 *)data, size))
    return E_VERIFY_FAIL;

  return 0;
}
