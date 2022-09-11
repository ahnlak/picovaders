/*
 * state/splash.hpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                   for the PicoSystem.
 *
 * This file defines the SplashState class; one of a series of handlers which
 * implement a single state in the game.
 *
 * Copyright (c) 2022 Pete Favelle <picosystem@ahnlak.com>
 * This file is distributed under the MIT License; see LICENSE for details.
 */

#pragma once

class SplashState : public GameStateInterface
{
private:
  uint_fast16_t   m_time_ms;

public:
                  SplashState( void );
                 ~SplashState();

  gamestate_t     update( uint32_t );
  void            draw( void );
};


/* End of file state/splash.hpp */
