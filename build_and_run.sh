#!/bin/bash

clean=0
rebuild=0
onlybuild=0
while getopts "a:bcr" flag; do
    case "${flag}" in
        a) 
            echo "Flag -a was set with argument: $OPTARG"
            ;;
        b) 
            onlybuild=1 
            ;;
        c)
            clean=1
            ;;
        r)
            rebuild=1
            ;;
    esac
done

# Clean the objects if wanted.
if [ $clean -eq 1 ] || [ $rebuild -eq 1 ]; then
    
    echo
    echo "********************"
    echo "Cleaning..."
    make clean

    # Exit if only cleaning.
    if [ $clean -eq 1 ]; then
        exit 0
    fi
fi

echo
echo "********************"
echo "Building..."
echo

# Build.
make

if [ $? -ne 0 ]; then

    echo
    echo "********************"
    echo "Build FAILED!"
    exit $?

fi

# Exit if only building.
if [ $onlybuild -eq 1 ]; then
    echo 
    echo "********************"
    echo "Build succeeded, exiting..."
    echo

    exit 0
fi

echo 
echo "********************"
echo "Running the game..."
echo

# Run.
./game

echo
echo "********************"
echo "Game ended."
