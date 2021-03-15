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
/* BINDTOOL_HEADER_FILE(frequencyTracker.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(e9dd1681c11bf1b5ff03179cf3df90af)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <LibreLoRa/frequencyTracker.h>
// pydoc.h is automatically generated in the build directory
#include <frequencyTracker_pydoc.h>

template<typename T>
void bind_frequencyTracker_template(py::module& m, const char* classname)
{

    using frequencyTracker    = gr::LibreLoRa::frequencyTracker<T>;


    py::class_<frequencyTracker,
	       gr::sync_block,
               gr::block,
               gr::basic_block,
	       std::shared_ptr<frequencyTracker>>(m, classname, D(frequencyTracker))

        .def(py::init(&frequencyTracker::make),
           py::arg("mu"),
           py::arg("SF"),
           py::arg("OSF"),
           py::arg("decimation") =  1,
           D(frequencyTracker,make)
        );
}

void bind_frequencyTracker(py::module& m)
{
    bind_frequencyTracker_template<float>(m, "frequencyTracker_ff");
    bind_frequencyTracker_template<gr_complex>(m, "frequencyTracker_cc");
}
