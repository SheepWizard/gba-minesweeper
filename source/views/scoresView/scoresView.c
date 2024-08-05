#include "scoresView.h"

static ScoresPage currentPage = SCORES_PAGE_BEGINNER;
static int scrollOffset = 0;

static void draw_difficulty()
{
  switch (currentPage)
  {
  case SCORES_PAGE_BEGINNER:

    break;
  case SCORES_PAGE_INTERMEDIATE:

    break;
  case SCORES_PAGE_EXPERT:

    break;
  default:
    break;
  }
}

static void draw_labels()
{
  tte_set_pos(30, 65);
  char timeLabel[5];
  sprintf(timeLabel, "Time");
  tte_write(timeLabel);

  tte_set_pos(110, 65);
  char nfLabel[3];
  sprintf(nfLabel, "NF");
  tte_write(nfLabel);

  tte_set_pos(150, 65);
  char _3bvLabel[4];
  sprintf(_3bvLabel, "3BV");
  tte_write(_3bvLabel);

  tte_set_pos(190, 65);
  char _3bvsLabel[6];
  sprintf(_3bvsLabel, "3BV/S");
  tte_write(_3bvsLabel);

  tte_set_pos(4, 71);
  char line[59];
  sprintf(line, "----------------------------------------------------------");
  tte_write(line);
}

static void draw_time(const u32 time)
{
  int totalSeconds = time / 10;
  int minutes = totalSeconds / 60;
  int seconds = totalSeconds % 60;
  int remainingDeciseconds = time % 10;
  minutes = minutes > 99 ? 99 : minutes;
  char timeText[20];
  sprintf(timeText, "  %02d:%02d.%d",
          minutes,
          seconds,
          remainingDeciseconds);
  tte_write(timeText);
}

static void draw_no_flag(const bool nf)
{
  char nfText[6];
  sprintf(nfText, nf ? "True" : "False");
  tte_write(nfText);
}

static void draw_3bv(const int _3bv)
{
  char _3bvText[12];
  sprintf(_3bvText, "%d", _3bv);
  tte_write(_3bvText);
}

static void draw_3bvs(const float _3bvs)
{
  char _3bvsText[12];
  sprintf(_3bvsText, "%.3f", _3bvs);
  tte_write(_3bvsText);
}

static void display_scores()
{
  memcpy(vid_mem, highscore_screenBitmap, M3_SIZE);

  draw_difficulty();
  draw_labels();

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
  int cursorY = 80;

  tte_set_pos(cursorX, cursorY);
  int i;
  for (i = scrollOffset; i < scrollOffset + SCORES_PER_PAGE; i++)
  {
    char positionText[13];
    sprintf(positionText, "%02d)", i + 1);
    tte_write(positionText);
    if (scores[i].time == -1)
    {
      char lineText[10];
      sprintf(lineText, "  -------");
      tte_write(lineText);
    }
    else
    {
      draw_time(scores[i].time);
      tte_set_pos(106, cursorY);
      draw_no_flag(scores[i].noFlag);
      tte_set_pos(152, cursorY);
      draw_3bv(scores[i]._3bv);

      int totalSeconds = scores[i].time / 10;
      float _3bvs = (float)scores[i]._3bv / (float)totalSeconds;
      tte_set_pos(191, cursorY);
      draw_3bvs(_3bvs);
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
  if ((key_repeat(KEY_DOWN)) && scrollOffset != MAX_SCORES - SCORES_PER_PAGE)
  {
    scrollOffset++;
    display_scores();
  }
  if ((key_repeat(KEY_UP)) && scrollOffset != 0)
  {

    scrollOffset--;
    display_scores();
  }
  if (currentPage != previousPage)
  {
    display_scores();
  }
}