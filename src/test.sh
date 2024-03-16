#!/bin/bash

gcc main.c -o misc/main
all_counter=0
pass_counter=0


echo -e "--Testing File name Validity--"

# The name of the file is not given as a command line argument
# Expected: raises an error and exits program
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


# The name of the file is given, but the file name is invalid/doesn't exist
# Expected: raises an error and exits the program
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


echo -e "\n\n\n--Testing Invalid Maze Types--"

# Loops through all the test mazes in the invalid maze folder
# and checks them against the criteria of a valid maze
filename="test_inputs/invalid_mazes.txt"
while IFS= read -r line
do
    ((all_counter++))
    invalid=0
    echo $line
    eval "$line"

    # Test for mazes size, where both the height and width are out
    # of bounds or either the height or the width are out of bounds.
    # Expected: raises an error and exits the program.
    printf "Test $all_counter.1 - Maze size out of bounds:"
    if grep -q "Error: Invalid Maze size" misc/tmp
    then
        echo -e "\e[34m   TRUE\e[0m"
        invalid=1
    else
        echo -e "\e[35m   FALSE\e[0m"
    fi
    
    # Test for mazes content, where is it made up of characters other
    # than #, ' ', S or E.
    # Expected: raises an error and exits the program.
    printf "Test $all_counter.2 - Maze has invalid characters:"
    if grep -q "Error: Unknown Characters in the Maze" misc/tmp
    then
        echo -e "\e[34m   TRUE\e[0m"
        invalid=1
    else
        echo -e "\e[35m   FALSE\e[0m"
    fi

    # Test for mazes content, where it checks for only 1 S and 1 E character.
    # Expected: raises an error and exits the program.
    printf "Test $all_counter.3 - Maze doesn't have 1 Start and 1 Exit:"
    if grep -q "Error: Has invalid number of Start and Exits" misc/tmp
    then
        echo -e "\e[34m   TRUE\e[0m"
        invalid=1
    else
        echo -e "\e[35m   FALSE\e[0m"
    fi

    # Test for mazes uniformity, where all the rows have to be the same length
    # Expected: raises an error and exits the program.
    printf "Test $all_counter.4 - Maze is not a rectangle:"
    if grep -q "Error: All rows and columns are not the same size" misc/tmp
    then
        echo -e "\e[34m   TRUE\e[0m"
        invalid=1
    else
        echo -e "\e[35m   FALSE\e[0m"
    fi


    if [[ "$invalid" == 1 ]]
    then 
        echo -e "Overall Result:\e[32m   PASS\e[0m\n"
        ((pass_counter++))
    else
        echo -e "Overall Result:\e[31m   FAIL\e[0m\n"
    fi

done < "$filename"




echo -e "\n\n--Testing Valid Maze Types--"

# Loops through all the test mazes in the valid maze folder
# and checks them against the criteria of a valid maze
filename="test_inputs/valid_mazes.txt"
while IFS= read -r line
do
    ((all_counter++))
    invalid=0
    echo $line
    echo q | eval "$line"

    # Test for mazes size, where both the height and width are out
    # of bounds or either the height or the width are out of bounds.
    # Expected: no error raised and program continues as normal.
    printf "Test $all_counter.1 - Maze size in the bounds"
    if grep -q "Error: Invalid Maze size" misc/tmp
    then
        echo -e "\e[35m   FALSE\e[0m"
        invalid=1
    else
        echo -e "\e[34m   TRUE\e[0m"
    fi

    # Test for mazes content, where is it made up of characters other
    # than #, ' ', S or E.
    # Expected: no error raised and program continues as normal.
    printf "Test $all_counter.2 - Maze has does not have invalid characters"
    if grep -q "Error: Unknown Characters in the Maze" misc/tmp
    then
        echo -e "\e[35m   FALSE\e[0m"
        invalid=1
    else
        echo -e "\e[34m   TRUE\e[0m"
    fi

    # Test for mazes content, where it checks for only 1 S and 1 E character.
    # Expected: no error raised and program continues as normal.
    printf "Test $all_counter.3 - Maze has only 1 Start and 1 Exit"
    if grep -q "Error: All rows and columns are not the same size" misc/tmp
    then
        echo -e "\e[35m   FALSE\e[0m"
        invalid=1
    else
        echo -e "\e[34m   TRUE\e[0m"
    fi

    # Test for mazes uniformity, where all the rows have to be the same length
    # Expected: no error raised and program continues as normal.
    printf "Test $all_counter.4 - Maze is a rectangle"
    if grep -q "Error: All rows and columns are not the same size" misc/tmp
    then
        echo -e "\e[35m   FALSE\e[0m"
        invalid=1
    else
        echo -e "\e[34m   TRUE\e[0m"
    fi

    if [[ "$invalid" == 0 ]]
    then 
        echo -e "Overall Result:\e[32m   PASS\e[0m\n"
        ((pass_counter++))
    else
        echo -e "Overall Result:\e[31m   FAIL\e[0m\n"
    fi

done < "$filename"



echo -e "\n\n--Testing User Inputs--"

# Loops through the contents of a file containing a list of 
# invalid inputs, and checks if they are in the list of 
# valid inputs - W,A,S,D,M,w,a,s,d,m.
# Expected: raises an error, and allows the user to try again.
filename="test_inputs/invalid_user_inputs.txt"
while IFS= read -r line
do
    ((all_counter++))
    echo -n "Test $all_counter - Invalid User inputs ($line)"
    printf "$line\nq" | ./misc/main test_inputs/student_mazes/valid/reg_5x5.txt > misc/tmp
    if grep -q "Error: Invalid user input" misc/tmp
    then
        echo -e "\e[32m   PASS\e[0m"
        ((pass_counter++))
    else
        echo -e "\e[31m   FAIL\e[0m"
    fi
