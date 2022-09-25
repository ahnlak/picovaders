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

  coord_t         m_player_base_loc;
  coord_t         m_player_bullet_loc;
  bool            m_player_firing;

  void            load_level( void );

  void            update_player( void );
  void            move_invaders( int_fast16_t );

public:
                  GameState( void );
                 ~GameState();

  gamestate_t     update( uint32_t );
  void            draw( void );
};


/* End of file state/game.hpp */
