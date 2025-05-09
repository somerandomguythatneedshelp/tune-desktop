# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Tune_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Tune_autogen.dir\\ParseCache.txt"
  "Tune_autogen"
  )
endif()
