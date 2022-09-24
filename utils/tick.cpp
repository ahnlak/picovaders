/*
 * utils/tick.cpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                 for the PicoSystem.
 *
 * This file implements the TickCounter class; different things happen at different
 * tick rates, so this class tracks when event should trigger.
 *
 * Copyright (c) 2022 Pete Favelle <picosystem@ahnlak.com>
 * This file is distributed under the MIT License; see LICENSE for details.
 */

/* System headers. */


/* Local headers. */

#include "picosystem.hpp"
#include "utils/tick.hpp"


/* Functions. */

/*
 * constructor - just initialises things like timers and assets.
 */

TickCounter::TickCounter( uint16_t p_frequency_ms )
{
  /* Remember the frequency at which we operate. */
  this->m_frequency_ms = p_frequency_ms;

  /* And reset our timers. */
  this->m_time_ms = 0;
  this->m_triggered_ms = 0;

  /* All done. */
  return;
}


/*
 * destructor - tidy up any allocated resources.
 */

TickCounter::~TickCounter()
{
  /* All done. */
  return;
}


/*
 * add_delta - adds the delta from the most recent frame; we get an indeterminate
 *             number of milliseconds added with each frame, so we take that
 *             and work out if we need more ticks.
 */

void TickCounter::add_delta( uint32_t p_delta )
{
  /* Very simply update our internal concept of time. */
  this->m_time_ms += p_delta;

  /* All done. */
  return;
}


/*
 * set_frequency - sets the frequency, in milliseonds, all future ticks. Returns
 *                 the previous frequency value, in case it's useful.
 */

uint16_t TickCounter::set_frequency( uint16_t p_frequency_ms )
{
  uint16_t l_current_frequency = this->m_frequency_ms;
  this->m_frequency_ms = p_frequency_ms;
  return l_current_frequency;
}


/*
 * ticked - determines if this counter should have ticked. If it should, the
 *          internal triggered time is updated and TRUE is returned - if not
 *          we just return FALSE and do nothing.
 */

bool TickCounter::ticked( void )
{
  /* Check to see if we should be triggered. */
  if ( ( this->m_triggered_ms + this->m_frequency_ms ) < this->m_time_ms )
  {
    this->m_triggered_ms += this->m_frequency_ms;
    this->m_triggered_count++;
    return true;
  }

  /* No trigger required. */
  return false;
}


/*
 * get_count - returns the number of times this ticker has been triggered;
 *             useful for things like picking which animation frame to use. 
 */
  
uint32_t TickCounter::get_count( void )
{
  return this->m_triggered_count;
}


/* End of file utils/tick.cpp */
