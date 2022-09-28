/*
 * state/splash.cpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                   for the PicoSystem.
 *
 * This file implements the SplashState class; one of a series of handlers which
 * implement a single state in the game.
 *
 * This particular state simply fades a logo in and out, when the game is first
 * booted up.
 *
 * Copyright (c) 2022 Pete Favelle <picosystem@ahnlak.com>
 * This file is distributed under the MIT License; see LICENSE for details.
 */

/* System headers. */

/* Local headers. */

#include "picosystem.hpp"
#include "picovaders.hpp"
#include "state/splash.hpp"
#include "assets/logo_ahnlak_1bit.hpp"


/* Functions. */

/*
 * constructor - just initialises things like timers and assets.
 */

SplashState::SplashState( void )
{
  /* Remember what state we are! */
  this->m_state = GAMESTATE_SPLASH;

  /* And set the timer to zero. */
  this->m_time_ms = 0;

  /* All done. */
  return;
}


/*
 * destructor - tidy up any allocated resources.
 */

SplashState::~SplashState()
{
  /* All done. */
  return;
}


/*
 * update - called every frame to update the state; passed a delta indicating
 *          the ms since the last time we were called, and can be used for
 *          pacing.
 * Returns the gamestate we should end up in; usually this is ourselves, but
 * allows this state to determine if/when we change to another.
 */

gamestate_t SplashState::update( uint32_t p_delta )
{
  /* Keep track of the passage of time. Note that the first delta may be */
  /* unnaturally large, so we need to dispense with it quietly.          */
#if 0
  if ( this->m_time_ms == 0 )
  {
    this->m_time_ms = 1;
  }
  else
#endif
  {
    this->m_time_ms += p_delta;
  }

  /* If we've splashed for 2 seconds, we can move on. */
  if ( this->m_time_ms > 2000 )
  {
    return GAMESTATE_TITLE;
  }

  /* By default, stay in this state. */
  return this->m_state;
}


/*
 * draw - called whenever we need to draw our current state.
 */

void SplashState::draw( void )
{
  uint8_t l_alpha = 0, l_green;

  /* Clear the screen every time... */
  picosystem::pen( 0, 0, 0 );
  picosystem::clear();

  /* Work out the alpha to give a nice fade, 1/2 second up, 1 pause, 1/2 down. */
  if ( this->m_time_ms < 500 )
  {
    l_alpha = this->m_time_ms * 15 / 500;
  }
  else if ( this->m_time_ms < 1500 )
  {
    l_alpha = 15;
  }
  else if ( this->m_time_ms < 2000 )
  {
    l_alpha = 15 - ( ( this->m_time_ms - 1500 ) * 15 / 500 );
  }


  /* Render the 1bit logo, fast as we can. */
  const uint8_t *l_logo = logo_ahnlak_1bit_data;
  for ( uint_fast8_t y = 24; y < 216; y++ )
  {
    /* Select a suitable pen, based on the fade up/down. */
    l_green = (((y+this->m_time_ms/10)%200)/20)+5;

    picosystem::pen( 15, l_green, 15, l_alpha );

    /* And draw the line data. */
    for ( uint_fast8_t x = 24; x < 216; x += 8 )
    {
      for ( uint_fast8_t bit = 0; bit < 8; bit++ )
      {
        if ( *l_logo & ( 0b10000000 >> bit ) )
        {
          picosystem::pixel( x + bit, y );
        }
      }
      l_logo++;
    }
  }

  /* All done. */
  return;
}


/* End of file state/splash.cpp */
