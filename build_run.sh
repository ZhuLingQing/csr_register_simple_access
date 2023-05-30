#!/bin/bash

tmp_path=`pwd`

echo "    >>>>> cpp_test <<<<<"

test_cpp_path=$tmp_path/csr_test_cpp/test
cd $test_cpp_path
./build_run.sh
cd $tmp_path

echo "    >>>> c_test <<<<<"

test_c_path=$tmp_path/csr_test/test
cd $test_c_path
./build_run.sh
cd $tmp_path

