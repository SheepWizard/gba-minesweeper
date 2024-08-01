#include "scoresView.h"

static ScoresPage currentPage = SCORES_PAGE_BEGINNER;

static void display_scores()
{
  memcpy(vid_mem, highscore_screenBitmap, M3_SIZE);

  SaveData *saveData = read_scores();

  WinScore scores[MAX_SCORES];

  switch (currentPage)
  {
  case SCORES_PAGE_BEGINNER:
    memcpy(scores, saveData->beginnerScores, sizeof(WinScore) * MAX_SCORES);
    break;
  case SCORES_PAGE_INTERMEDIATE:
    memcpy(scores, saveData->intermediateScores, sizeof(WinScore) * MAX_SCORES);
    break;
  case SCORES_PAGE_EXPERT:
    memcpy(scores, saveData->expertScores, sizeof(WinScore) * MAX_SCORES);
    break;
  }

  int cursorX = 10;
  int cursorY = 50;

  tte_set_pos(cursorX, cursorY);
  u32 i;
  for (i = 0; i < MAX_SCORES; i++)
  {
    if (scores[i].time == -1)
    {
      char str[8];
      sprintf(str, "-------");
      tte_write(str);
    }
    else
    {
      int totalSeconds = scores[i].time / 10;
      int minutes = totalSeconds / 60;
      int seconds = totalSeconds % 60;
      int remainingDeciseconds = scores[i].time % 10;
      minutes = minutes > 99 ? 99 : minutes;
      char str[13];
      sprintf(str, "%02d:%02d.%d", minutes, seconds, remainingDeciseconds);
      tte_write(str);
    }

    cursorY += 20;
    tte_set_pos(cursorX, cursorY);
  }

  free(saveData);
}

void init_scores_view()
{
  memcpy(vid_mem, highscore_screenBitmap, M3_SIZE);
  currentPage = SCORES_PAGE_BEGINNER;
  tte_init_bmp_default(3);
  tte_set_ink(CLR_BLACK);
  display_scores();
}

void update_scores_view()
{
  ScoresPage previousPage = currentPage;
  if (key_hit(KEY_R))
  {
    currentPage = (currentPage + 1) % (SCORES_PAGE_EXPERT + 1);
  }
  if (key_hit(KEY_L))
  {
    currentPage = (currentPage + (SCORES_PAGE_EXPERT - 1)) % (SCORES_PAGE_EXPERT + 1);
  }
  if (key_hit(KEY_B))
  {
    set_view(VIEW_MAIN_MENU);
    return;
  }
  if (currentPage != previousPage)
  {
    display_scores();
  }
}