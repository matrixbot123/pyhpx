#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;
int main(int argc , char** argv){
    auto f = hpx::async([](){return 23;});
    std::cout<< f.get() <<std::endl;

    py::scoped_interpreter guard{};
    std::string line ;
    while(std::cin>>line){
        py::exec(line) ;
    }
    return 0;
}