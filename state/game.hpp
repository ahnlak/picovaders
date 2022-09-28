/*
 * state/game.hpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                 for the PicoSystem.
 *
 * This file defines the GameState class; the core of the game, this lasts until
 * the player loses their last life and we move into the death state.
 *
 * Copyright (c) 2022 Pete Favelle <picosystem@ahnlak.com>
 * This file is distributed under the MIT License; see LICENSE for details.
 */

#pragma once

#include "utils/tick.hpp"

#define SHEET_WIDTH   10
#define SHEET_HEIGHT  5
#define PLAYER_WIDTH  15
#define PLAYER_LASER  4

struct explosion_t
{
  uint_fast8_t x;
  uint_fast8_t y;
  uint_fast8_t sprite;
  bool         wide;
};

#define MAX_EXPLOSIONS 15

class GameState : public GameStateInterface
{
private:
  uint_fast32_t   m_time_ms;
  int_fast16_t    m_invader_offset;
  uint_fast8_t    m_invader_descent;
  bool            m_invader_ltor;
  uint_fast8_t    m_invaders[SHEET_HEIGHT][SHEET_WIDTH];
  TickCounter    *m_invader_tick;
  TickCounter    *m_base_tick;
  TickCounter    *m_bullet_tick;
  TickCounter    *m_explosion_tick;

  explosion_t     m_explosion_list[MAX_EXPLOSIONS+1];

  coord_t         m_player_base_loc;
  coord_t         m_player_bullet_loc;
  bool            m_player_firing;
  uint32_t        m_score;

  void            load_level( void );
  coord_t         get_invader_location( uint_fast8_t, uint_fast8_t );
  coord_t         get_invader_position( uint_fast8_t, uint_fast8_t );

  void            update_player( void );
  void            update_bullet( void );
  void            add_explosion( uint_fast8_t, uint_fast8_t, uint_fast8_t, bool );
  void            update_explosions( void );
  void            update_invaders( int_fast16_t );

public:
                  GameState( void );
                 ~GameState();

  gamestate_t     update( uint32_t );
  void            draw( void );
};


/* End of file state/game.hpp */
