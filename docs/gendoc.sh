#!/bin/bash

cd ../app
for d in `ls` ; do
  cd $d
  doxygen
  cd ..
done
