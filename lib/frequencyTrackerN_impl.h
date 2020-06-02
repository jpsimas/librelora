/* -*- c++ -*- */
/*
 * Copyright 2020 Joao Pedro de O. Simas.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_LIBRELORA_FREQUENCYTRACKERN_IMPL_H
#define INCLUDED_LIBRELORA_FREQUENCYTRACKERN_IMPL_H

#include <LibreLoRa/frequencyTrackerN.h>

namespace gr {
  namespace LibreLoRa {

    class frequencyTrackerN_impl : public frequencyTrackerN
    {
     private:
      // Nothing to declare in this block.
      const std::vector<gr_complex> window;
      std::vector<gr_complex> windowedSig;
      float mu;
      gr_complex w;
     public:
      frequencyTrackerN_impl(float mu, size_t SF, size_t OSF, const std::vector<gr_complex>& window);
      ~frequencyTrackerN_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace LibreLoRa
} // namespace gr

#endif /* INCLUDED_LIBRELORA_FREQUENCYTRACKERN_IMPL_H */
