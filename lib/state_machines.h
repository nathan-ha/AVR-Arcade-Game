/*        Your Name & E-mail: Nathan Ha    nha023@ucr.edu

*          Discussion Section: 22

 *         Assignment: Final Project

 *         Description: State Machine Logic Goes Here

 *

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 */
#ifndef STATE_MACHINES_H
#define STATE_MACHINES_H

#include <stdio.h>
#include <string.h>
#include <avr/eeprom.h>

#include "../lib/LCD.h"
#include "../lib/game_logic.h"
#include "../lib/helper.h"
#include "../lib/irAVR.h"
#include "../lib/music.h"
#include "../lib/periph.h"
#include "../lib/serialATmega.h"
#include "../lib/spiAVR.h"
#include "../lib/timerISR.h"
#include "../lib/lcd_messages.h"

const unsigned short BUZZER_PERIOD = 150;
const unsigned short GAME_PERIOD = 50;
const unsigned short DISPLAY_PERIOD = GAME_PERIOD;
const unsigned short LCD_PERIOD = 200;
const unsigned short IR_PERIOD = 100;

enum passive_buzzer_state { PBUZZER_INIT, PLAY, PLAY_DEATH, PLAY_WIN };
int tick_passive_buzzer(int state) {

  switch (state) {
    case PBUZZER_INIT:
      state = PLAY;
      break;
    case PLAY:
      if (health_player <= 0) {
        state = PLAY_DEATH;
        song_tick = 0;
      } else if (win) {
        state = PLAY_WIN;
        song_tick = 0;
      }
      break;
    case PLAY_DEATH:
      if (health_player > 0) {
        state = PLAY;
        song_tick = 0;
      }
      break;
    case PLAY_WIN:
      if (!win) {
        state = PLAY;
        song_tick = 0;
      }
      break;
    default:
      break;
  }

  switch (state) {
    case PLAY:
      pbuzzer_change_freq(pgm_read_word(&bad_apple[song_tick]));
      song_tick = (song_tick + 1) %  bad_apple_length;
      break;
    case PLAY_DEATH:
      pbuzzer_change_freq(pgm_read_word(&lavendar_town[song_tick]));
      song_tick = (song_tick + 1) % lavendar_town_length;
      break;
    case PLAY_WIN:
      pbuzzer_change_freq(pgm_read_word(&night_of_knights[song_tick]));
      song_tick = (song_tick + 1) % night_of_knight_length;
    default:
      break;
  }
  return state;
}

enum display_state { DISPLAY_INIT, REFRESH };
int tick_display(int state) {
  switch (state) {
    case DISPLAY_INIT:
      state = REFRESH;
      break;
    case REFRESH:
      break;
    default:
      break;
  }
  switch (state) {
    case REFRESH:
      draw_game_screen();
      break;
    default:
      break;
  }
  return state;
}

enum game_state { GAME_INIT, GAME_START, GAME_PLAYING, GAME_PAUSE, GAME_LOSE, GAME_WIN, GAME_HIGHSCORE };
int tick_game(int state) {
  switch (state) {
    case GAME_INIT:
      state = GAME_START;
      break;
    case GAME_START:
      state = GAME_PAUSE;
      break;
    case GAME_PLAYING:
      if (win) {
        state = GAME_WIN;
      } else if (ir_value == PAUSE_IR) {
        state = GAME_PAUSE;
        ir_value = -1;
      } else if (ir_value == POWER_IR) {
        state = GAME_START;
        ir_value = -1;
      }
      if (health_player <= 0) state = GAME_LOSE;
      break;
    case GAME_PAUSE:
      if (ir_value == PAUSE_IR) {
        state = GAME_PLAYING;
        ir_value = -1;
      } else if (ir_value == POWER_IR) {
        state = GAME_START;
        ir_value = -1;
      } else if (ir_value == RIGHT_IR) {
        state = GAME_HIGHSCORE;
        ir_value = -1;
      }
      break;
    case GAME_LOSE:
      if (ir_value == POWER_IR) {
        state = GAME_START;
        ir_value = -1;
      }
      break;
    case GAME_WIN:
      if (ir_value == POWER_IR) {
        state = GAME_START;
        ir_value = -1;
      }
      break;
    case GAME_HIGHSCORE:
      if (ir_value == LEFT_IR) {
        state = GAME_PAUSE;
        ir_value = -1;
      } else if (ir_value == POWER_IR) {
        state = GAME_START;
        ir_value = -1;
      }
      break;
    default:
      break;
  }

  switch (state) {
    case GAME_START:
      TFT_FLUSH();
      game_init();
      elapsed_time_ms = 0;
      elapsed_time_seconds = 0;
      break;
    case GAME_PLAYING:
      if ((elapsed_time_ms += GAME_PERIOD) >= 1000) {
        elapsed_time_ms = 0;
        elapsed_time_seconds++;
      }
      gameplay_message();
      game_loop();
      break;
    case GAME_PAUSE:
      pause_message();
      break;
    case GAME_LOSE:
      TFT_DRAW_RECTANGLE(0, 0, 130, 130, 0xFFF);
      death_message();
      TFT_DRAW_RECTANGLE(0, 0, 130, 130, 0xFFF);
      break;
    case GAME_WIN:
      update_best_time();
      win_message();
      break;
    case GAME_HIGHSCORE:
      high_score_message();
      break;
    default:
      break;
  }
  return state;
}

enum lcd_state { LCD_INIT, LCD_CLEAR, LCD_TOP, LCD_BOTTOM };
int tick_lcd(int state) {
  switch (state) {
    case LCD_INIT:
      state = LCD_CLEAR;
      break;
    case LCD_CLEAR:
      state = LCD_TOP;
      break;
    case LCD_TOP:
      state = LCD_BOTTOM;
      break;
    case LCD_BOTTOM:
      state = LCD_INIT;
      break;
    default:
      break;
  }
  switch (state) {
    case LCD_CLEAR:
      lcd_clear();
      break;
    case LCD_TOP:
      lcd_goto_xy(0, 0);
      lcd_write_str(lcd_message_top);
      break;
    case LCD_BOTTOM:
      lcd_goto_xy(1, 0);
      lcd_write_str(lcd_message_bottom);
      break;
    default:
      break;
  }
  return state;
}

enum ir_state { IR_INIT, IR_RECEIVE };
int tick_ir(int state) {
  switch (state) {
    case IR_INIT:
      state = IR_RECEIVE;
      break;
    case IR_RECEIVE:
      break;
    default:
      break;
  }
  switch (state) {
    case IR_RECEIVE:
      decode_results d;
      if (IRdecode(&d)) {
        if (d.value > 0) ir_value = d.value;
        IRresume();
      }
      break;
    default:
      break;
  }
  return state;
}

#endif
