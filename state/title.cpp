/*
 * state/title.cpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                  for the PicoSystem.
 *
 * This file implements the TitleState class; a simple welcome screen, with
 * enticing images and an invitation to press a button to start!
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
#include "state/title.hpp"
#include "assets/spritesheet.hpp"


/* Functions. */

/*
 * constructor - just initialises things like timers and assets.
 */

TitleState::TitleState( void )
{
  /* Remember what state we are! */
  this->m_state = GAMESTATE_TITLE;

  /* And set the timer to zero. */
  this->m_time_ms = 0;
  this->m_last_tick = 0;

  /* And the invader offset (we'll let them drift left and right) */
  this->m_invader_offset = 20;
  this->m_invader_ltor = true;

  /* All done. */
  return;
}


/*
 * destructor - tidy up any allocated resources.
 */

TitleState::~TitleState()
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

gamestate_t TitleState::update( uint32_t p_delta )
{
  /* Keep track of the passage of time. Note that the first delta may be */
  /* unnaturally large, so we need to dispense with it quietly.          */
  if ( this->m_time_ms == 0 )
  {
    this->m_time_ms = 1;
  }
  else
  {
    this->m_time_ms += p_delta;
  }

  /* The invaders will drift left and right, as a fairly leisurely pace. */
  if ( (this->m_time_ms - this->m_last_tick) > 300 )
  {
    /* Mark this tick. */
    this->m_last_tick = this->m_time_ms;

    /* And move the offset. */
    if ( this->m_invader_ltor )
    {
      if ( this->m_invader_offset >= 40 )
      {
        this->m_invader_ltor = false;
        this->m_invader_offset -= 2;
      }
      else
      {
        this->m_invader_offset += 2;
      }
    }
    else
    {
      if ( this->m_invader_offset == 0 )
      {
        this->m_invader_ltor = true;
        this->m_invader_offset += 2;
      }
      else
      {
        this->m_invader_offset -= 2;
      }
    }
  }

  /* Check to see if the player has pressed X, in order to start the game. */
  if ( picosystem::pressed( picosystem::X ) )
  {
    return GAMESTATE_SPLASH;
  }

  /* By default, stay in this state. */
  return this->m_state;
}


/*
 * draw - called whenever we need to draw our current state.
 */

void TitleState::draw( void )
{
  int32_t l_width, l_height;
  uint8_t l_alpha;

  /* Clear the screen every time... */
  picosystem::pen( 0, 0, 0 );
  picosystem::clear();

  /* Blit the title logo into the middle of the screen. */
  picosystem::blit( &spritesheet_buffer, SPRITE_TITLE_X, SPRITE_TITLE_Y, 
                    SPRITE_TITLE_W, SPRITE_TITLE_H,
                    (SCREEN_WIDTH - SPRITE_TITLE_W) / 2,
                    (SCREEN_HEIGHT - SPRITE_TITLE_H) / 2 );

  /* Draw some ... invaders! */
  for ( int i = 0; i < 10; i++ )
  {
    picosystem::sprite( SPRITE_INVADER1, (i*20) + this->m_invader_offset, 40 );
    picosystem::sprite( SPRITE_INVADER1+1, (i*20) + this->m_invader_offset + 8, 40 );
    picosystem::sprite( SPRITE_INVADER2, (i*20) + this->m_invader_offset, 60 );
    picosystem::sprite( SPRITE_INVADER2+1, (i*20) + this->m_invader_offset + 8, 60 );
  }

  /* And prompt the player to start. */
  l_alpha = 5 + abs(((this->m_time_ms/50)%20)-10);
  picosystem::pen( 10, 15, 15, l_alpha );
  picosystem::measure( "PRESS X TO START", l_width, l_height );
  picosystem::text( "PRESS X TO START", (SCREEN_WIDTH - l_width) / 2, 180 );

  /* And a little advertising... */
  picosystem::pen( 15, 8, 15, 10 );
  picosystem::measure( "github.com/ahnlak/picovaders", l_width, l_height );
  picosystem::text( "github.com/ahnlak/picovaders", 
                    (SCREEN_WIDTH - l_width) / 2, SCREEN_HEIGHT - l_height );

  /* DEBUG - superimpose the state name on the buffer. */
#ifdef DEBUG
  this->ident( "TITLE" );
#endif

  /* All done. */
  return;
}


/* End of file state/title.cpp */