import os
import subprocess

target_dir = "/home/lyes/Documents/GCPC-2k26-Challenges/challenges/dungeon-escape/data/secret"
solution_path = "/home/lyes/Documents/GCPC-2k26-Challenges/challenges/dungeon-escape/submissions/accepted/solution.py"

os.makedirs(target_dir, exist_ok=True)

test_cases = []

# Case 1: Impossible
test_cases.append((
    "Impossible to reach",
    """3 3
S..
###
..E"""
))

# Case 2: Key unreachable, door blocks exit
test_cases.append((
    "Key unreachable",
    """3 4
S..K
###.
k##E"""
))

# Case 3: S and E adjacent
test_cases.append((
    "S and E adjacent",
    """2 2
SE
.."""
))

# Case 4: 1D corridor (Needs key)
test_cases.append((
    "1D corridor possible",
    "1 15\nS.....k.....K.E"
))

# Case 5: 1D impossible
test_cases.append((
    "1D impossible",
    "1 10\nS....K...kE"
))

# Case 6: Multiple doors
test_cases.append((
    "Multiple doors",
    """5 5
S...k
#####
K.K.K
#####
E...."""
))

# Case 7: Go around vs use key (Go around is longer)
test_cases.append((
    "Go around vs use key",
    """5 7
S...K.E
###.#.#
k.....#
###.###
......."""
))

# Case 8: Large empty grid
test_cases.append((
    "Large empty",
    f"500 500\nS{'.' * 498}K\n" + "\n".join(['.' * 500] * 498) + f"\nk{'.' * 498}E"
))

# Case 9: Large Zigzag
def generate_zigzag(n, m):
    grid = [['.'] * m for _ in range(n)]
    for i in range(1, n, 2):
        for j in range(m - 1):
            if (i // 2) % 2 == 0:
                grid[i][j] = '#'
            else:
                grid[i][j + 1] = '#'
    grid[0][0] = 'S'
    grid[n-1][m-1] = 'E'
    grid[n-1][0] = 'k'
    grid[0][m-1] = 'K'
    return f"{n} {m}\n" + "\n".join("".join(row) for row in grid)

test_cases.append((
    "Large Zigzag",
    generate_zigzag(499, 500)
))

# Case 10: Heavy backtracking
test_cases.append((
    "Heavy backtracking",
    """5 10
S........#
##########
........k#
##########
K........E"""
))

for i, (name, content) in enumerate(test_cases, 1):
    in_file = os.path.join(target_dir, f"{i}.in")
    ans_file = os.path.join(target_dir, f"{i}.ans")
    desc_file = os.path.join(target_dir, f"{i}.desc")
    
    with open(in_file, 'w') as f:
        f.write(content.strip() + '\n')
        
    with open(desc_file, 'w') as f:
        f.write(name + '\n')
        
    cmd = f"python3 {solution_path} < {in_file} > {ans_file}"
    subprocess.run(cmd, shell=True)

print("Generated 10 secret test cases successfully.")
