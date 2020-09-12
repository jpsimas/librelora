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
#include "AppendPrefix_impl.h"

namespace gr {
  namespace LibreLoRa {

    template<typename T>
    typename AppendPrefix<T>::sptr
    AppendPrefix<T>::make(const size_t payloadSize, const std::vector<T> prefix)
    {
      return gnuradio::get_initial_sptr
        (new AppendPrefix_impl<T>(payloadSize, prefix));
    }


    /*
     * The private constructor
     */
    template<typename T>
    AppendPrefix_impl<T>::AppendPrefix_impl(const size_t payloadSize, const std::vector<T> prefix)
      : gr::block("AppendPrefix",
		  gr::io_signature::make(1, 1, sizeof(T)),
		  gr::io_signature::make(1, 1, sizeof(T))),
	payloadSize(payloadSize),
	prefix(prefix),
	sampleCount(0) {
      this->set_min_output_buffer(payloadSize + prefix.size());
    }

    /*
     * Our virtual destructor.
     */
    template<typename T>
    AppendPrefix_impl<T>::~AppendPrefix_impl()
    {
    }

    template<typename T>
    void
    AppendPrefix_impl<T>::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      // const size_t nFrames = (noutput_items + payloadSize + prefix.size() - 1)/(payloadSize + prefix.size());
      
      // ninput_items_required[0] = nFrames*payloadSize;
      ninput_items_required[0] = noutput_items;
    }

    template<typename T>
    int
    AppendPrefix_impl<T>::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const T *in = (const T *) input_items[0];
      T *out = (T *) output_items[0];

      // const size_t nFrames = (noutput_items + payloadSize + prefix.size() - 1)/(payloadSize + prefix.size());
      
      // for(auto k = 0; k < nFrames; k++) {
      // 	auto outK = out + k*(payloadSize + prefix.size());
      // 	auto inK = in + k*payloadSize;
      // 	memcpy(outK, prefix.data(), prefix.size()*sizeof(T));
      // 	memcpy(outK + prefix.size(), inK, payloadSize*sizeof(T));
      // }

#ifndef NDEBUG
      // std::cout << "AppendPrefix: work called. noutput_items: " << std::dec << noutput_items << ". sampleCount: " << sampleCount << std::endl;
#endif
      
      size_t nFrames = 0;
      for(auto i = 0; i < noutput_items; i++) {
// 	if(sampleCount == 0) {
// 	  memcpy(out + i + nFrames*prefix.size(), prefix.data(), prefix.size()*sizeof(T));
// 	  nFrames++;
// #ifndef NDEBUG
// 	  std::cout << "AppendPrefix: prefix inserted. sampleCount: " << sampleCount << std::endl;
// #endif
// 	}

	std::vector<gr::tag_t> tags;
	auto nr =  this->nitems_read(0);
	static const pmt::pmt_t tagKey = pmt::intern("loraParams");
	this->get_tags_in_range(tags, 0, nr + i, nr + i + 1, tagKey);
	if(tags.size() != 0)
	  if(pmt::to_bool(pmt::tuple_ref(tags[0].value, 2))) {
	    memcpy(out + i + nFrames*prefix.size(), prefix.data(), prefix.size()*sizeof(T));
	    nFrames++;
#ifndef NDEBUG
	    std::cout << "AppendPrefix: prefix inserted." << std::endl;
#endif
	}

	
	out[i + nFrames*prefix.size()] = in[i];
	// sampleCount = (sampleCount + 1)%payloadSize;
      }
      
      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      // gr::block::consume_each (nFrames*payloadSize);
      gr::block::consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      // return nFrames*(payloadSize + prefix.size());
      return nFrames*prefix.size() + noutput_items;
    }

    template class AppendPrefix<float>;
    template class AppendPrefix<gr_complex>;
    template class AppendPrefix<uint8_t>;
    template class AppendPrefix<uint16_t>;
    
  } /* namespace LibreLoRa */
} /* namespace gr */
