/*
 * utils/text.cpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                 for the PicoSystem.
 *
 * This file implements the ScalableText class; a simple wrapper to the standard
 * PicoSystem API text handling, to allow us to arbitarily scale it. Because
 * it's just done through blit scaling, it probably works best as integer scales.
 *
 * Copyright (c) 2022 Pete Favelle <picosystem@ahnlak.com>
 * This file is distributed under the MIT License; see LICENSE for details.
 */

/* System headers. */

#include <string.h>


/* Local headers. */

#include "picosystem.hpp"
#include "utils/text.hpp"


/* Functions. */

/*
 * constructor - just initialises things like timers and assets.
 */

ScalableText::ScalableText( const char *p_text, float p_scale )
{
  /* Remember the scale we're using. */
  this->set_scale( p_scale );

  /* And then set the text, assuming we have any. */
  if ( p_text != nullptr )
  {
    this->set_text( p_text );
  }

  /* All done. */
  return;
}


/*
 * destructor - tidy up any allocated resources.
 */

ScalableText::~ScalableText()
{
  /* Clean up the buffer, if we've created one. */
  if ( this->m_buffer != nullptr )
  {
    delete this->m_buffer;
    this->m_buffer = nullptr;
  }

  /* All done. */
  return;
}


/*
 * set_text - updates or sets the text used. A new buffer will be allocated
 *            to hold it, sized to fit the text and no more.
 */

void ScalableText::set_text( const char *p_text )
{
  /* Save the text; we have a limit on length, because... well, we do. */
  strncpy( this->m_text, p_text, SCALABLETEXT_MAX_LEN );
  this->m_text[SCALABLETEXT_MAX_LEN] = '\0';

  /* If the buffer has been previously allocated, clean it up. */
  if ( this->m_buffer != nullptr )
  {
    delete this->m_buffer;
    this->m_buffer = nullptr;
  }

  /* Measure the next text and fetch a buffer for it. */
  picosystem::measure( this->m_text, this->m_text_width, this->m_text_height );
  this->m_buffer = picosystem::buffer( this->m_text_width, this->m_text_height );

  /* Check we have something to draw in! */
  if ( this->m_buffer == nullptr )
  {
    return;
  }

  /* Good, just draw it then. */
  picosystem::target( this->m_buffer );
  picosystem::text( this->m_text );
  picosystem::target();

  /* All done! */
  return;
}


/*
 * set_scale - updates or set the scale at which the text will be drawn.
 */

void ScalableText::set_scale( float p_scale )
{
  /* Very simple set operation. */
  this->m_scale = p_scale;
  return;
}


/*
 * get_width and get_height - returns the size at which the text will be drawn,
 *                            at the currently assigned scale.
 */

int32_t ScalableText::get_width( void )
{
  return this->m_text_width * this->m_scale;
}
int32_t ScalableText::get_height( void )
{
  return this->m_text_height * this->m_scale;
}


/*
 * draw - draws the text buffer to the current target; by default we render
 *        at the current scale, but overloads allow this to be changed or for
 *        a specific target width/height to be provided.
 */

void ScalableText::draw( int32_t p_x, int32_t p_y )
{
  /* Just call the scalable version, with our defaults. */
  this->draw( p_x, p_y, this->m_scale );
  return;
}
void ScalableText::draw( int32_t p_x, int32_t p_y, float p_scale )
{
  /* Calculate the destination size based on scale, and call the main version. */
  this->draw( p_x, p_y, this->get_width(), this->get_height() );
  return;
}

void ScalableText::draw( int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height )
{
  /* Once we get here, it's a fairly painless blit. */
  picosystem::blend( picosystem::PEN );
  picosystem::blit( this->m_buffer, 
                    0, 0, this->m_text_width, this->m_text_height,
                    p_x, p_y, p_width, p_height );
  picosystem::blend();
  return;
}


/* End of file utils/text.cpp */
