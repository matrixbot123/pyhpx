#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;
int main(int argc , char** argv){
    auto f = hpx::async([](){return 23;});
    std::cout<< f.get() <<std::endl;

    py::scoped_interpreter guard{};
        if (argc > 1) {
        // Execute Python file
        std::string filename = argv[1];

        // Append additional arguments for the Python script if provided
        std::string pyArgs;
        for (int i = 2; i < argc; ++i) {
            pyArgs += " ";
            pyArgs += argv[i];
        }

        std::string pyCommand = "exec(open('" + filename + "').read())";
        py::exec(pyCommand + pyArgs);
    } else {
        // Interactive mode
        std::string line;
        while (std::getline(std::cin, line)) {
            try {
                py::exec(line);
            } catch (const py::error_already_set& e) {
                // Print the error message and continue the loop
                py::print(e.what());
            }
        }
    }
    return 0;
}