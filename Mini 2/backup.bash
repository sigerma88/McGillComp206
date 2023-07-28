#!/bin/bash

########################################################################
#                                AUTHOR
# Name: Siger Ma
# Department: Mcgill, Faculty of Engineering, ECSE, Software Engineering
# McGill ID: 261051828
# Email: siger.ma@mail.mcgill.ca
########################################################################
#                             DOCUMENTATION
# This is a bash script to take an individual file or a directory to
# back them up in a tar file.
#
# Instructions and arguments:
#   ./backup.bash [backup directory] [file or dir to backup]
#
# Exit code:
#   0 - Success
#   1 - Error - Wrong number of arguments
#   2 - Error - Wrong back up source or wrong backup destination
#   3 - Error - Override cancelled
#########################################################################

# Variables
currentDate=$(date +%Y%m%d)
sourceFileDirectory=$2
destinationDirectory=$1

# Detect error 1
if [ $# -ne 2 ]; then
	echo "Error: Expected two input parameters."
	echo "Usage: ./backup.bash <backupdirectory> <fileordirtobackup>"
	exit 1
fi

# Detect error 2
if [ ! -d "$destinationDirectory" ]; then
	echo "Error: The directory '$destinationDirectory' does not exist."
	exit 2
elif [ ! -d "$sourceFileDirectory" -a ! -f "$sourceFileDirectory" ]; then
	echo "Error: The file or directory $sourceFileDirectory does not exist."
	exit 2
elif [ $sourceFileDirectory -ef $destinationDirectory ]; then
	echo "Error: $destinationDirectory and $sourceFileDirectory are the same directory."
	exit 2
fi

# Compute variables
sourceFileDirectoryBasename=$(basename $sourceFileDirectory)
sourceFileDirectoryDirname=$(dirname $sourceFileDirectory)
tarName="$sourceFileDirectoryBasename.$currentDate.tar"

# Detect error 3
if [ -f "$destinationDirectory/$tarName" ]; then
	echo "Backup file $tarName already exists. Overwrite? (y/n)"
	read confirmation
	if [ $confirmation != "y" ]; then
		echo "Error: Backup cancelled"
		exit 3
	fi
fi

# Tar
tar -cf "$destinationDirectory/$tarName" -C $sourceFileDirectoryDirname $sourceFileDirectoryBasename &> /dev/null
exit 0

