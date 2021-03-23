#!/bin/bash
if [ $# -lt 1 ]; then
	echo "Usage: ./count-items.sh <path>"
	exit 2
fi
dir=$1
if [ ! -e "$dir" ]; then
        echo "No such path"
        exit 1
fi
if [ ! -d "$dir" ]; then
        echo 1
fi
if [ -d "$dir" ]; then
	counter=1
	((counter+=`source num-readable-files.sh`))
        for i in `source list-readable-dirs.sh`
        do
             ((counter+=`source count-items.sh $dir/$i`))
        done
echo $counter
exit 0
fi
