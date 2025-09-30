#!/bin/bash

if [[ $# -ne 2 ]]; then
	echo "Need 2 arguments, cub3d and folder to maps"
	exit 1
fi

for file in $2*; do
	echo $file":"
	valgrind $1 $file
done
