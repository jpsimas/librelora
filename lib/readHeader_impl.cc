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
#include "readHeader_impl.h"

#include <array>

namespace gr {
  namespace LibreLoRa {

    readHeader::sptr
    readHeader::make(size_t SF)
    {
      return gnuradio::get_initial_sptr
        (new readHeader_impl(SF));
    }


    /*
     * The private constructor
     */
    readHeader_impl::readHeader_impl(size_t SF)
      : gr::sync_block("readHeader",
		  gr::io_signature::make(1, 1, 12*sizeof(uint8_t)),
		       gr::io_signature::makev(5, 5, {sizeof(uint8_t), sizeof(uint8_t), sizeof(uint8_t), sizeof(uint8_t), 7*sizeof(uint8_t)})) {
    }

    /*
     * Our virtual destructor.
     */
    readHeader_impl::~readHeader_impl()
    {
    }

    constexpr uint8_t nibblePairity(const uint8_t nibble) {
      return (nibble ^ (nibble >> 1) ^ (nibble >> 2) ^ (nibble >> 3)) & 0x1;
    }
    
    uint8_t calculateHeaderChecksum(const uint16_t headerData) {
      uint8_t checkSum = 0x00;
      constexpr std::array<uint16_t, 5> masks = {0xF21, 0x752, 0xA94, 0x1E8, 0x00F};
      for(size_t i = 0; i < masks.size(); i++)
	checkSum |= nibblePairity(masks[i]&headerData) << i;
      return checkSum;
    }
    
    int
    readHeader_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const uint8_t *in = (const uint8_t *) input_items[0];
      uint8_t *payloadLength = (uint8_t *) output_items[0];
      uint8_t *payloadCRCPresent = (uint8_t *) output_items[1];
      uint8_t *CR = (uint8_t *) output_items[2];
      uint8_t *headerCheckSumValid = (uint8_t *) output_items[3];
      uint8_t *dataOut = (uint8_t *) output_items[4];

      // Do <+signal processing+>
      for(size_t i = 0; i < noutput_items; i++) {
	auto inI = in + 12*i;
	payloadLength[i] = (inI[0] << 4)&(inI[1]);
	payloadCRCPresent[i] = inI[2] & 0x01;
	CR[i] = inI[2] >> 1;
	uint8_t headerCheckSum = (inI[3] << 4)&inI[4];
	uint8_t headerCheckSumCalculated = calculateHeaderChecksum(*((uint16_t*) inI));
	headerCheckSumValid[i] = (headerCheckSum == headerCheckSumCalculated);
	for(size_t j = 0; j < 7; j++)
	  dataOut[7*i + j] = inI[5 + j];
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace LibreLoRa */
} /* namespace gr */

