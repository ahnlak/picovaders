/*
 * state/title.hpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                  for the PicoSystem.
 *
 * This file defines the TitleState class; a simple welcome screen, with
 * enticing images and an invitation to press a button to start!
 *
 * Copyright (c) 2022 Pete Favelle <picosystem@ahnlak.com>
 * This file is distributed under the MIT License; see LICENSE for details.
 */

#pragma once

class TitleState : public GameStateInterface
{
private:
  uint_fast32_t   m_last_tick;
  uint_fast32_t   m_time_ms;
  uint_fast8_t    m_invader_offset;
  bool            m_invader_ltor;

public:
                  TitleState( void );
                 ~TitleState();

  gamestate_t     update( uint32_t );
  void            draw( void );
};


/* End of file state/title.hpp */
