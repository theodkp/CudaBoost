#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <regressor.hpp>

namespace py = pybind11;

PYBIND11_MODULE(gbm_pybind, m) {
    m.doc() = "Gradient Boosting Machine implementation in C++";

    py::class_<Regressor>(m, "Regressor")
        .def(py::init<int, int, float, int, std::string>(),
            // default values
            py::arg("n_estimators") = 100,
            py::arg("max_depth") = 3,
            py::arg("learning_rate") = 0.1f,
            py::arg("n_bins") = 256,
            py::arg("device") = "cpu"
        )
        .def("fit", &Regressor::fit,
            py::arg("X"),
            py::arg("y")
        );
}