// Copyright 2018 The VGC Developers
// See the COPYRIGHT file at the top-level directory of this distribution
// and at https://github.com/vgc/vgc/blob/master/COPYRIGHT
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef VGC_DOM_WRAPS_COMMON_H
#define VGC_DOM_WRAPS_COMMON_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

// Return value policy to use for methods returning raw pointers to
// vgc::dom::Node instances. These pointers are non-owning and we desire that
// Python references to such nodes do NOT extend the lifetime of the node.
//
// XXX Should we use py::return_value_policy::reference_internal, or
// py::return_value_policy::reference, or something else? Below are
// examples of the behaviour we would like, if at all possible.
//
// Scenario 1:
//
// >>> element = someElement()
// >>> child = element.firstChild
// >>> element.removeChild(child) # or child deleted from the GUI, C++ side
// >>> child.doSomething()
// ExpiredObjectError: the given element does not exist anymore
//
// Current behaviour: ?
//
// Scenario 2:
//
// >>> root = Document().createChildElement("vgc")
// >>> print(root)
// <vgc.dom.Vgc object at 0x7f45ba8d4ab0>
// >>> print(root.parent)
// <vgc.dom.Document object at 0x7f45ba8d4ab0>
//
// Current behaviour: ?
//
auto node_ptr_policy = py::return_value_policy::reference_internal;

#endif // VGC_DOM_WRAPS_COMMON_H
