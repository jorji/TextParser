###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (C) 2012-2015 Institute of Industrial Science, The University of Tokyo.
# All rights reserved.
#
# Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN.
# All rights reserved.
#
# Copyright (c) 2016-2018 Research Institute for Information Technology, Kyushu University.
# All rights reserved.
#
###################################################################################

##
## Compile option selector
##
macro (AddOptimizeOption)
  if (TARGET_ARCH STREQUAL "INTEL_F_TCS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Kfast")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Kfast")
    if(enable_fapi)
      set(CMAKE_Fortran_FLAGS "-Kfast")
    endif()

  elseif (USE_F_TCS STREQUAL "YES")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Kfast")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Kfast")
    # -fPIC : PIC flag
    if(enable_fapi)
      set(CMAKE_Fortran_FLAGS "-Kfast")
    endif()

  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")
    if(enable_fapi)
      set(CMAKE_Fortran_FLAGS "-O3 -Wall")
    endif()

  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -xHOST -O3 -qopt-report=3")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -xHOST -O3 -qopt-report=3")
    if(enable_fapi)
      set(CMAKE_Fortran_FLAGS "-xHOST -O3 -qopt-report=3")
    endif()

  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "PGI")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fast -O3")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fast -O3")
    if(enable_fapi)
      set(CMAKE_Fortran_FLAGS "-fast -O3")
    endif()

  else()
    message("using default option")
  endif()
endmacro()


macro (FreeForm)
  if(CMAKE_Fortran_COMPILER MATCHES ".*frtpx$")
    #set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS}")

  elseif(TARGET_ARCH STREQUAL "INTEL_F_TCS")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -Free")

  elseif(CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -ffree-form")

  elseif(CMAKE_Fortran_COMPILER_ID STREQUAL "Intel")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -free")

  elseif(CMAKE_Fortran_COMPILER_ID STREQUAL "PGI")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -Mfree")

  endif()
endmacro()

macro(C99)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
endmacro()

macro(CPP11)
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
  CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
  if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  endif()
endmacro()

macro(checkOpenMP)
  if(enable_OPENMP)
    if(USE_F_TCS STREQUAL "YES")
      set(OpenMP_C_FLAGS "-Kopenmp")
      set(OpenMP_CXX_FLAGS "-Kopenmp")
      set(OpenMP_Fortran_FLAGS "-Kopenmp")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set(OpenMP_C_FLAGS "-fopenmp")
      set(OpenMP_CXX_FLAGS "-fopenmp")
      set(OpenMP_Fortran_FLAGS "-fopenmp")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
      set(OpenMP_C_FLAGS "-qopenmp")
      set(OpenMP_CXX_FLAGS "-qopenmp")
      set(OpenMP_Fortran_FLAGS "-qopenmp")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "PGI")
      set(OpenMP_C_FLAGS "-mp")
      set(OpenMP_CXX_FLAGS "-mp")
      set(OpenMP_Fortran_FLAGS "-mp")
    else()
      find_package(OpenMP REQUIRED)
    endif()

    # OpenMP_*_FLAGSにはfind_package(OpenMP REQUIRED)でオプションフラグが設定される
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${OpenMP_Fortran_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
  endif()
endmacro()
