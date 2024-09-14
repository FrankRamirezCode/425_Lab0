# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/frank/Documents/425 Lab/ECE425L_GPIO/GPIO/tmp/GPIO+Target_1"
  "/home/frank/Documents/425 Lab/ECE425L_GPIO/GPIO/tmp/1"
  "/home/frank/Documents/425 Lab/ECE425L_GPIO/GPIO/tmp/GPIO+Target_1"
  "/home/frank/Documents/425 Lab/ECE425L_GPIO/GPIO/tmp/GPIO+Target_1/tmp"
  "/home/frank/Documents/425 Lab/ECE425L_GPIO/GPIO/tmp/GPIO+Target_1/src/GPIO+Target_1-stamp"
  "/home/frank/Documents/425 Lab/ECE425L_GPIO/GPIO/tmp/GPIO+Target_1/src"
  "/home/frank/Documents/425 Lab/ECE425L_GPIO/GPIO/tmp/GPIO+Target_1/src/GPIO+Target_1-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/frank/Documents/425 Lab/ECE425L_GPIO/GPIO/tmp/GPIO+Target_1/src/GPIO+Target_1-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/frank/Documents/425 Lab/ECE425L_GPIO/GPIO/tmp/GPIO+Target_1/src/GPIO+Target_1-stamp${cfgdir}") # cfgdir has leading slash
endif()