done < "$filename"



# Loops through the contents of a file containing a list of 
# invalid inputs, and checks if they are in the list of 
# valid inputs - W,A,S,D,M,w,a,s,d,m.
# Expected: no errors raised, and the program continues as normal.
filename="test_inputs/valid_user_inputs.txt"
while IFS= read -r line
do
    ((all_counter++))
    echo -n "Test $all_counter - Valid User inputs ($line)" 
    printf "$line\nq" | ./misc/main test_inputs/student_mazes/valid/reg_5x5.txt > misc/tmp
    if grep -q "Error: Invalid user input" misc/tmp
    then
        echo -e "\e[31m   FAIL\e[0m"
    else
        echo -e "\e[32m   PASS\e[0m"
        ((pass_counter++))
    fi
done < "$filename"
echo ""


# Moves the player to the right and prints out the current
# state of the maze. Compares the current state to the expected
# state to confirm if the player moved correctly
# Expected: displayed maze state is equal to the expected maze state
((all_counter++))
echo -n "Test $all_counter - Correctly Moves to the Right" 
printf "D\nM\nq" | ./misc/main test_inputs/student_mazes/valid/empty_5x5.txt > misc/tmp
if grep -q "# SX#" misc/tmp
then
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m"
fi


# Moves the player to the left and prints out the current
# state of the maze. Compares the current state to the expected
# state to confirm if the player moved correctly
# Expected: displayed maze state is equal to the expected maze state
((all_counter++))
echo -n "Test $all_counter - Correctly Moves to the Left" 
printf "A\nM\nq" | ./misc/main test_inputs/student_mazes/valid/empty_5x5.txt > misc/tmp
if grep -q "#XS #" misc/tmp
then
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m"
fi


# Moves the player up and prints out the current
# state of the maze. Compares the current state to the expected
# state to confirm if the player moved correctly
# Expected: displayed maze state is equal to the expected maze state
((all_counter++))
echo -n "Test $all_counter - Correctly Moves Up" 
printf "W\nM\nq" | ./misc/main test_inputs/student_mazes/valid/empty_5x5.txt > misc/tmp
if grep -q "  X #" misc/tmp
then
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m"
fi


# Moves the player down and prints out the current
# state of the maze. Compares the current state to the expected
# state to confirm if the player moved correctly
# Expected: displayed maze state is equal to the expected maze state
((all_counter++))
echo -n "Test $all_counter - Correctly Moves Down" 
printf "S\nM\nq" | ./misc/main test_inputs/student_mazes/valid/empty_5x5.txt > misc/tmp
if grep -q "# X  " misc/tmp
then
    echo -e "\e[32m   PASS\e[0m"
    ((pass_counter++))
else
    echo -e "\e[31m   FAIL\e[0m"
fi




echo -e "\n--Testing Movement Through Maze--"

# Moves player into a square containing a wall.
# Expected: raises an error and allows user to try again.
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


# Moves player into a square containing a blank space
# Expected: no error raised, and player moved to the new square
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


# Moves player off the edge of the map
# Expected: raises an error and allows user to try again.
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


# Moves player off the edge of the map
# Expected: raises an error and allows user to try again.
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


# Moves player off the edge of the map
# Expected: raises an error and allows user to try again.
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


# Moves player off the edge of the map
# Expected: raises an error and allows user to try again.
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


# Loops through the mazes in the valid mazes folder and runs
# some random user inputs to check if an unexpected error causes
# the program to crash. If no errors, the final input will be 
# "END", which is an invalid input, hence will raise the invalid 
# user input error.
# Expected: no unexpected errors - all inputs run correctly, and 
# Invalid user input error raised at the end.
filename="test_inputs/walking_around_mazes.txt"
while IFS= read -r line
do
    ((all_counter++))
    eval "$line"
    printf "Test $all_counter - Walking around a random maze"
    if grep -q "Shutting down program" misc/tmp
    then
        echo -e "\e[32m   PASS\e[0m"
        ((pass_counter++))

    elif grep -q "Congratulations! You have completed the maze!" misc/tmp
    then
        echo -e "\e[32m   PASS\e[0m"
        ((pass_counter++))

    else
        echo -e "\e[31m   FAIL\e[0m"
    fi
done < "$filename"





echo -e "\n--Testing Game End State--"

# Loops through mazes in the solvable maze folder and traverses
# the maze using the solution file.
# Expected: player reaches E and a congratulations message is displayed.
filename="test_inputs/completed_mazes.txt"
while IFS= read -r line
do
    ((all_counter++))
    eval "$line"

    printf "Test $all_counter - Displays game end message"
    if grep -q "Congratulations! You have completed the maze!" misc/tmp
    then 
        echo -e "\e[32m   PASS\e[0m"
        ((pass_counter++))
    
    else
        echo -e "\e[31m   FAIL\e[0m"
    fi

done < "$filename"

fail_counter=$((all_counter - pass_counter))
echo -e "\n\n--Test Results--"
echo "Total Tests: $all_counter"
echo "Tests Passed: $pass_counter"
echo "Tests Failed: $fail_counter"