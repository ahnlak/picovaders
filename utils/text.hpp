/*
 * utils/text.hpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                 for the PicoSystem.
 *
 * This file defines the ScalableText class; a simple wrapper to the standard
 * PicoSystem API text handling, to allow us to arbitarily scale it. Because
 * it's just done through blit scaling, it probably works best as integer scales.
 *
 * Copyright (c) 2022 Pete Favelle <picosystem@ahnlak.com>
 * This file is distributed under the MIT License; see LICENSE for details.
 */

#pragma once

#define SCALABLETEXT_MAX_LEN  50

class ScalableText
{
private:
  picosystem::buffer_t *m_buffer = nullptr;
  float                 m_scale;
  char                  m_text[SCALABLETEXT_MAX_LEN+1];
  int32_t               m_text_width;
  int32_t               m_text_height;

public:
                  ScalableText( const char *, float = 1.0f );
                 ~ScalableText();

  void            set_text( const char * );
  void            set_scale( float );
  int32_t         get_width( void );
  int32_t         get_height( void );
  void            draw( int32_t, int32_t );
  void            draw( int32_t, int32_t, float );
  void            draw( int32_t, int32_t, int32_t, int32_t );
};


/* End of file utils/text.hpp */
