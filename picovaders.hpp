/*
 * picovaders.hpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                 for the PicoSystem.
 *
 * This file defines all the global constants and structures, which are used
 * throughout the game.
 *
 * Copyright (c) 2022 Pete Favelle <picosystem@ahnlak.com>
 * This file is distributed under the MIT License; see LICENSE for details.
 */

#pragma once

/* Constants and enums. */

#define SCREEN_WIDTH    240
#define SCREEN_HEIGHT   240

#define SPRITE_TITLE_X  0
#define SPRITE_TITLE_Y  24
#define SPRITE_TITLE_W  128
#define SPRITE_TITLE_H  56

typedef enum
{
  INVADER_NONE,
  INVADER1,
  INVADER2,
  INVADER3
} invader_t;

typedef enum
{
  /* First row. */
  SPRITE_INVADER1 = 0,
  SPRITE_INVADER2 = 2, 
  SPRITE_INVADER3 = 4,
  SPRITE_SHIP = 6,
  SPRITE_BOOM = 8,
  SPRITE_BOMB1 = 10, SPRITE_BOMB2, SPRITE_BULLET,
  SPRITE_SHELTER1,

  /* Second row. */
  SPRITE_INVADER1_ALT = 16,
  SPRITE_INVADER2_ALT = 18, 
  SPRITE_INVADER3_ALT = 20,
  SPRITE_SHIP_ALT = 22,
  SPRITE_BOOM_ALT = 24,
  SPRITE_BOMB1_ALT = 26, SPRITE_BOMB2_ALT, SPRITE_BULLET_ALT,
  SPRITE_SHELTER2,

  /* Third row. */
  SPRITE_BASE = 32,
  SPRITE_BASE_BOOM1 = 34,
  SPRITE_BASE_BOOM2 = 36,
  SPRITE_BASE_BOOM3 = 38,
  SPRITE_BIG_BOOM = 40,
  SPRITE_BIG_BOOM_ALT = 42, 
  SPRITE_SHELTER3 = 45
} spriteindex_t;

typedef enum
{
  GAMESTATE_SPLASH,
  GAMESTATE_TITLE,
  GAMESTATE_GAME,
  GAMESTATE_DEATH,
  GAMESTATE_MAX
} gamestate_t;


/* Structures. */

struct coord_t
{
  uint_fast8_t x;
  uint_fast8_t y;
};


/* Interfaces. */

class GameStateInterface
{
  protected:
    gamestate_t   m_state = GAMESTATE_MAX;

    void                ident( const char *p_id )
                        {
                          int32_t w, h;
                          picosystem::pen( 0, 0, 0 );
                          picosystem::measure( p_id, w, h );
                          picosystem::frect( 0, 0, w, h );
                          picosystem::pen( 15, 15, 15 );
                          picosystem::text( p_id, 0, 0 );
                        }

  public:
    virtual gamestate_t update( uint32_t ) = 0;
    virtual void        draw( void ) = 0;
    
    gamestate_t         get_state( void ) { return m_state; }
};


/* End of file picovaders.hpp */
