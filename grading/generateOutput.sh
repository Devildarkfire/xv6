#!/bin/bash
if [ "$#" -ne 1 ]; then 
    echo "Usage: ./generateOutput.sh outputdir"
    exit
fi
echo "Output: $1"
OUTDIR=$1


for i in $(ls -d */)
do	
	echo ---------------------------------------------------------------
	cd $i
	pwd	
	./master.sh my_shell.c
	cd ..
	
done

rm -f xv6-public
cp -r xv6-public-org/ xv6-public/

cp student_modified_files/* xv6-public/ ####there could be a problem if students include their makefiles which do not make the testcases 

python3 helper.py

mkdir $OUTDIR -p
cp xv6-public/out*.txt $OUTDIR
