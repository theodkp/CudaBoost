#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "dataset.hpp"

namespace py = pybind11;

// Bind the loadCSV function to Python
PYBIND11_MODULE(gbm_pybind, m) {
    m.doc() = "Python bindings for GBM Dataset"; // Optional module docstring

    // Expose loadCSV to Python
    m.def("load_csv", &loadCSV, "A function to load a CSV file into a Dataset");

    // Expose Dataset class if needed
    py::class_<Dataset>(m, "Dataset")
        .def(py::init<>())
        .def_readwrite("featureNames", &Dataset::featureNames)
        .def_readwrite("data", &Dataset::data);
}