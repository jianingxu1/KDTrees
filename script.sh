#!/bin/bash

echo "TypeOfTree is: $1"
typeOfTree=$1

for k in {2..6}
do
  echo "Processing for type of tree $typeOfTree and dimension $k"
  ./main <<EOF
  $typeOfTree $k
EOF
done
