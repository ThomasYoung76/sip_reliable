#!/bin/bash

# define case name. like "call_01"
case_name=$1
case_file=test_${case_name}.cpp
echo "case name is: ${case_name}"
echo "case file is: ${case_file}"

# test call
if [ $1 == "call" ]; then
  make -f test_${case_name}.mk clean
  make -f test_${case_name}.mk 
  cp -R bin/mips /home/rootfs/vt/fs_k2268s/mnt/user_rootfs/usr/sbin/
  echo "OK"
  exit
fi

# Reliability Test
if [ $2 == "reliability" ]; then
    echo "Reliability Test"
    echo "Generate makefile 'test_${case_name}.mk and make the makefile" 
  #handle file
  sed "s/test_call/test_${case_name}/" test_call.mk > test_tmp.mk
  sed "s/TestForUA/TestForReliability/" test_tmp.mk > test_${case_name}.mk
  #compile 
  make -f test_${case_name}.mk clean
  make -f test_${case_name}.mk 
  cp -R bin/mips /home/rootfs/vt/fs_k2268s/mnt/user_rootfs/usr/sbin/
  echo "OK"
  rm -rf test_${case_name}.mk
  exit
fi

# test others
if [ -f $case_file ];then 
  echo "Generate makefile 'test_${case_name}.mk and make the makefile" 
  #handle file
  sed "s/test_call/test_${case_name}/" test_call.mk > test_${case_name}.mk

  #compile 
  make -f test_${case_name}.mk clean
  make -f test_${case_name}.mk 
  cp -R bin/mips /home/rootfs/vt/fs_k2268s/mnt/user_rootfs/usr/sbin/
  echo "OK"
else
  echo "Error : case_name is uncorrect or case_file is not exist"
fi
# delete the mkfile
rm -rf test_${case_name}.mk
