#include <pybind11/pybind11.h>

#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

/////////////////////////////////////////////////////////////
// gps coordinate
//
// illustrates serialization for a simple type
//
class gps_position
{
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & degrees;
    ar & minutes;
    ar & seconds;
  }
  int degrees;
  int minutes;
  float seconds;
public:
  gps_position(){};
  gps_position(int d, int m, float s) :
    degrees(d), minutes(m), seconds(s)
  {}
};

int test_serialization() {
  // create and open a character archive for output
  std::ofstream ofs("test_filename");

  // create class instance
  const gps_position g(35, 59, 24.567f);

  // save data to archive
  {
    boost::archive::text_oarchive oa(ofs);
    // write class instance to archive
    oa << g;
    // archive and stream closed when destructors are called
  }

  // ... some time later restore the class instance to its orginal state
  gps_position newg;
  {
    // create and open an archive for input
    std::ifstream ifs("test_filename");
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> newg;
    // archive and stream closed when destructors are called
  }
  return 0;
}

int add(int i, int j) {
  return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(_boost_example, m) {
  m.doc() = "Simple Boost example";

  m.def("add", &add);
  m.def("subtract", [](int i, int j) { return i - j; });
  m.def("test_serialization", &test_serialization);
}
