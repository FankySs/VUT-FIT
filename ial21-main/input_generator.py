import random
import string
import pandas as pd

size = 1_000_000

file = open(f"tests/input_{size}.txt", "a")

vertex = []

counter = 0

vertex_dict = {}  # dictionary because is much faster than List.

while True:
    vertex_1 = random.choice(string.ascii_letters) + random.choice(string.ascii_letters)
    vertex_2 = random.choice(string.ascii_letters) + random.choice(string.ascii_letters)

    if vertex_1 != vertex_2 and vertex_dict.get(vertex_1 + vertex_2) is None:
        vertex_dict[vertex_1 + vertex_2] = {
            "vertex_1": vertex_1,
            "vertex_2": vertex_2
        }
        file.write(f"{vertex_1} {vertex_2}\n")
        counter += 1

    if counter >= size:
        break
