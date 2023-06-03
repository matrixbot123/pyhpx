#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <iostream>

#include <hpx/hpx.hpp>
#include <hpx/hpx_start.hpp>
#include <hpx/hpx_main.hpp>
#include <hpx/local/future.hpp>

namespace py = pybind11;


void init_hpx_runtime(){
    int argc = 0;
    char** argv = nullptr;
    hpx::start(nullptr, argc, argv);
}

//set values to the shared_future
void set_future_value(hpx::shared_future<int>& future, int value) {
    // Create a new promise
    hpx::promise<int> promise;
    promise.set_value(value);
    hpx::future<int> new_future = promise.get_future();
    future = std::move(new_future);
}


//async function that takes function from 
hpx::shared_future<int> myAsyncFunction(py::args args)
{
    if (args.size() == 0)
    {
        throw std::runtime_error("No function provided.");
    }

    py::function f = py::cast<py::function>(args[0]);
    py::tuple arguments(args.size() - 1);
    for (size_t i = 1; i < args.size(); ++i)
    {
        arguments[i - 1] = args[i];
    }

    return hpx::async([f, arguments]() {
        py::gil_scoped_acquire acquire;
        py::object result = f(*arguments);
        return result.cast<int>();
    });
}



PYBIND11_MODULE(pyhpx , m){ 



    m.def(  "init_hpx",
            &init_hpx_runtime);
                     
    py::class_ <hpx::shared_future<int>>(m,"shared_futureInt")
        .def(py::init<>())
        .def(py::init<const hpx::shared_future<int>&>())
        .def("set_value", &set_future_value)
        .def("get", [](const hpx::shared_future<int>& future) { return future.get(); },"Get the value of shared future");        
    ;

    m.def("new_async", [](py::args args) {
            return myAsyncFunction(args);}
        );


}


