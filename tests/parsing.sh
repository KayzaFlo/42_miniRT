#!/bin/sh

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

scenes_dir=scenes/
valgrind="valgrind --show-leak-kinds=all --track-origins=yes --leak-check=full --log-file="filename""

mrt=./miniRT

echo -e "\n${Blue}Parsing Tests\n=======================\n"

path=$scenes_dir
files=$(ls $path)
for file in $files
do
    echo -e "\n${Purple}file name: $Yellow$file\n$White"
    $valgrind $mrt $path$file
    echo -e "\n${Red}LEAKS${Cyan}"
    grep "ERROR SUMMARY" filename
    echo "====================="
done

echo -e "\n${Purple}file name: ${Yellow}non_existant.rt\n$White"
$valgrind $mrt scenes/non_existant.rt
echo -e "\n${Red}LEAKS${Cyan}"
grep "ERROR SUMMARY" filename
echo "====================="

echo -e "$Green\nALL DONE\n"