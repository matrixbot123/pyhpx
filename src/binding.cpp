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
// ============================================================================
//set values to the shared_future
void set_future_value(hpx::shared_future<int>& future, int value) {
    // Create a new promise
    hpx::promise<int> promise;
    promise.set_value(value);
    hpx::future<int> new_future = promise.get_future();
    future = std::move(new_future);
}

bool is_ready(const hpx::shared_future<int>& future){
    return future.is_ready();
}

int get(const hpx::shared_future<int>& future){
    return future.get();
}

//=============================================================================
//async function that takes function from 
hpx::shared_future<int> async_function(py::function f, py::args args)
{

    return hpx::async([f, args]() {
        py::gil_scoped_acquire acquire;
        py::object result = f(*args);
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
        .def("is_ready",&is_ready,"Checks if the associated shared state is ready")
        .def("get",&get,"Get the value of shared future")
    ;

    m.def("new_async", [](py::function f,py::args args) {
        return async_function(f,args);
    });

}


