#!/bin/bash

gcc main.c -o misc/main
all_counter=0
pass_counter=0


echo -e "--Testing File name Validity--"

#Testing when file name is not given
((all_counter++))
echo -n "Test $all_counter - Filename not given" 
./misc/main > misc/tmp
if grep -q "Error: Filename not given" misc/tmp
then
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m"
fi

((all_counter++))
echo -n "Test $all_counter - Filename is invalid"
./misc/main maze.txt > misc/tmp
if grep -q "Error: File doesn't exist" misc/tmp
then 
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m"
fi





echo -e "\n--Testing Invalid Maze Types--"
filename="test_inputs/invalid_mazes.txt"

while IFS= read -r line
do
    ((all_counter++))
    invalid=0
    $line

    printf "Test $all_counter.1 - Maze size out of bounds:"
    if grep -q "Error: Invalid Maze size" misc/tmp
    then 
        echo -e "   TRUE"
        invalid=1
    else
        echo -e "   FALSE"
    fi
    

    printf "Test $all_counter.2 - Maze has invalid characters:"
    if grep -q "Error: Unknown Characters in the Maze" misc/tmp
    then 
        echo -e "   TRUE"
        invalid=1
    else
        echo -e "   FALSE"
    fi


    printf "Test $all_counter.3 - Maze doesn't have 1 Start and 1 Exit:"
    if grep -q "Error: Has invalid number of Start and Exits" misc/tmp
    then 
        echo -e "   TRUE"
        invalid=1
    else
        echo -e "   FALSE"
    fi


    printf "Test $all_counter.4 - Maze is not a rectangle:"
    if grep -q "Error: All rows and columns are not the same size" misc/tmp
    then 
        echo -e "   TRUE"
        invalid=1
    else
        echo -e "   FALSE"
    fi


    if [[ "$invalid" == 1 ]]
    then 
        echo -e "Overall Result:\e[32m   PASS\e[0m\n"
        ((pass_counter++))
    else
        echo -e "Overall Result:\e[31m   FAIL\e[0m\n"
    fi

done < "$filename"





echo -e "--Testing Valid Maze Types--"

filename="test_inputs/valid_mazes.txt"
while IFS= read -r line
do
    ((all_counter++))
    $line

    printf "Test $all_counter.1 - Maze size in the bounds"
    if grep -q "Error: Invalid Maze size" misc/tmp
    then
        echo -e "\e[31m   FAIL\e[0m" 
    else
        echo -e "\e[32m   PASS\e[0m"
        ((pass_counter++))
    fi


    printf "Test $all_counter.2 - Maze has does not have invalid characters"
    if grep -q "Error: Unknown Characters in the Maze" misc/tmp
    then
        echo -e "\e[31m   FAIL\e[0m" 
    else
        echo -e "\e[32m   PASS\e[0m"
        ((pass_counter++))
    fi


    printf "Test $all_counter.3 - Maze is a rectangle"
    if grep -q "Error: All rows and columns are not the same size" misc/tmp
    then
        echo -e "\e[31m   FAIL\e[0m\n" 
    else
        echo -e "\e[32m   PASS\e[0m\n"
        ((pass_counter++))
    fi

done < "$filename"




echo -e "--Testing User Inputs--"

((all_counter++))
echo -n "Test $all_counter - Invalid User inputs" 
./misc/main test_inputs/student_mazes/valid/reg_5x5.txt < test_inputs/random_user_inputs.txt > misc/tmp
if grep -q "Error: Invalid user input" misc/tmp
then
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m"
fi





#GET TEST MAZES
#LOGIC FOR THIS IS:
#   Read valid maze
#   Go through a text file containing a set of moves
#   Print out player position
#   Check if the player position is equal to the expected position
#   Alternative to compare maze state instead of player position
echo -e "\n--Testing Movement Through Maze--"

((all_counter++))
echo -n "Test $all_counter - Walking into a wall" 
./misc/main test_inputs/student_mazes/valid/reg_5x5.txt < test_inputs/walk_into_wall.txt > misc/tmp
if grep -q "You cannot walk into a wall. Try moving somewhere else!" misc/tmp
then
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m"
fi


((all_counter++))
echo -n "Test $all_counter - Walking into a blank space" 
./misc/main test_inputs/student_mazes/valid/reg_5x5.txt < test_inputs/walk_into_space.txt > misc/tmp
if grep -q "You cannot walk into a wall. Try moving somewhere else!" misc/tmp
then
    echo -e "\e[31m   FAIL\e[0m"
else
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
fi


((all_counter++))
echo -n "Test $all_counter - Walking outside the map (left-side)" 
./misc/main test_inputs/student_mazes/valid/reg_5x5_nowall.txt < test_inputs/walk_outside_map_left.txt > misc/tmp
if grep -q "You cannot walk off the edge of the maze. Try moving somewhere else!" misc/tmp
then
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m"
fi


((all_counter++))
echo -n "Test $all_counter - Walking outside the map (right-side)" 
./misc/main test_inputs/student_mazes/valid/reg_5x5_nowall.txt < test_inputs/walk_outside_map_right.txt > misc/tmp
if grep -q "You cannot walk off the edge of the maze. Try moving somewhere else!" misc/tmp
then
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m"
fi


((all_counter++))
echo -n "Test $all_counter - Walking outside the map (top)" 
./misc/main test_inputs/student_mazes/valid/reg_5x5_nowall.txt < test_inputs/walk_outside_map_top.txt > misc/tmp
if grep -q "You cannot walk off the edge of the maze. Try moving somewhere else!" misc/tmp
then
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m"
fi


((all_counter++))
echo -n "Test $all_counter - Walking outside the map (bottom)" 
./misc/main test_inputs/student_mazes/valid/reg_5x5_nowall.txt < test_inputs/walk_outside_map_bottom.txt > misc/tmp
if grep -q "You cannot walk off the edge of the maze. Try moving somewhere else!" misc/tmp
then
    echo -e "\e[32m   PASS\e[0m\n"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m\n"
fi


filename="test_inputs/valid_mazes.txt"
while IFS= read -r line
do
    ((all_counter++))
    $line

    printf "Test $all_counter - Walking around a random maze"
    if grep -q "Error: Invalid Maze size" misc/tmp
    then 
        echo -e "\e[32m   PASS\e[0m"
        ((pass_counter++))
    else
        echo -e "\e[31m   FAIL\e[0m"
    fi

done < "$filename"





echo -e "\n--Testing Game End State--"

filename="test_inputs/completed_mazes.txt"
while IFS= read -r line
do
    ((all_counter++))
    $line

    printf "Test $all_counter - Displays game end message"
    if grep -q "Congratulations! You have completed the maze!" misc/tmp
    then 
        echo -e "\e[32m   PASS\e[0m"
        ((pass_counter++))
    else
        echo -e "\e[31m   FAIL\e[0m"
    fi

done < "$filename"


echo -e "\n\n--Test Results--"
echo "Total Tests: $all_counter"
echo "Tests Passed: $pass_counter"
