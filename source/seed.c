#include "seed.h"

void load_seed()
{
  SaveData *data = malloc(sizeof(SaveData));
  int code = sram_read(data);
  if (code != E_SUCCESS)
  {
    return;
  }

  srand(data->seed);
  free(data);
}

void update_seed(int value)
{
  SaveData *data = malloc(sizeof(SaveData));
  int code = sram_read(data);
  if (code != E_SUCCESS)
  {
    return;
  }

  int newSeed = ((u16)data->seed + value);
  srand(newSeed);
  data->seed = (u8)newSeed;

  sram_write(data);
  free(data);
}