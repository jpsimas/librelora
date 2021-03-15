/*
 * Copyright 2021 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(GrayDecode.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(994be1b5d65408c85f99eed9a4d6b7f9)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <LibreLoRa/GrayDecode.h>
// pydoc.h is automatically generated in the build directory
#include <GrayDecode_pydoc.h>

void bind_GrayDecode(py::module& m)
{

    using GrayDecode    = gr::LibreLoRa::GrayDecode;


    py::class_<GrayDecode,
	       gr::sync_block,
               gr::block,
               gr::basic_block,
	       std::shared_ptr<GrayDecode>>(m, "GrayDecode", D(GrayDecode))

        .def(py::init(&GrayDecode::make),
           py::arg("nBits"),
           D(GrayDecode,make)
        )
        



        ;




}








