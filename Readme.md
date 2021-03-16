# TextParser - Text Parsing Library

- Copyright (c) 2012-2015 Institute of Industrial Science, The University of Tokyo. All rights reserved.
- Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN. All rights reserved.
- Copyright (c) 2016-2018 Research Institute for Information Technology, Kyushu University. All rights reserved.


## OUTLINE
Text Parser library allows us to describe and to parse JSON like simple parameter structure.


## SOFTWARE REQUIREMENT
- Cmake
- MPI library (option)


## HOW TO BUILD

### Build

~~~
$ export TP_HOME=/hogehoge

Example: ${HOME}/lib

$ mkdir BUILD
$ cd BUILD
$ cmake [options] ..
$ make
$ make test  // if test option is specified.
$ sudo make install
~~~

### Options

`-D INSTALL_DIR=` *Install_directory*

>  Specify the directory that this library will be installed. Built library is
   installed at `install_directory/lib` and the header files are placed at
   `install_directory/include`.

`-D enable_fapi=` {no | yes}

>  This option is for building Fortran API. Default is no.

`-D enable_test=` {no | yes}

>  This option turns on compiling sample codes and execute the tests. Default is no.

`-D with_MPI=` {no | yes}

>  If you use an MPI library, specify `with_MPI=yes`, otherwise no or you can omit.


The default compiler options are described at the top level CMakeLists.txt file.
See the detail at BUILD OPTION section. If you need to change compiler flags,
you can specify by `CMAKE_C_FLAGS`, `CMAKE_CXX_FLAGS`, and `CMAKE_Fortran_FLAGS`, respectively. These FLAGS override the default option `-O3`.

~~~
-D CMAKE_C_FLAGS=options
-D CMAKE_CXX_FLAGS=options
-D CMAKE_Fortran_FLAGS=options
~~~

* `-Wno-dev` option suppresses warnings for developers.


## Configure Examples

### INTEL/GNU/PGI compiler

  ~~~
  $ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Denable_fapi=yes -Denable_test=yes
          -Dwith_MPI=yes -DCMAKE_C_COMPILER=mpicc -DCMAKE_CXX_COMPILER=mpicxx ..
  ~~~


### FUJITSU compiler / Fugaku, fx10, fx100, K computer on login nodes (Cross compilation) and intel TCS environment

~~~
$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain_Fugaku.cmake -Dwith_MPI=yes -Denable_fapi=yes -Denable_test=yes ..

$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain_fx10.cmake -Dwith_MPI=yes -Denable_fapi=yes -Denable_test=yes ..

$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain_fx100.cmake -Dwith_MPI=yes -Denable_fapi=yes -Denable_test=yes ..

$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain_K.cmake -Dwith_MPI=yes -Denable_fapi=yes -Denable_test=yes ..

$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain_intel_F_TCS.cmake -Dwith_MPI=yes -Denable_fapi=yes -Denable_test=yes ..
~~~


##### Note
- On Fujitsu machines(Fugaku, fx10, K, fx100), confirm appropriate directrory path for compiler environment.
- Before building, execute following command for clean. `$ make distclean`



## TEST
* If you specify the test option by `-Denable_test=yes`, you can
execute the intrinsic tests by;

	`$ make test` or `$ ctest`

* The detailed results are written in `BUILD/Testing/Temporary/LastTest.log` file.
Meanwhile, the summary is displayed for stdout.



## CONTRIBUTORS

* Kenji    Ono        *keno@{cc.kyushu-u.ac, riken, iis.u-tokyo.ac}.jp*
* Tomohiro Kawanabe
* Takafumi Suzuki
* Satoshi  Fuchikami
* Naoyuki  Sogo
* Eri      Takebe
* Syoyo    Fujita
* Ken      Uzawa
