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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "normalizeCorrelation_impl.h"

#include <cmath>
#include <volk/volk.h>

namespace gr {
  namespace LibreLoRa {

    normalizeCorrelation::sptr
    normalizeCorrelation::make(size_t correlationVectorSize)
    {
      return gnuradio::get_initial_sptr
        (new normalizeCorrelation_impl(correlationVectorSize));
    }


    /*
     * The private constructor
     */
    normalizeCorrelation_impl::normalizeCorrelation_impl(size_t correlationVectorSize)
      : gr::sync_block("normalizeCorrelation",
		  gr::io_signature::make(3, 3, sizeof(float)),
		  gr::io_signature::make(1, 1, sizeof(float))),
	correlationVectorSize(correlationVectorSize){
    }

    /*
     * Our virtual destructor.
     */
    normalizeCorrelation_impl::~normalizeCorrelation_impl()
    {
    }

    // void
    // normalizeCorrelation_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    // {
    //   /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    //   ninput_items_required[0] = noutput_items;
    // }
    
    int
    normalizeCorrelation_impl::work (int noutput_items,
					     gr_vector_const_void_star &input_items,
					     gr_vector_void_star &output_items)
    {
      const float *unnormCorr = (const float *) input_items[0];
      const float *signalSum = (const float *) input_items[1];
      const float *signalSquaredSum = (const float *) input_items[2];
      
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
      
      for(size_t i = 0; i < noutput_items; i++) {
       	auto norm = signalSquaredSum[i] - signalSum[i]*signalSum[i]*(1.0/correlationVectorSize);
	
       	out[i] = unnormCorr[i]/sqrt(norm);
      }
      
      // Tell runtime system how many input items we consumed on
      // each input stream.
      //consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace LibreLoRa */
} /* namespace gr */

