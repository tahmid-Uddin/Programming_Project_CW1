#Created by Chat-gpt - edited functionality to better fit needs
#Prompt:
#   Mazes are made up of four characters:
#   ‘#’ - A wall which the player cannot move across
#   ‘  ‘ (a space) - A path which the player can move across
#   ‘S’ - The place where the player starts the maze
#   ‘E’ - The place where the player exits the maze
#   A maze has a height and a width, with a maximum of 100 and a minimum of 5.
#   The height and width do not have to be equal – as long as both are within the accepted range.
#   Within a maze, each ‘row’ and ‘column’ should be the same length – the maze should be a rectangle.
#   Can you write me a python script that create valid mazes, writes them into a .txt file, with the naming convention reg_[height]x[width].txt?

import random

def generate_maze(height, width):
    maze = [['#' for _ in range(width)] for _ in range(height)]
    # Randomly create paths
    for i in range(0, height):
        for j in range(0, width):
            if random.random() < random.randint(5,9) / 10:  # Adjust probability for more open paths
                maze[i][j] = ' '

    maze[1][1] = 'S'
    maze[random.randint(2,height-1)][random.randint(2,width-1)] = 'E'

    return maze

def save_maze_to_file(maze, height, width):
    file_name = f"src/test_inputs/student_mazes/invalid/ireg_{height}x{width}.txt"
    with open(file_name, 'w') as file:
        for row in maze:
            file.write(''.join(row) + '\n')

def create_and_save_maze(height, width):
    maze = generate_maze(height, width)
    save_maze_to_file(maze, height, width)

# Define sizes for test mazes
number_of_mazes = 3
maze_sizes = []
for i in range(0, number_of_mazes):
    height = random.randint(5,10)
    width = random.randint(5,10)
    maze_sizes.append((height, width))

# Create and save mazes
for size in maze_sizes:
    height, width = size
    create_and_save_maze(height, width)
