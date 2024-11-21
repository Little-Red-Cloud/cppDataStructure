# CPP Data Structure

This is a simple implementation of data structures in C++ when learning data structures. I implemented the following algorithms such as Bubble Sort, Selection Sort, Insertion Sort, Shell Sort, Heap Sort and calculate the time complexity of each algorithm. Simple Binary Search Tree is also implemented.

## Usage
In shell
```shell 
cd root_directory/
mkdir build
cd build/
cmake ..
cmake --build .
```

In your CMakeLists.txt
```cmake
add_library(dataStructure INTERFACE)
target_include_directories(dataStructure INTERFACE              
    "root_directory/include")
target_link_libraries(dataStructure INTERFACE
    "root_directory/lib/libdataStructure.a")

targetlink_libraries(your_target_name dataStructure)
```