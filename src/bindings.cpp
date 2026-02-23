#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "system.hpp"

namespace py = pybind11; // Makes the code much cleaner to read

PYBIND11_MODULE(myvicsek, m) {
    m.doc() = "MyVicsek: A Python binding for a C++ implementation of the Vicsek model";

    // Bind the Particle class first so System knows what a Particle is
    py::class_<Particle>(m, "Particle")
        .def(py::init<>()) // Bind the empty constructor too!
        .def(py::init<double, double, double, double, double>(),
            py::arg("x"), py::arg("y"), py::arg("theta"), py::arg("r"), py::arg("v"))
        // You MUST expose these members to see them in Python
        .def_readwrite("x", &Particle::x)
        .def_readwrite("y", &Particle::y)
        .def_readwrite("theta", &Particle::theta)
        .def_readwrite("r", &Particle::r)
        .def_readwrite("v", &Particle::v);

    py::class_<System>(m, "System")
        .def(py::init<int, double, double, double, int>(), 
            py::arg("particleNumber"), 
            py::arg("sideLength"), 
            py::arg("timeStep"), 
            py::arg("noiseStrength"), 
            py::arg("seed"))
        .def("saveConfig", &System::saveConfig)
        // def_readonly is okay here, pybind11/stl.h handles the vector conversion
        .def_readonly("particles", &System::particles) 
        .def("randomStart", &System::randomStart)
        .def("updateRule", &System::updateRule)
        .def_readwrite("noiseStrength", &System::noiseStrength);
}