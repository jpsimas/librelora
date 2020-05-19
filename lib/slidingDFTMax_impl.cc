/* -*- c++ -*- */
/*
 * Copyright 2020 Joao Pedro de O Simas.
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
#include "slidingDFTMax_impl.h"

#include <volk/volk.h>

namespace gr {
  namespace LibreLoRa {

    slidingDFTMax::sptr
    slidingDFTMax::make(size_t DFTLength, size_t SF, size_t symbolSize)
    {
      return gnuradio::get_initial_sptr
        (new slidingDFTMax_impl(DFTLength, SF, symbolSize));
    }


    /*
     * The private constructor
     */
    slidingDFTMax_impl::slidingDFTMax_impl(size_t DFTLength, size_t SF, size_t symbolSize)
      : gr::sync_block("slidingDFTMax",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
		       gr::io_signature::make(1, 1, sizeof(float))),
	length(DFTLength),
	beta(float(1 << SF)/(symbolSize*symbolSize)),
	offset(beta),
	step(std::polar<float>(1.0, -2*M_PI*beta))
    {
      
      set_history(length);

      const int alignment_multiple = volk_get_alignment()/sizeof(gr_complex);
      set_alignment(std::max(1,alignment_multiple));
      
      exponents = (gr_complex *)volk_malloc(length*sizeof(gr_complex), volk_get_alignment());

      DFT = (gr_complex *)volk_malloc(length*sizeof(gr_complex), volk_get_alignment());
      float alphai = 1.0;
      for (size_t i = 0; i < length; i++) {
	exponents[i] = alphai*std::polar<float>(1, (2.0*M_PI/length)*i);
	alphai *= alpha;
	DFT[i] = 1;
      }

      e0 = 1.0;
      eN = std::polar<float>(1.0, beta*length*(length + 1)/2.0);
    }

    /*
     * Our virtual destructor.
     */
    slidingDFTMax_impl::~slidingDFTMax_impl()
    {
      free(exponents);
      free(DFT);
    }

    // void
    // slidingDFTMax_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    // {
    //   /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    //   ninput_items_required[0] = noutput_items + length;
    // }
    
    int
    slidingDFTMax_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *indexOut = (float *) output_items[0];

      // Do <+signal processing+>
      
      for(size_t i = 0; i < noutput_items; i++) {
	volk_32fc_x2_multiply_32fc(DFT, exponents, DFT, length);
	
	const auto delta = - in[i]*alphaN*eN + in[i + length]*e0;

	e0 *= step;
	eN *= step;
	
	for(auto j = 0; j < length; j++)
	  DFT[j] += delta;

	uint32_t indMax;
	volk_32fc_index_max_32u(&indMax, DFT, length);
	
	indexOut[i] = remainder(indMax/float(length)/* + offset*/ , 1.0);
	offset += beta;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace LibreLoRa */
} /* namespace gr */
