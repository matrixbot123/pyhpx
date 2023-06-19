#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <iostream>

#include <hpx/hpx.hpp>
#include <hpx/hpx_start.hpp>
#include <hpx/hpx_main.hpp>
#include <hpx/future.hpp>

namespace py = pybind11;
//set values to the shared_future
void set_future_value(hpx::shared_future<int>& future, int value) {
    py::gil_scoped_release release;

    hpx::promise<int> promise;
    promise.set_value(value);
    hpx::future<int> new_future = promise.get_future();
    future = std::move(new_future);
}

void init_hpx_runtime(){
    py::gil_scoped_release release;
    try{    
        int argc = 0;
        char** argv = nullptr;
        hpx::start(nullptr, argc, argv);
    } catch(const std::exception& e){
        std::cerr<< "Excepting in the init "<< e.what() << std::endl;
        throw;
    }
    // py::gil_scoped_acquire acquire;

}

bool is_ready(const hpx::shared_future<int>& future){
    py::gil_scoped_release release;
    return future.is_ready();
}

int get(const hpx::shared_future<int>& future){
    py::gil_scoped_release release;
    try{
        return future.get();
    } catch(const std::exception& e){
        std::cerr << "excepting in get" << e.what()<< std::endl;
        throw;
    }    
}

//async function that takes function from 
hpx::shared_future<int> async_function(std::function<int(int)> f, int a)
{   std::cout<<"called async "<<a<<std::endl;
    // py::gil_scoped_release release;
    return hpx::async([f, a]() {
        py::gil_scoped_acquire acquire;
        try {
            return f(a);
        }catch (const std::exception& e) {
            // Handle the exception here, e.g., log or rethrow
            std::cerr << "Exception in async function: " << e.what() << std::endl;
            throw;
        }      
    });
}

PYBIND11_MODULE(pyhpx , m){ 
    m.def(  "init_hpx",
            &init_hpx_runtime);
                     
    py::class_ <hpx::shared_future<int>>(m,"shared_futureInt")
        .def(py::init<>())
        .def(py::init<const hpx::shared_future<int>&>())
        // .def("set_value", &set_future_value)
        // .def("is_ready",&is_ready,"Checks if the associated shared state is ready")
        .def("get",&get,"Get the value of shared future")
    ;

    m.def("new_async", 
        [](std::function<int(int)> f,int a)
        {
            py::gil_scoped_release release;
            return async_function(f,a);
        }
        );

}


