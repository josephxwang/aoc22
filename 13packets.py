import ast

from functools import cmp_to_key

def recCompareLists(l1, l2):
    # Pointer
    p = 0

    while p < len(l1) and p < len(l2):
        # If both integers
        if type(l1[p]) == int and type(l2[p]) == int:
            # False if left larger than right
            if l1[p] > l2[p]:
                return False
            
            # True if left smaller than right
            elif l1[p] < l2[p]:
                return True
        
        # If both lists
        elif type(l1[p]) == list and type(l2[p]) == list:
            res = recCompareLists(l1[p], l2[p])

            if res != None:
                return res

        # If one int and one list
        elif type(l1[p]) == int and type(l2[p]) == list:
            res = recCompareLists([l1[p]], l2[p])

            if res != None:
                return res

        elif type(l1[p]) == list and type(l2[p]) == int:
            res = recCompareLists(l1[p], [l2[p]])

            if res != None:
                return res

        # Stop if left larger than right
        # if l1[p] > l2[p]:
        #     return False

        p += 1
    
    # If right list out of elements first
    if p < len(l1) and p >= len(l2):
        return False
    
    # If left list out of elements first
    if p >= len(l1) and p < len(l2):
        return True


def recCompareLists2(l1, l2):
    # Pointer
    p = 0

    while p < len(l1) and p < len(l2):
        # If both integers
        if type(l1[p]) == int and type(l2[p]) == int:
            # False if left larger than right
            if l1[p] > l2[p]:
                return 1
            
            # True if left smaller than right
            elif l1[p] < l2[p]:
                return -1
        
        # If both lists
        elif type(l1[p]) == list and type(l2[p]) == list:
            res = recCompareLists2(l1[p], l2[p])

            if res != None:
                return res

        # If one int and one list
        elif type(l1[p]) == int and type(l2[p]) == list:
            res = recCompareLists2([l1[p]], l2[p])

            if res != None:
                return res

        elif type(l1[p]) == list and type(l2[p]) == int:
            res = recCompareLists2(l1[p], [l2[p]])

            if res != None:
                return res

        # Stop if left larger than right
        # if l1[p] > l2[p]:
        #     return False

        p += 1
    
    # If right list out of elements first
    if p < len(l1) and p >= len(l2):
        return 1
    
    # If left list out of elements first
    if p >= len(l1) and p < len(l2):
        return -1


# Get data as nested lists
with open("input.txt") as f:
    lines = [ast.literal_eval(line.strip()) for line in f if line != "\n"]

sum = 0
for i in range(0, len(lines), 2):
    l1 = lines[i]
    l2 = lines[i+1]

    res = recCompareLists(l1, l2)

    # print(res)

    if res:
        # print((i // 2 + 1))
        sum += (i // 2 + 1)

print(sum)

lines.sort(key=cmp_to_key(recCompareLists2))

i1 = lines.index([[2]]) + 1
i2 = lines.index([[6]]) + 1

print(i1 * i2)

# for line in lines:
#     print(line)

# l1 = [1,[2,[3,[4,[5,6,0]]]],8,9]
# l2 = [1,[2,[3,[4,[5,6,7]]]],8,9]

# print(recCompareLists(l1, l2))
# print(recCompareLists2(l1, l2))