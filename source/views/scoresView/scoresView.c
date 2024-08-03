#include "scoresView.h"

static ScoresPage currentPage = SCORES_PAGE_BEGINNER;
static int scrollOffset = 0;

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
  int cursorY = 65;

  tte_set_pos(cursorX, cursorY);
  int i;
  for (i = scrollOffset; i < scrollOffset + SCORES_PER_PAGE; i++)
  {
    if (scores[i].time == -1)
    {
      char str[22];
      sprintf(str, "%02d)  -------", (i + 1));
      tte_write(str);
    }
    else
    {
      int totalSeconds = scores[i].time / 10;
      int minutes = totalSeconds / 60;
      int seconds = totalSeconds % 60;
      int remainingDeciseconds = scores[i].time % 10;
      minutes = minutes > 99 ? 99 : minutes;

      float _3bvs = (float)scores[i]._3bv / (float)totalSeconds;

      char str[355];
      sprintf(str, "%02d)  %02d:%02d.%d                                 %d    %.3f", (i + 1),
              minutes,
              seconds,
              remainingDeciseconds,
              scores[i]._3bv,
              _3bvs);
      tte_write(str);
    }

    cursorY += 15;
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
  if (key_hit(KEY_R) || key_hit(KEY_RIGHT))
  {
    scrollOffset = 0;
    currentPage = (currentPage + 1) % (SCORES_PAGE_EXPERT + 1);
  }
  if (key_hit(KEY_L) || key_hit(KEY_LEFT))
  {
    scrollOffset = 0;

    currentPage = (currentPage + (SCORES_PAGE_EXPERT)) % (SCORES_PAGE_EXPERT + 1);
  }
  if (key_hit(KEY_B))
  {
    set_view(VIEW_MAIN_MENU);
    return;
  }
  if (key_hit(KEY_DOWN))
  {
    if (scrollOffset != MAX_SCORES - SCORES_PER_PAGE)
    {
      scrollOffset++;
      display_scores();
    }
  }
  if (key_hit(KEY_UP))
  {
    if (scrollOffset != 0)
    {
      scrollOffset--;
      display_scores();
    }
  }
  if (currentPage != previousPage)
  {
    display_scores();
  }
}