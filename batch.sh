#!/bin/bash
a=$1
for file in $a*
do
	echo $file
	com=$(./cr "$file" '1' |grep -E "(Function|Final Cost)")
	output="$com"
	echo "${output}"

done
