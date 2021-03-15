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
/* BINDTOOL_HEADER_FILE(correlationSyncDemod.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(f2ec6ec8b23687345305efe7d44ff423)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <LibreLoRa/correlationSyncDemod.h>
// pydoc.h is automatically generated in the build directory
#include <correlationSyncDemod_pydoc.h>

void bind_correlationSyncDemod(py::module& m)
{

    using correlationSyncDemod    = gr::LibreLoRa::correlationSyncDemod;


    py::class_<correlationSyncDemod,
               gr::block,
               gr::basic_block,
	       std::shared_ptr<correlationSyncDemod>>(m, "correlationSyncDemod", D(correlationSyncDemod))

        .def(py::init(&correlationSyncDemod::make),
           py::arg("corrMin"),
           py::arg("corrStop"),
           py::arg("symbolSize"),
           py::arg("preambleSize"),
           py::arg("SF"),
           py::arg("syncWordNumber"),
           D(correlationSyncDemod,make)
        )
        



        ;




}








