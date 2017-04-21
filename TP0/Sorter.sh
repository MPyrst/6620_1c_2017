#!/usr/bin/env bash
#	Usage: ./Sorter.sh filename

# 	Input: filename
#	Output: filename_Sorted. File with the words sorted.

if [ "$#" -ne 1 ]
then	echo 'No se pasó ningún archivo.'
	exit 1
fi

#LC_COLLATE=C sort : Case sensitive como el strcmp de C
splittedText=`cat $1`
sortedText=$(for word in $splittedText; do
		echo "$word"
	done | LC_COLLATE=C sort )

echo $sortedText >> $1_Sorted




