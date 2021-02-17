##
# @brief  CMakeLists.txt for the ndarray-opencv-converter.
# @author Luis Carlos Garcia Peraza Herrera (luiscarlos.gph@gmail.com).
# @date   10 Feb 2021

cmake_minimum_required(VERSION 3.5)
project(ndcv_example)


#####################
# Find dependencies #
#####################

# Python libraries
find_package(Python3 REQUIRED COMPONENTS Interpreter Development NumPy)

# OpenCV
find_package(OpenCV REQUIRED)

# libboost_pythonXX.a
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS python3)


################################
# Setup building-related flags #
################################

include_directories(
  inc 
  ${Python3_INCLUDE_DIRS}
  ${Python3_NumPy_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)


##################
# Rules to build #
##################

# Compile libsuperlibrary.so
set(library_name "superlibrary")
add_library(${library_name} SHARED superlibrary.cpp)
set_target_properties(${library_name} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${library_name} ${Python3_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBS})

# Compile exemplary_program (C++ example binary that uses 'superlibrary')
add_executable(exemplary_program exemplary_program.cpp)
target_link_libraries(exemplary_program ${library_name})


####################
# Rules to install #
####################

# Install libsuperlibrary.so in ${CMAKE_INSTALL_PREFIX} (typically /usr/local/lib)
install(TARGETS ${library_name} LIBRARY DESTINATION lib)

# Create soft link inside the folder of Python packages so that libsuperlibrary.so can be imported
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink 
${CMAKE_INSTALL_PREFIX}/lib/lib${library_name}.so
${Python3_SITELIB}/${library_name}.so
)")
