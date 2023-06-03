## Installation 
In my repository, I have primarily utilized two main libraries: pybind11 and HPX. To obtain identical results, please install these libraries as demonstrated below:

### HPX

```
git clone https://github.com/STEllAR-GROUP/hpx.git
cd hpx
git checkout -b 1.9.0 v1.9.0
```
above steps are just get the source code and to change the branch to 1.9.0.

. Installation Using Cmake
1. make a build folder outside the source code folder
``` 
mkdir build_hpx && cd build_hpx 
```

2. Dependencies
```
sudo apt install libboost-all-dev
sudo apt-get install libasio-dev
```
3. `cmake /path/to/source code` (this command will install the hpx to the default location `/usr/local`)


4. once all of the above steps done just run
```
cmake --build . --target install
```

note : need to install few libraries like boost (must), hwloc/tcmalloc/jemalloc or just do if having problem with (hwloc/tcmalloc/jemalloc)
`cmake -DHPX_WITH_MALLOC=system ...`

### Pybind11
```
git submodule add https://github.com/pybind/pybind11 pybind11
git checkout -b 2.10.4 v2.10.4
```
I am currently using 2.10.4 latest vesion 


## Usage 
Currently  I have mainly implemented 2 things `init_hpx()`,`shared_future<int>` (class implemented partially) and `shared_future<int> new_async` function .

To import the library just make a build folder
```
mkdir build && cd build
cmake ..
make pyhpx
```
An `.so` file will be created just do `import pyhpx` in python 
### Example 
```
matrix@matrix:~ python 
>>> import pyhpx
>>> pyhpx.init_hpx()        //init runtime
>>> def add(a,b):
...     return a+b
... 
>>> add(1,4)
5
>>> sf = pyhpx.new_async(add,1,70) 
>>> sf.get()
71
```
