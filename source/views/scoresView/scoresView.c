#include "scoresView.h"

static ScoresPage currentPage = SCORES_PAGE_BEGINNER;

static void display_scores()
{
  TTC *context = tte_get_context();
  context->eraseProc(0, 0, M3_WIDTH, M3_HEIGHT);

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

  int cursorX = 0;
  int cursorY = 0;
  tte_set_pos(cursorX, cursorY);
  u32 i;
  for (i = 0; i < MAX_SCORES; i++)
  {
    char str[sizeof(WinScore)];
    sprintf(str, "%d, %d, %d", scores[i].time, scores[i].flags, scores[i]._3bv);
    tte_write(str);
    cursorY += 20;
    tte_set_pos(0, cursorY);
  }

  free(saveData);
}

void init_scores_view()
{
  memcpy(vid_mem, highscore_screenBitmap, M3_SIZE);
  currentPage = SCORES_PAGE_BEGINNER;
  tte_init_bmp_default(3);
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