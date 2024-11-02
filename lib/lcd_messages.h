#ifndef LCD_MESSAGE_H
#define LCD_MESSAGE_H

#include "game_logic.h"

// message displayed during gameplay
void gameplay_message() {
  char tmp[16] = "";
  strncpy(lcd_message_top, "Boss hp:", 16 - 1);
  lcd_message_top[16 - 1] = '\0';

  snprintf(tmp, sizeof(tmp), "%d", health_boss);
  strncat(lcd_message_top, tmp, 16 - strlen(lcd_message_top) - 1);

  strncpy(lcd_message_bottom, "Time: ", 16 - 1);
  lcd_message_bottom[16 - 1] = '\0';

  snprintf(tmp, sizeof(tmp), "%d", elapsed_time_seconds);
  strncat(lcd_message_bottom, tmp, 16 - strlen(lcd_message_bottom) - 1);
  strncat(lcd_message_bottom, ".", 16 - strlen(lcd_message_bottom) - 1);

  snprintf(tmp, sizeof(tmp), "%d", elapsed_time_ms);
  strncat(lcd_message_bottom, tmp, 16 - strlen(lcd_message_bottom) - 1);
  strncat(lcd_message_bottom, " s", 16 - strlen(lcd_message_bottom) - 1);
}

// message displayed after dying
void death_message() {
  char tmp[16] = "";
  strncpy(lcd_message_top, "You Died...L", 16 - 1);
  lcd_message_top[16 - 1] = '\0';

  strncpy(lcd_message_bottom, "Time: ", 16 - 1);
  lcd_message_bottom[16 - 1] = '\0';

  snprintf(tmp, sizeof(tmp), "%d", elapsed_time_seconds);
  strncat(lcd_message_bottom, tmp, 16 - strlen(lcd_message_bottom) - 1);
  strncat(lcd_message_bottom, ".", 16 - strlen(lcd_message_bottom) - 1);

  snprintf(tmp, sizeof(tmp), "%d", elapsed_time_ms);
  strncat(lcd_message_bottom, tmp, 16 - strlen(lcd_message_bottom) - 1);
  strncat(lcd_message_bottom, " s", 16 - strlen(lcd_message_bottom) - 1);
}

void pause_message() {
  char tmp[16] = "";
  strncpy(lcd_message_top, "PAUSED     HS->", 16 - 1);
  lcd_message_top[16 - 1] = '\0';

  strncpy(lcd_message_bottom, "Time: ", 16 - 1);
  lcd_message_bottom[16 - 1] = '\0';

  snprintf(tmp, sizeof(tmp), "%d", elapsed_time_seconds);
  strncat(lcd_message_bottom, tmp, 16 - strlen(lcd_message_bottom) - 1);
  strncat(lcd_message_bottom, ".", 16 - strlen(lcd_message_bottom) - 1);

  snprintf(tmp, sizeof(tmp), "%d", elapsed_time_ms);
  strncat(lcd_message_bottom, tmp, 16 - strlen(lcd_message_bottom) - 1);
  strncat(lcd_message_bottom, " s", 16 - strlen(lcd_message_bottom) - 1);
}

void win_message() {
  char tmp[16] = "";
  strncpy(lcd_message_top, "YOU'RE WINNER!!!!!", 16 - 1);
  lcd_message_top[16 - 1] = '\0';

  strncpy(lcd_message_bottom, "Time: ", 16 - 1);
  lcd_message_bottom[16 - 1] = '\0';

  snprintf(tmp, sizeof(tmp), "%d", elapsed_time_seconds);
  strncat(lcd_message_bottom, tmp, 16 - strlen(lcd_message_bottom) - 1);
  strncat(lcd_message_bottom, ".", 16 - strlen(lcd_message_bottom) - 1);

  snprintf(tmp, sizeof(tmp), "%d", elapsed_time_ms);
  strncat(lcd_message_bottom, tmp, 16 - strlen(lcd_message_bottom) - 1);
  strncat(lcd_message_bottom, " s", 16 - strlen(lcd_message_bottom) - 1);
}

void high_score_message() {
  const short current_best_seconds = eeprom_read_word(0);
  const short current_best_msec = eeprom_read_word(2);
  char tmp[16] = "";
  strncpy(lcd_message_top, "<- Menu", 16 - 1);
  lcd_message_top[16 - 1] = '\0';

  strncpy(lcd_message_bottom, "#1: ", 16 - 1);
  lcd_message_bottom[16 - 1] = '\0';

  snprintf(tmp, sizeof(tmp), "%d", current_best_seconds);
  strncat(lcd_message_bottom, tmp, 16 - strlen(lcd_message_bottom) - 1);
  strncat(lcd_message_bottom, ".", 16 - strlen(lcd_message_bottom) - 1);

  snprintf(tmp, sizeof(tmp), "%d", current_best_msec);
  strncat(lcd_message_bottom, tmp, 16 - strlen(lcd_message_bottom) - 1);
  strncat(lcd_message_bottom, " s", 16 - strlen(lcd_message_bottom) - 1);
}

#endif