/*
 * picovaders.cpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                 for the PicoSystem.
 *
 * This is the main entry point, and provides the init/update/draw trinity of
 * functions expected by the PicoSystem SDK.
 *
 * Copyright (c) 2022 Pete Favelle <picosystem@ahnlak.com>
 * This file is distributed under the MIT License; see LICENSE for details.
 */

/* System headers. */

/* Local headers. */

#include "picosystem.hpp"
#include "picovaders.hpp"
#include "state/game.hpp"
#include "state/splash.hpp"
#include "state/title.hpp"
#include "assets/spritesheet.hpp"


/* Module variables. */

gamestate_t         m_next_state;
uint32_t            m_last_frame_ms;
GameStateInterface *m_current_state = nullptr;


/* Functions. */

/*
 * init - the PicoSystem SDK entry point; called when the game is launched. 
 */

void init( void )
{
  /* Set our initial gamestate to the splash screen. */
  m_next_state = GAMESTATE_SPLASH;

  /* Set the last frame time to now. */
  m_last_frame_ms = picosystem::time();

  /* Load up the spritesheet. */
  picosystem::spritesheet( &spritesheet_buffer );

  /* All done. */
  return;
}


/*
 * update - called from the PicoSystem SDK every frame to update the world.
 *          Passed a count of update frames since the game launched. This is
 *          *probably* around 40Hz, but it's not guaranteed so we need to
 *          measure time for ourselves.
 */

void update( uint32_t p_tick )
{
  uint32_t l_delta, l_current_frame_ms;

  /* Work out our delta from the last update; this will always be needed. */
  l_current_frame_ms = picosystem::time();
  l_delta = l_current_frame_ms - m_last_frame_ms;
  m_last_frame_ms = l_current_frame_ms;

  /* Check to see if we've been requested to switch states. */
  if ( ( m_current_state == nullptr ) ||
       ( m_current_state->get_state() != m_next_state ) )
  {
    /* If we have a current state, delete it. */
    if ( m_current_state != nullptr )
    {
      delete m_current_state;
      m_current_state = nullptr;
    }

    /* Create the right state object now. */
    switch( m_next_state )
    {
      case GAMESTATE_SPLASH:
        m_current_state = new SplashState();
        break;
      case GAMESTATE_TITLE:
        m_current_state = new TitleState();
        break;
      case GAMESTATE_GAME:
        m_current_state = new GameState();
        break;
    }
  }

  /* We can now just ask the state object to update itself. */
  if ( m_current_state != nullptr )
  {
    m_next_state = m_current_state->update( l_delta );
  }

  /* All done. */
  return;
}


/*
 * draw - called from the PicoSystem SDK every frame to draw the world. As with
 *        update, although this aspires to be 40Hz, it may not be. As this is
 *        pure presentation, however, we don't need to worry unduly about this.
 */

void draw( uint32_t p_tick )
{
  /* Because this is just a render operation, timings and states don't change. */
  if ( m_current_state != nullptr )
  {
    m_current_state->draw();
  }

  /* All done. */
  return;
}


/* End of file picovaders.cpp */
