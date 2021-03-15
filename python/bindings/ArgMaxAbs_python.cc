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
/* BINDTOOL_HEADER_FILE(ArgMaxAbs.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(7f82f248624c926a93db772a29e7e60a)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <LibreLoRa/ArgMaxAbs.h>
// pydoc.h is automatically generated in the build directory
#include <ArgMaxAbs_pydoc.h>

void bind_ArgMaxAbs(py::module& m)
{

    using ArgMaxAbs    = gr::LibreLoRa::ArgMaxAbs;


    py::class_<ArgMaxAbs,
	       gr::sync_block,
               gr::block,
               gr::basic_block,
	       std::shared_ptr<ArgMaxAbs>>(m, "ArgMaxAbs", D(ArgMaxAbs))

        .def(py::init(&ArgMaxAbs::make),
           py::arg("vecLength"),
           D(ArgMaxAbs,make)
        )
        



        ;




}







