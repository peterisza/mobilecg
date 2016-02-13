#!/bin/bash

EXTENSIONS="*.cpp *.h *.rb *.s *.ld makefile*"
TO=UTF-8

function convert {
	if [ "`uname`" == "Darwin" ]; then
		#MAC
		
		ENCODING=`file -I $1|sed 's/ //g'|sed 's/charset=/ /g'|awk '{print $2}'`
	else
		ENCODING=`file ./ -bi $1|awk -F "=" '{print $2}'`
	fi
	
	if [ "$ENCODING" != "unknown-8bit" ] && [ "$ENCODING" != "utf-8" ]; then
		echo "    ENCODING IS $ENCODING"
		iconv -f $ENCODING -t $TO $1 > $1.new
		if [ $? -ne 0 ]; then
			echo "CONVERSION FAILED"
			exit -1
		fi
		
		mv $1.new $1
		
		dos2unix $1 2>/dev/null
	fi
	
}

function fixExtensions {
	FILES=`find ./ -iname $1`
	for file in $FILES; do
		echo "Converting file $file"
		convert $file
	done
	
}


for ext in $EXTENSIONS; do
	fixExtensions $ext
done
