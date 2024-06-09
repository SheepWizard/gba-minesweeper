#include "highScores.h"

static void add_highScore(const u8 score, u8 *list)
{
  u8 i;
  u8 prev = -1;
  for (i = 0; i < MAX_SCORES; i++)
  {
    if (list[i] > score || list[i] == 255)
    {
      prev = list[i];
      list[i] = score;
    }
    if (prev != -1)
    {
      u8 temp = list[i];
      list[i] = prev;
      prev = temp;
    }
  }
}

void save_score(const enum SCORES_SAVE type, const u8 score)
{
  SaveData *saveData = malloc(sizeof(SaveData));
  int code = sram_read(saveData, sizeof(SaveData));
  if (code != E_SUCCESS)
  {
    return;
  }

  mgba_printf(LOG_INFO, "%d", score);

  switch (type)
  {
  case SAVE_BEGINNER:
    add_highScore(score, saveData->beginnerScores);
    break;
  case SAVE_INTERMEDIATE:
    add_highScore(score, saveData->intermediateScores);
    break;
  case SAVE_EXPERT:
    add_highScore(score, saveData->expertScores);
    break;
  }

  sram_write(saveData, sizeof(SaveData));

  free(saveData);
}