# Add " ->" to the end of every line

# Get all input
lines = []
for t in range(174):
    lines.append(input())

# Append data to each line
for i in range(len(lines)):
    lines[i] = lines[i] + ' ->'

print()

# Output
for line in lines:
    print(line)