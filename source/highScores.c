#include "highScores.h"

static int compare(const void *a, const void *b)
{
  WinScore aScore = *(WinScore *)a;
  WinScore bScore = *(WinScore *)b;

  if (aScore.time == -1)
  {
    return 1;
  }
  if (bScore.time == -1)
  {
    return -1;
  }
  if (aScore.time == bScore.time)
  {
    return 0;
  }
  else if (aScore.time < bScore.time)
  {
    return -1;
  }
  else
  {
    return 1;
  }
}

static void add_highScore(const WinScore newScore, WinScore *list)
{
  WinScore sort[MAX_SCORES + 1];
  memcpy(sort, list, sizeof(WinScore) * MAX_SCORES);
  sort[MAX_SCORES] = newScore;

  qsort(sort, MAX_SCORES + 1, sizeof(WinScore), compare);
  memcpy(list, sort, sizeof(WinScore) * MAX_SCORES);
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