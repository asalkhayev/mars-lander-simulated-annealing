import sys
import math
import random

#  Hyperparameters
SEQ_LEN = 60
TEMP_START = 120.0
TEMP_END = 0.1
ITERATIONS = 2500

GRAVITY = 3.711
MAX_ROT = 15
MAX_POWER_CHANGE = 1

#  Read surface & find landing zone
surfaceN = int(input())
surface = []
landing_x1 = landing_x2 = landing_y = None

for _ in range(surfaceN):
    x, y = map(int, input().split())
    surface.append((x, y))

for i in range(len(surface) - 1):
    (x1, y1), (x2, y2) = surface[i], surface[i + 1]
    if y1 == y2:
        landing_x1, landing_x2, landing_y = x1, x2, y1
        break

#  Simulation of a move sequence

def simulate(x, y, h_speed, v_speed, fuel, rot, power, seq):
    """Simulate the lander with the given move sequence."""
    for (drot, dpow) in seq:
        rot = max(-90, min(90, rot + drot))
        power = max(0, min(4, power + dpow))

        rad = math.radians(rot)
        ax = math.sin(rad) * power
        ay = math.cos(rad) * power - GRAVITY

        h_speed += ax
        v_speed += ay
        x += h_speed
        y += v_speed
        fuel -= power

        if y <= 0:
            break

    return x, y, h_speed, v_speed, fuel, rot, power

#  Score function

def score_state(x, y, hs, vs):
    """Higher score is better."""
    if y < landing_y - 50:
        return -10**9

    if x < landing_x1:
        dist = landing_x1 - x
    elif x > landing_x2:
        dist = x - landing_x2
    else:
        dist = 0

    return -3 * abs(dist) - 4 * abs(hs) - 6 * abs(vs)

#  Sequence helpers

def random_seq():
    """Create a random sequence of moves."""
    seq = []
    for _ in range(SEQ_LEN):
        drot = random.choice([-MAX_ROT, 0, MAX_ROT])
        dpow = random.choice([-MAX_POWER_CHANGE, 0, MAX_POWER_CHANGE])
        seq.append((drot, dpow))
    return seq

def mutate(seq, temperature):
    """Change a few random moves – more changes when temperature is high."""
    new = list(seq)
    count = max(1, int(1 + temperature / 20))
    for _ in range(count):
        i = random.randrange(SEQ_LEN)
        drot = random.choice([-MAX_ROT, 0, MAX_ROT])
        dpow = random.choice([-MAX_POWER_CHANGE, 0, MAX_POWER_CHANGE])
        new[i] = (drot, dpow)
    return new

#  Game loop

best_seq = random_seq()

while True:
    x, y, hs, vs, fuel, rot, power = map(int, input().split())

    _, _, hs2, vs2, _, _, _ = simulate(x, y, hs, vs, fuel, rot, power, best_seq)
    best_score = score_state(x, y, hs2, vs2)
    current_seq = best_seq

    for it in range(ITERATIONS):
        t = TEMP_START + (TEMP_END - TEMP_START) * (it / ITERATIONS)
        candidate = mutate(current_seq, t)
        _, _, hs2, vs2, _, _, _ = simulate(
            x, y, hs, vs, fuel, rot, power, candidate
        )
        s = score_state(x, y, hs2, vs2)

        if s > best_score:
            best_score = s
            best_seq = candidate
            current_seq = candidate
        else:
            delta = s - best_score
            prob = math.exp(delta / t) if t > 0 else 0
            if random.random() < prob:
                current_seq = candidate

    drot, dpow = best_seq[0]
    rot = max(-90, min(90, rot + drot))
    power = max(0, min(4, power + dpow))

    print(rot, power)
