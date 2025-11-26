# Mars Lander -- Simulated Annealing Controller

This repository contains my solution for the **Optimization Problems 2**
homework: implementing a search-based controller (Hill Climbing,
Simulated Annealing, GA, etc.) for a CodinGame game and reaching the top
10--20% of the leaderboard.

I chose **Mars Lander (Episode 2)** and implemented a **Simulated
Annealing (SA)** controller in Python.

------------------------------------------------------------------------

## Idea

On each game turn the bot:

1.  Reads the current state of the lander (position, speed, fuel,
    rotation, power).
2.  Simulates a **sequence of future moves** (rotation and thrust
    changes).
3.  Uses an **estimation function** (score) to evaluate how good the
    final state is:
    -   distance to landing zone
    -   horizontal and vertical speed
    -   penalty for crashing
4.  Uses **Simulated Annealing** to:
    -   start from a random sequence of moves,
    -   repeatedly apply random mutations,
    -   accept better sequences and sometimes worse ones (depending on
        temperature),
    -   slowly reduce the temperature to focus on exploitation.
5.  Outputs **only the first command** from the best sequence for the
    current turn.

This process is repeated every frame.

------------------------------------------------------------------------

## Algorithm details

### State & Moves

A solution (candidate) is a sequence of moves:

-   each move = `(Δrotation, Δpower)`
-   `Δrotation ∈ {-15, 0, 15}` (degrees per step)
-   `Δpower ∈ {-1, 0, 1}` (change of thrust level)

The physics follow the rules from the Mars Lander statement:

-   gravity `g = 3.711`
-   rotation range: `[-90, 90]`
-   power range: `[0, 4]`

### Estimation (Score Function)

The score tries to:

-   keep the lander above the landing zone,
-   minimize horizontal distance from the landing platform,
-   minimize horizontal and vertical speed,
-   heavily penalize obvious crashes.

Formally, the score is (negative penalties):

``` text
score = - 3 * distance_to_landing_zone
        - 4 * |horizontal_speed|
        - 6 * |vertical_speed|
        - big_penalty_if_below_platform
```

Higher score = better trajectory.

### Simulated Annealing

For each turn:

1.  Start from the best sequence from the previous turn (or a random
    one).
2.  For a fixed number of iterations:
    -   mutate a copy of the current sequence (several random moves
        changed),
    -   simulate the lander using this sequence,
    -   compute the score,
    -   accept or reject using SA rule:

``` text
if new_score > current_score:
    accept
else:
    accept with probability exp((new_score - current_score) / T)
```

3.  Temperature `T` is decreased linearly between `TEMP_START` and
    `TEMP_END`.

The final best sequence is remembered and its first move is used as
output.

------------------------------------------------------------------------

## Files

-   `main.py` -- the CodinGame-compatible solution
-   `notes.md` -- parameter tuning notes and short reflections
-   `.gitignore` -- basic Python ignores

------------------------------------------------------------------------

## AI tools usage (short)

I used AI **only for small clarifications** while working on the
assignment: - to discuss reasonable ranges for SA parameters
(temperature, iterations), - to get ideas for mutation design and
scoring components.

I then implemented, tested and tuned the final solution myself based
on: - the lecture slides ("Optimization Problems 2"), - the official
Mars Lander problem statement on CodinGame, - trial-and-error in the
CodinGame IDE.
