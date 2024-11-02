/*        Your Name & E-mail: Nathan Ha    nha023@ucr.edu

*          Discussion Section: 22

 *         Assignment: Final Project

 *         Description: Music notes and songs go here

 *

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 */
#ifndef MUSIC_H
#define MUSIC_H

#include <avr/pgmspace.h>

// piano notes and their frequencies
const PROGMEM short C1 = 33;
const PROGMEM short CSHARP1_DFLAT1 = 35;
const PROGMEM short D1 = 37;
const PROGMEM short DSHARP1_EFLAT1 = 39;
const PROGMEM short E1 = 41;
const PROGMEM short F1 = 44;
const PROGMEM short FSHARP1_GFLAT1 = 46;
const PROGMEM short G1 = 49;
const PROGMEM short GSHARP1_AFLAT1 = 52;
const PROGMEM short A1 = 55;
const PROGMEM short ASHARP1_BFLAT1 = 58;
const PROGMEM short B1 = 62;

const PROGMEM short C2 = 65;
const PROGMEM short CSHARP2_DFLAT2 = 69;
const PROGMEM short D2 = 73;
const PROGMEM short DSHARP2_EFLAT2 = 78;
const PROGMEM short E2 = 82;
const PROGMEM short F2 = 87;
const PROGMEM short FSHARP2_GFLAT2 = 93;
const PROGMEM short G2 = 98;
const PROGMEM short GSHARP2_AFLAT2 = 104;
const PROGMEM short A2 = 110;
const PROGMEM short ASHARP2_BFLAT2 = 117;
const PROGMEM short B2 = 123;

const PROGMEM short C3 = 131;
const PROGMEM short CSHARP3_DFLAT3 = 139;
const PROGMEM short D3 = 147;
const PROGMEM short DSHARP3_EFLAT3 = 156;
const PROGMEM short E3 = 165;
const PROGMEM short F3 = 175;
const PROGMEM short FSHARP3_GFLAT3 = 185;
const PROGMEM short G3 = 196;
const PROGMEM short GSHARP3_AFLAT3 = 208;
const PROGMEM short A3 = 220;
const PROGMEM short ASHARP3_BFLAT3 = 233;
const PROGMEM short B3 = 247;

const PROGMEM short C4 = 262;
const PROGMEM short CSHARP4_DFLAT4 = 277;
const PROGMEM short D4 = 294;
const PROGMEM short DSHARP4_EFLAT4 = 311;
const PROGMEM short E4 = 330;
const PROGMEM short F4 = 349;
const PROGMEM short FSHARP4_GFLAT4 = 370;
const PROGMEM short G4 = 392;
const PROGMEM short GSHARP4_AFLAT4 = 415;
const PROGMEM short A4 = 440;
const PROGMEM short ASHARP4_BFLAT4 = 466;
const PROGMEM short B4 = 494;

const PROGMEM short C5 = 523;
const PROGMEM short CSHARP5_DFLAT5 = 554;
const PROGMEM short D5 = 587;
const PROGMEM short DSHARP5_EFLAT5 = 622;
const PROGMEM short E5 = 659;
const PROGMEM short F5 = 698;
const PROGMEM short FSHARP5_GFLAT5 = 740;
const PROGMEM short G5 = 784;
const PROGMEM short GSHARP5_AFLAT5 = 831;
const PROGMEM short A5 = 880;
const PROGMEM short ASHARP5_BFLAT5 = 932;
const PROGMEM short B5 = 988;

const PROGMEM short C6 = 1047;
const PROGMEM short CSHARP6_DFLAT6 = 1109;
const PROGMEM short D6 = 1175;
const PROGMEM short DSHARP6_EFLAT6 = 1245;
const PROGMEM short E6 = 1319;
const PROGMEM short F6 = 1397;
const PROGMEM short FSHARP6_GFLAT6 = 1480;
const PROGMEM short G6 = 1568;
const PROGMEM short GSHARP6_AFLAT6 = 1661;
const PROGMEM short A6 = 1760;
const PROGMEM short ASHARP6_BFLAT6 = 1865;
const PROGMEM short B6 = 1976;

