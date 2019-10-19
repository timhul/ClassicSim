#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int i, int j) {
  return i + j;
}

PYBIND11_MODULE(classic_sim, m) {
  m.doc() = "Python bindings for ClassicSim";
  m.def("add", &add, "A function which adds two numbers.");
}
