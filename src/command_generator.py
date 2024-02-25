from os import listdir
from os.path import isfile, join

path = "src/test_inputs/student_mazes/solvable"
directory = [filename for filename in listdir(path) if isfile(join(path, filename))]

file_name = f"commands.txt"
with open(file_name, 'w') as file:
    for filename in directory:
        filename = filename.split(".")[0]
        file.write(f"./misc/main test_inputs/student_mazes/solvable/{filename}.txt < test_inputs/student_mazes/solvable/{filename}_solution.txt > misc/tmp\n")