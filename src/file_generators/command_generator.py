from os import listdir
from os.path import isfile, join

path = "src/test_inputs/student_mazes/invalid"
directory = [filename for filename in listdir(path) if isfile(join(path, filename))]

file_name = f"invalid_mazes.txt"
counter = 1
with open(file_name, 'w') as file:
    for filename in directory:
        filename = filename.split(".")[0]
        file.write(f"./misc/main test_inputs/student_mazes/invalid/{filename}.txt > misc/tmp\n")
        counter += 1