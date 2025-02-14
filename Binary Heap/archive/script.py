import random

with open("test_cases.txt", "w") as f:
    for _ in range(1, 201):
        n = random.randint(1, 10)
        array = [random.randint(0, 100) for _ in range(n)]
        f.write(f"{n}\n")
        if n > 0:
            f.write(" ".join(map(str, array)) + "\n")
        else:
            f.write("\n")