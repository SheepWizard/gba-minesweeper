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

void update_seed(u8 value)
{
  SaveData *data = malloc(sizeof(SaveData));
  int code = sram_read(data);
  if (code != E_SUCCESS)
  {
    return;
  }

  u8 newSeed = (data->seed + value) % 255;

  srand(newSeed);
  data->seed = newSeed;

  sram_write(data);
  free(data);
}