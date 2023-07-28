#!/bin/bash

########################################################################
#                                AUTHOR
# Name: Siger Ma
# Department: Mcgill, Faculty of Engineering, ECSE, Software Engineering
# McGill ID: 261051828
# Email: siger.ma@mail.mcgill.ca
########################################################################
#                             DOCUMENTATION
# This is a bash script to compare two directories and present their
# differences.
#
# Instructions and arguments:
#   ./deltad.bash [original directory] [comparison directory]
#
# Exit code:
#   0 - Success - No difference between directories
#   1 - Error - Wrong number of arguments
#   2 - Error - Arguments are not directories or are the same
#   3 - Success - Directories differ
#########################################################################

# Variables
originalDirectory=$1
comparisonDirectory=$2

# Detect error 1
if [ $# -ne 2 ]; then
	echo "Error: Expected two input parameters."
	echo "Usage: ./deltad.bash <originaldirectory> <comparisondirectory>"
	exit 1
fi

# Detect error 2
if [ ! -d "$originalDirectory" ]; then
	echo "Error: Input parameter #1 '$originalDirectory' is not a directory."
	echo "Usage: ./deltad.bash <originaldirectory> <comparisondirectory>"
	exit 2
elif [ ! -d "$comparisonDirectory" ]; then
	echo "Error: Input parameter #2 '$comparisonDirectory' is not a directory."
	echo "Usage: ./deltad.bash <originaldirectory> <comparisondirectory>"
	exit 2
elif [ $originalDirectory -ef $comparisonDirectory ]; then
	echo "Error: $originalDirectory and $comparisonDirectory are the same directory."
	echo "Usage: ./deltad.bash <originaldirectory> <comparisondirectory>"
	exit 2
fi

# Computed variables
originalDirectoryName=$(basename $originalDirectory)
comparisonDirectoryName=$(basename $comparisonDirectory)
originalDirectoryPath=$(pwd $originalDirectory)
comparisonDirectoryPath=$(pwd $comparisonDirectory)

# Detect differences
diff -q $originalDirectory $comparisonDirectory 2> /dev/null | while read diffOutput; do
	set $diffOutput
	if [[ $diffOutput =~ ^Files.*differ$ ]]; then
		echo "$originalDirectoryPath/$originalDirectoryName/$(basename $2) differs"
	elif [[ $diffOutput =~ ^Only[[:space:]]in ]]; then
		if [ $3 = "$originalDirectory:" ]; then
			missingFile="$originalDirectory/$4"
			if [ -f "$missingFile" ]; then
				echo "$comparisonDirectoryPath/$comparisonDirectoryName/$4 is missing"
			fi
		elif [ $3 = "$comparisonDirectory:" ]; then
			missingFile="$comparisonDirectory/$4"
			if [ -f "$missingFile" ]; then
				echo "$originalDirectoryPath/$originalDirectoryName/$4 is missing"
			fi
		fi
	fi
done

# Difference found, exit with code 3
if [ $((PIPESTATUS[0])) = 1 ] ; then
	exit 3
fi

# No difference found
exit 0

