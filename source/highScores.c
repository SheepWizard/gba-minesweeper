#include "highScores.h"

static void add_highScore(const WinScore newScore, WinScore *list)
{
  int i;
  int replaceIndex = 0;

  for (i = MAX_SCORES - 1; i >= 0; i--)
  {
    if (list[i].time > newScore.time || list[i].time == -1)
    {
      replaceIndex = i;
    }
  }

  WinScore prev = list[replaceIndex];
  list[replaceIndex].time = newScore.time;
  list[replaceIndex]._3bv = newScore._3bv;
  list[replaceIndex].flags = newScore.flags;

  for (i = replaceIndex + 1; i < MAX_SCORES; i++)
  {
    WinScore temp = list[i];
    list[i] = prev;
    prev = temp;
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