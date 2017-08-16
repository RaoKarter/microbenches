#!/bin/bash

for d in src/*; do
  tarfile=`echo $d | sed 's/src\///'`.tar
  echo Generating $tarfile...
  pushd $d > /dev/null
  tar -cf ../../$tarfile *
  popd > /dev/null
done

echo Done.