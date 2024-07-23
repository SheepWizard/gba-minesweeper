#include "highScores.h"

static void add_highScore(const u32 score, volatile u32 *list)
{
  u32 i;
  u32 prev = -1;
  for (i = 0; i < MAX_SCORES; i++)
  {
    mgba_printf(LOG_INFO, "%d", list[i]);
    if (prev != -1)
    {
      int temp = list[i];
      list[i] = prev;
      prev = temp;
    }
    else if (list[i] > score || list[i] == 4294967295)
    {
      prev = list[i];
      list[i] = score;
    }
  }
}

void save_score(const ScoreSave type, const u32 score)
{
  volatile SaveData *saveData = sram_read();

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
}

volatile SaveData *read_scores()
{
  volatile SaveData *saveData = sram_read();
  return saveData;
}