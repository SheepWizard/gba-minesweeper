#include "highScores.h"

static const int MASK = 0xff;

static void add_highScore(const int score, int *list)
{
  int i;
  int prev = -1;
  for (i = 0; i < MAX_SCORES; i++)
  {
    if (prev != -1)
    {
      int temp = list[i];
      list[i] = prev;
      prev = temp;
    }
    else if (list[i] > score || list[i] == 65535)
    {
      prev = list[i];
      list[i] = score;
    }
  }
}

static void save_data_to_high_scores(SaveData *saveData, HighScores *highScores)
{
  int i, j;
  for (i = 0, j = 0; i < MAX_SCORES * 2; i += 2, j++)
  {
    int beginnerScore = (saveData->beginnerScores[i + 1] << 8) | saveData->beginnerScores[i];
    int intermediateScore = (saveData->intermediateScores[i + 1] << 8) | saveData->intermediateScores[i];
    int expertScore = (saveData->expertScores[i + 1] << 8) | saveData->expertScores[i];

    highScores->beginnerScores[j] = beginnerScore;
    highScores->intermediateScores[j] = intermediateScore;
    highScores->expertScores[j] = expertScore;
  }
}

static void high_scores_to_save_data(HighScores *highScores, SaveData *saveData)
{
  int i, j;
  for (i = 0, j = 0; i < MAX_SCORES; i++, j += 2)
  {
    u8 beginnerLower = highScores->beginnerScores[i] & MASK;
    u8 beginnerUpper = (highScores->beginnerScores[i] >> 8) & MASK;
    u8 intermediateLower = highScores->intermediateScores[i] & MASK;
    u8 intermediateUpper = (highScores->intermediateScores[i] >> 8) & MASK;
    u8 expertLower = highScores->expertScores[i] & MASK;
    u8 expertUpper = (highScores->expertScores[i] >> 8) & MASK;

    saveData->beginnerScores[j] = beginnerLower;
    saveData->beginnerScores[j + 1] = beginnerUpper;
    saveData->intermediateScores[j] = intermediateLower;
    saveData->intermediateScores[j + 1] = intermediateUpper;
    saveData->expertScores[j] = expertLower;
    saveData->expertScores[j + 1] = expertUpper;
  }
}

void save_score(const enum SCORES_SAVE type, const int score)
{
  SaveData *saveData = malloc(sizeof(SaveData));
  int code = sram_read(saveData, sizeof(SaveData));
  if (code != E_SUCCESS)
  {
    return;
  }

  HighScores *highScores = malloc(sizeof(HighScores));
  save_data_to_high_scores(saveData, highScores);

  switch (type)
  {
  case SAVE_BEGINNER:
    add_highScore(score, highScores->beginnerScores);
    break;
  case SAVE_INTERMEDIATE:
    add_highScore(score, highScores->intermediateScores);
    break;
  case SAVE_EXPERT:
    add_highScore(score, highScores->expertScores);
    break;
  }
  high_scores_to_save_data(highScores, saveData);
  sram_write(saveData, sizeof(SaveData));

  free(highScores);
  free(saveData);
}

int read_scores(HighScores *highScores)
{
  SaveData *saveData = malloc(sizeof(SaveData));
  int code = sram_read(saveData, sizeof(SaveData));
  if (code != E_SUCCESS)
  {
    return code;
  }

  save_data_to_high_scores(saveData, highScores);

  free(saveData);

  return code;
}