/*
 * utils/tick.hpp; part of PicoVaders, a Space Invaders inspired shoot-em-up
 *                 for the PicoSystem.
 *
 * This file defines the TickCounter class; different things happen at different
 * tick rates, so this class tracks when event should trigger.
 *
 * Copyright (c) 2022 Pete Favelle <picosystem@ahnlak.com>
 * This file is distributed under the MIT License; see LICENSE for details.
 */

#pragma once

class TickCounter
{
private:
  uint16_t    m_frequency_ms;
  uint32_t    m_time_ms;
  uint32_t    m_triggered_ms;
  uint32_t    m_triggered_count;

public:
              TickCounter( uint16_t );
             ~TickCounter();

  void        add_delta( uint32_t );
  uint16_t    set_frequency( uint16_t );
  bool        ticked( void );
  uint32_t    get_count( void );
};


/* End of file utils/tick.hpp */
