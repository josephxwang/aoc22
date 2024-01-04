from functools import lru_cache

@cache
def rec_crack_geodes(time, robots, minerals, blueprint):
    global max_geode

    if time == 0:
        curr_geode = minerals[3]

        if curr_geode > max_geode:
            max_geode = curr_geode
            print(max_geode)

        return
    
    # Add minerals
    minerals = [minerals[i] + robots[i] for i in range(len(minerals))]

    # Try to buy each robot
    for rob_i in range(4):
        new_robots = [0,0,0,0]

        # Check each mineral requirement
        can_buy = True
        for min_i in range(4):
            if minerals[min_i] - robots[min_i] < blueprint[rob_i][min_i]:
                can_buy = False
                break
        
        if can_buy:
            new_robots[rob_i] += 1

            rec_crack_geodes(time-1, [robots[i] + new_robots[i] for i in range(len(robots))], [minerals[i] - blueprint[rob_i][i] for i in range(len(minerals))], blueprint)

    # Do nothing
    rec_crack_geodes(time-1, robots, minerals, blueprint)

def part1(): 
    global max_geode

    with open("19testpy.txt") as f:
        lines = [[int(n) for n in line.split()] for line in f]

    for line in lines:
        max_geode = 0
        quality = line[0]

        # Get robot costs
        blueprint = []
        blueprint.append([line[1],0,0,0])
        blueprint.append([line[2],0,0,0])
        blueprint.append([line[3],line[4],0,0])
        blueprint.append([line[5],0,line[6],0])

        print(rec_crack_geodes(24, [1,0,0,0], [0,0,0,0], blueprint))

if __name__ == "__main__":
    print(part1())