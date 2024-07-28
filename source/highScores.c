#include "highScores.h"

static void add_highScore(const WinScore newScore, WinScore *list)
{
  int i;
  WinScore prev;
  prev.time = -1;
  for (i = 0; i < MAX_SCORES; i++)
  {
    mgba_printf(LOG_INFO, "%d", list[i]);
    if (prev.time != -1)
    {
      int temp = list[i].time;
      list[i] = prev;
      prev.time = temp;
    }
    else if (list[i].time > newScore.time)
    {
      prev = list[i];
      list[i].time = newScore.time;
      list[i]._3bv = newScore._3bv;
      list[i].flags = newScore.flags;
    }
  }
}

void save_score(const ScoreSave type, const WinScore newScore)
{
  SaveData *saveData = sram_read();

  switch (type)
  {
  case SAVE_BEGINNER:
    add_highScore(newScore, saveData->beginnerScores);
    break;
  case SAVE_INTERMEDIATE:
    add_highScore(newScore, saveData->intermediateScores);
    break;
  case SAVE_EXPERT:
    add_highScore(newScore, saveData->expertScores);
    break;
  }

  sram_write(saveData);
}

SaveData *read_scores()
{
  SaveData *saveData = sram_read();
  return saveData;
}