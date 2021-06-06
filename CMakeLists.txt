cmake_minimum_required ( VERSION 2.8)
project(lineExt)
## Compile as C++11
add_compile_options(-std=c++11)
## Specify additional locations of header files
include_directories(./include)
## Add cmake target dependencies src file
aux_source_directory(./src centerline_src)
## generate aim 
add_executable(../lineExt ${centerline_src})

