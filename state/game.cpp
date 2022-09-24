/*
 * state/game.cpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                 for the PicoSystem.
 *
 * This file implements the GameState class; the core of the game, this lasts
 * until the player loses their last life and we move into the death state.
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
#include "assets/spritesheet.hpp"
#include "state/game.hpp"
#include "utils/tick.hpp"


/* Functions. */

/*
 * constructor - just initialises things like timers and assets.
 */

GameState::GameState( void )
{
  /* Remember what state we are! */
  this->m_state = GAMESTATE_GAME;

  /* And set the timer to zero. */
  this->m_time_ms = 0;

  /* Intialise the various tickers. */
  this->m_invader_tick = new TickCounter( 400 );
  this->m_base_tick = new TickCounter( 20 );

  /* And the invader offset (we'll let them drift left and right) */
  this->m_invader_offset = 20;
  this->m_invader_descent = 20;
  this->m_invader_ltor = true;

  /* Position the player roughly in the middle. */
  this->m_player_base_loc.x = ( SCREEN_WIDTH - PLAYER_WIDTH ) / 2;
  this->m_player_base_loc.y = 220;
  this->m_player_firing = false;

  /* Do the initial level load. */
  this->load_level();

  /* All done. */
  return;
}


/*
 * destructor - tidy up any allocated resources.
 */

GameState::~GameState()
{
  /* Clean up the tickers. */
  if ( this->m_invader_tick != nullptr )
  {
    delete this->m_invader_tick;
    this->m_invader_tick = nullptr;
  }
  if ( this->m_base_tick != nullptr )
  {
    delete this->m_base_tick;
    this->m_base_tick = nullptr;
  }

  /* All done. */
  return;
}


/*
 * load_level - fills the sheet of invaders with, well, invaders.
 */

void GameState::load_level( void )
{
  uint_fast8_t l_index, l_row;

  /* Pretty simple stuff; the first row is invader3 and the next two, type 2 */
  for ( l_index = 0; l_index < SHEET_WIDTH; l_index++ )
  {
    this->m_invaders[0][l_index] = INVADER3;
    this->m_invaders[1][l_index] = INVADER2;
    this->m_invaders[2][l_index] = INVADER2;
  }

  /* The remaining rows are fileld with type 1. */
  for ( l_row = 3; l_row < SHEET_HEIGHT; l_row++ )
  {
    for ( l_index = 0; l_index < SHEET_WIDTH; l_index++ )
    {
      this->m_invaders[l_row][l_index] = INVADER1;
    }  
  }
}


/*
 * update_player - runs all the player updates for a tick; basically check the
 *                 user inputs and issue appropriate commands.
 */

void GameState::update_player( void )
{
  /* So, if the user wants to go left (and can), move them. */
  if ( picosystem::button( picosystem::LEFT ) )
  {
    /* Simply move within screen boundaries. */
    if ( this->m_player_base_loc.x > 0 )
    {
      this->m_player_base_loc.x--;
    }
  }

  /* Also right. */
  if ( picosystem::button( picosystem::RIGHT ) )
  {
    /* Simply move within screen boundaries. */
    if ( this->m_player_base_loc.x < ( SCREEN_WIDTH - PLAYER_WIDTH ) )
    {
      this->m_player_base_loc.x++;
    }
  }

  /* Check to see if the player has fired, and hasn't already got one flying. */
  if ( picosystem::pressed( picosystem::X ) && ( !this->m_player_firing ) )
  {
    /* Work out the location of the bullet. */
    this->m_player_bullet_loc.x = this->m_player_base_loc.x + PLAYER_LASER;
    this->m_player_bullet_loc.y = this->m_player_base_loc.y;

    /* And set it flying. */
    this->m_player_firing = true;
  }

  /* All done. */
}


/*
 * update - called every frame to update the state; passed a delta indicating
 *          the ms since the last time we were called, and can be used for
 *          pacing.
 * Returns the gamestate we should end up in; usually this is ourselves, but
 * allows this state to determine if/when we change to another.
 */

