#!/bin/bash
if [ "$#" -ne 1 ]; then 
    echo "Usage: ./generateOutput.sh outputdir"
    exit
fi
echo "Output: $1"
OUTDIR=$1

python3 helper.py

mkdir $OUTDIR -p
cp xv6-public/out*.txt $OUTDIR
