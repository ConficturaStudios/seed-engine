#!/bin/bash
set -e
set -u
set -o pipefail

BLACK='\033[0;30m'
DARK_GRAY='\033[1;30m'
RED='\033[0;31m'
LIGHT_RED='\033[1;31m'
GREEN='\033[0;32m'
LIGHT_GREEN='\033[1;32m'
BROWN_ORANGE='\033[0;33m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
LIGHT_BLUE='\033[1;34m'
PURPLE='\033[0;35m'
LIGHT_PURPLE='\033[1;35m'
CYAN='\033[0;36m'
LIGHT_CYAN='\033[1;36m'
LIGHT_GRAY='\033[0;37m'
WHITE='\033[1;37m'
NC='\033[0m'

> ToDoLists.txt

#Track todo changes (completed, add, stayed the same, etc.)

for file in $(find $(pwd)/core/*/ -name "*.cpp" -or -name "*.hpp" -or -name "*.h" -type f)
do

    COUNT=0
    #echo "Checking file '$file' for TODOs..."
    while IFS= read -r line; do
        COUNT=$(( $COUNT + 1 ))
        if [[ $line =~ ^.*//TODO:\s*(.*)$ ]]; then
            COLOR=$CYAN
            printf "CORE: [$(basename $file) line $COUNT]:${BASH_REMATCH[1]}" >> ToDoLists.txt
            echo -e "CORE: [$(basename $file) line $COUNT]:${COLOR}${BASH_REMATCH[1]}${NC}"
        fi
    done < $file
    #echo "Done with file '$file'."
done
#echo "Done processing Core."


for file in $(find $(pwd)/editor/*/ -name "*.cpp" -or -name "*.hpp" -or -name "*.h" -type f)
do

    COUNT=0
    #echo "Checking file '$file' for TODOs..."
    while IFS= read -r line; do
        COUNT=$(( $COUNT + 1 ))
        if [[ $line =~ ^.*//TODO:\s*(.*)$ ]]; then
            echo "EDITOR: [$(basename $file) line $COUNT]:${BASH_REMATCH[1]}" >> ToDoLists.txt
            echo "EDITOR: [$(basename $file) line $COUNT]:${BASH_REMATCH[1]}"
        fi
    done < $file
   #echo "Done with file '$file'."
done
#echo "Done processing Editor."