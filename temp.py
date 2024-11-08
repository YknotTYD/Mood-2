
import random

for i in range(20):

    print(f"""map->lines[{i}][0] = {random.randrange(1500)};
map->lines[{i}][1] = {random.randrange(700)};
map->lines[{i}][2] = {random.randrange(1500)};
map->lines[{i}][3] = {random.randrange(700)};""".replace("\n", ""))
