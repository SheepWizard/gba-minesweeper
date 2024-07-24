#include "scoresView.h"

static ScoresPage currentPage = SCORES_PAGE_BEGINNER;

static void display_scores()
{
  TTC *context = tte_get_context();
  context->eraseProc(0, 0, M3_WIDTH, M3_HEIGHT);

  SaveData *saveData = read_scores();

  u32 scores[MAX_SCORES];

  switch (currentPage)
  {
  case SCORES_PAGE_BEGINNER:
    memcpy32(scores, saveData->beginnerScores, MAX_SCORES);
    break;
  case SCORES_PAGE_INTERMEDIATE:
    memcpy32(scores, saveData->intermediateScores, MAX_SCORES);
    break;
  case SCORES_PAGE_EXPERT:
    memcpy32(scores, saveData->expertScores, MAX_SCORES);
    break;
  }

  int cursorX = 0;
  int cursorY = 0;
  tte_set_pos(cursorX, cursorY);
  u32 i;
  for (i = 0; i < MAX_SCORES; i++)
  {
    char str[16];
    sprintf(str, "%d", scores[i]);
    tte_write(str);
    cursorY += 20;
    tte_set_pos(0, cursorY);
  }

  free(saveData);
}

void init_scores_view()
{
  m3_fill(CLR_BLACK);
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