#include "seed.h"

void load_seed()
{
  volatile SaveData *saveData = sram_read();

  srand(saveData->seed);
}

void update_seed(int value)
{
  volatile SaveData *saveData = sram_read();

  u16 newSeed = (saveData->seed + value);
  srand(newSeed);
  saveData->seed = newSeed;
}