gamestate_t GameState::update( uint32_t p_delta )
{
  uint_fast8_t  l_first_column, l_last_column, l_invader_count;
  uint_fast8_t  l_row, l_column;
  uint_fast16_t l_tick_length;
  int_fast16_t  l_offset_limit;

  /* Keep track of the passage of time. Note that the first delta may be */
  /* unnaturally large, so we need to dispense with it quietly.          */
  if ( this->m_time_ms == 0 )
  {
    this->m_time_ms = 1;
  }
  else
  {
    /* Update our internal time count. */
    this->m_time_ms += p_delta;

    /* And also our tickers. */
    this->m_invader_tick->add_delta( p_delta );
    this->m_base_tick->add_delta( p_delta );
  }

  /* First order of the day, move any bullets and bombs in flight. */

  /* Scan the sheet, to work out both how many invaders remain, and the  */
  /* first and last occupied columns, which determines turn points.      */
  l_invader_count = 0;
  l_last_column = 0;
  l_first_column = SHEET_WIDTH;

  for( l_row = 0; l_row < SHEET_HEIGHT; l_row++ )
  {
    for( l_column = 0; l_column < SHEET_WIDTH; l_column++ )
    {
      /* If it's empty, move on. */
      if( this->m_invaders[l_row][l_column] == INVADER_NONE )
      {
        continue;
      }

      /* Increase the invader count. */
      l_invader_count++;

      /* If the current column is less that the current first, count it. */
      if ( l_first_column > l_column )
      {
        l_first_column = l_column;
      }

      /* Also the last. */
      if ( l_last_column < l_column )
      {
        l_last_column = l_column;
      }
    }
  }

  /* And now we can derive the tick rate and limits from this, and move them. */
  l_tick_length = 150 + l_invader_count;
  if ( this->m_invader_ltor )
  {
    l_offset_limit = 44;
  }
  else
  {
    l_offset_limit = 0;
  }

  /* The invaders will drift left and right, as a fairly leisurely pace. */
  while( this->m_invader_tick->ticked() )
  {
    /* And move the offset. */
    if ( this->m_invader_ltor )
    {
      if ( this->m_invader_offset >= l_offset_limit )
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
      if ( this->m_invader_offset == l_offset_limit )
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

  /* Handle the player. */
  while( this->m_base_tick->ticked() )
  {
    this->update_player();
  }

  /* By default, stay in this state. */
  return this->m_state;
}


/*
 * draw - called whenever we need to draw our current state.
 */

void GameState::draw( void )
{
  int32_t       l_width, l_height;
  uint8_t       l_alpha;
  uint32_t      l_invader1, l_invader2, l_invader3;
  uint_fast8_t  l_row, l_column;
  int32_t       l_invader_x, l_invader_y;
  int32_t       l_bullet;

  /* Clear the screen every time... */
  picosystem::pen( 0, 0, 0 );
  picosystem::clear();

  /* Draw some ... invaders! */
  if ( this->m_invader_tick->get_count() % 2 )
  {
    l_invader1 = SPRITE_INVADER1;
    l_invader2 = SPRITE_INVADER2;
    l_invader3 = SPRITE_INVADER3;
    l_bullet = SPRITE_BULLET;
  }
  else
  {
    l_invader1 = SPRITE_INVADER1_ALT;
    l_invader2 = SPRITE_INVADER2_ALT;
    l_invader3 = SPRITE_INVADER3_ALT;
    l_bullet = SPRITE_BULLET_ALT;
  }

  for( l_row = 0; l_row < SHEET_HEIGHT; l_row++ )
  {
    for( l_column = 0; l_column < SHEET_WIDTH; l_column++ )
    {
      /* Work out the co-ordinates. */
      l_invader_x = ( l_column * 20 ) + this->m_invader_offset;
      l_invader_y = ( l_row * 20 ) + this->m_invader_descent;

      /* And render the right thing. */
      switch( this->m_invaders[l_row][l_column] )
      {
        case INVADER1:
          picosystem::sprite( l_invader1, l_invader_x, l_invader_y );
          picosystem::sprite( l_invader1+1, l_invader_x+8, l_invader_y );
          break;
        case INVADER2:
          picosystem::sprite( l_invader2, l_invader_x, l_invader_y );
          picosystem::sprite( l_invader2+1, l_invader_x+8, l_invader_y );
          break;
        case INVADER3:
          picosystem::sprite( l_invader3, l_invader_x, l_invader_y );
          picosystem::sprite( l_invader3+1, l_invader_x+8, l_invader_y );
          break;
      }
    }
  }

  /* Also, draw the player. */
  picosystem::sprite( SPRITE_BASE, this->m_player_base_loc.x, m_player_base_loc.y );
  picosystem::sprite( SPRITE_BASE+1, this->m_player_base_loc.x+8, m_player_base_loc.y );

  /* Player bullet, if there is one. */
  if ( this->m_player_firing )
  {
    picosystem::sprite( l_bullet, this->m_player_bullet_loc.x, this->m_player_bullet_loc.y );
  }

  /* DEBUG - superimpose the state name on the buffer. */
#ifdef DEBUG
  this->ident( "GAME" );
#endif

  /* All done. */
  return;
}


/* End of file state/game.cpp */
