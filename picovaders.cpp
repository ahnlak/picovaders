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


/* Functions. */

/*
 * init - the PicoSystem SDK entry point; called when the game is launched. 
 */

void init( void )
{
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
  /* All done. */
  return;
}


/* End of file picovaders.cpp */