const PROGMEM short C7 = 2093;
const PROGMEM short CSHARP7_DFLAT7 = 2217;
const PROGMEM short D7 = 2349;
const PROGMEM short DSHARP7_EFLAT7 = 2489;
const PROGMEM short E7 = 2637;
const PROGMEM short F7 = 2794;
const PROGMEM short FSHARP7_GFLAT7 = 2960;
const PROGMEM short G7 = 3136;
const PROGMEM short GSHARP7_AFLAT7 = 3322;
const PROGMEM short A7 = 3520;
const PROGMEM short ASHARP7_BFLAT7 = 3729;
const PROGMEM short B7 = 3951;

const short PROGMEM
    night_of_knights[] = {//D4, F4, E4, D4, C4, A4, E4, C4,  // intro
                         // D5, F5, E5, D5, C5, A5, E5, C5, C5, D4, F4, E4, D4, C4, A4, E4, C4, C4, D4, F4, E4,
                        //   D4, C4, A5, E5, C5, C5, D4, B4, C5, E5, D4, A4, G4, E4, F4, A4, G4, F4, E4, D4,  // chorus
                        //   A4, G4, A4, E4, F4, A4, C4, C4, D5, A5, G5, E5, F5, A5, G5, F5, E5, D5, A5, G5, A5,
                        //   E5, F5, A5, C5, C5, D5, A5, G5, E5, F5, A5, G5, F5, E5, D5, A5, G5, A5, E5, F5, A5,
                          C5, C5, A5, F5, E5, F5, E4, G5, F4, E5, F4, E5, C5, D5, A6, G5, A5,  // juice
                          C6, A5, G5, A5, A5, F5, E5, F5, E4, G5, F4, E5, F4, E5, C5, D5, A6, G5, A5, C6, A5,
                          G5, A5, A5, F5, E5, F5, E4, G5, F4, E5, F4, E5, C5, D5, A6, G5, A5, C6, A5, G5, A5,
                          A5, F5, E5, F5, E4, G5, F4, E5, F4, E5, C5, D5, A6, G5, A5, C6, A5, F4, F4, G4, G4,
                          G4, A4, A3, A4, A3, A4, C5, B5, C5, B5, C6, C6,  // intermission ? idk what to call it
                          A5, F5, E5, F5, E4, G5, F4, E5, F4, E5, C5, D5, A6, G5, A5, C6, A5, G5, A5, A5, F5,
                          E5, F5, E4, G5, F4, E5, F4, E5, C5, D5, A6, G5, A5, C6, A5, G5, A5, A5, F5, E5, F5,
                          E4, G5, F4, E5, F4, E5, C5, D5, A6, G5, A5, C6, A5, G5, A5, G4, G4, G4, A4, G4, F4,
                          E4, D4, G4, G4, F4, G4, F4, D4, C4};
const int night_of_knight_length = (sizeof(night_of_knights) / sizeof(night_of_knights[0]));

const short PROGMEM lavendar_town[] = {C6, G6, B6, FSHARP6_GFLAT6};
const int lavendar_town_length = (sizeof(lavendar_town) / sizeof(lavendar_town[0]));

const short PROGMEM bad_apple[] = {
    E4, FSHARP4_GFLAT4, G4, A4, B4, B4, E4, D5, B4, B4, E4, E4, B4, A4, G4, FSHARP4_GFLAT4, E4,
    FSHARP4_GFLAT4, G4, A4, B4, B4, A4, G4, FSHARP4_GFLAT4, B4, FSHARP4_GFLAT4, G4, FSHARP4_GFLAT4,
    E4, DSHARP5_EFLAT5, FSHARP4_GFLAT4, E4, FSHARP4_GFLAT4, G4,
    A4, B4, B4, A4, D5, E5, E5, FSHARP5_GFLAT5, G5, G5, E5, FSHARP5_GFLAT5, G5, A5, B5, B5, A5, 
    G5, A5, A5, FSHARP5_GFLAT5, FSHARP5_GFLAT5, G5, G5, A5, A5, E5, E5, E5, E5, E5, FSHARP5_GFLAT5,
    G5, G5, FSHARP5_GFLAT5, FSHARP5_GFLAT5, FSHARP5_GFLAT5, FSHARP5_GFLAT5, B4, B4, B4, B4, 
    FSHARP5_GFLAT5, FSHARP5_GFLAT5, FSHARP5_GFLAT5, FSHARP5_GFLAT5, G5, E5, E5, E5, E5, 
};

const int bad_apple_length = (sizeof(bad_apple) / sizeof(bad_apple[0]));

#endif  // piano_notes.h
