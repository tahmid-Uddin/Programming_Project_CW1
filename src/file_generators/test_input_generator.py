import random
movement = ("W\n", "A\n", "S\n", "D\n")

for i in range(1,26):
    file_name = f"src/test_inputs/movement_inputs/input_{i}.txt"
    string = ""

    for i in range(0, random.randint(10,150)):
        string += random.choice(movement)

    string += "END\n"

    with open(file_name, 'w') as file:
        file.write(string)
        