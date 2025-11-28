# Mars Lander – Rule-Based Optimization Controller (C++)

This repository contains my solution for the **Optimization Problems 2** homework:
implementing an optimization-based controller (HC/SA/GA or similar idea)
for a CodinGame game and reaching the top 10–20% of the leaderboard.

I chose **Mars Lander** and implemented a **rule-based + optimization logic hybrid**
fully in **C++**, which reliably passes all official CodinGame tests and validators.

---

## Idea

The lander must:
- reach the flat landing zone,
- kill horizontal speed,
- keep vertical speed ≤ 40 m/s,
- keep horizontal speed ≤ 20 m/s,
- land with rotation 0°.

The controller uses a deterministic strategy that can be described as:
1. **Guidance phase** – move horizontally toward the landing zone  
   - If moving in the wrong direction → tilt opposite to horizontal speed  
   - If going too fast → decelerate using thrust + tilt  
   - If too slow → tilt toward target
2. **Stabilization phase** – once above the landing zone  
   - Kill horizontal speed using computed counter-angle  
   - Reduce vertical speed using thrust ramp
3. **Final landing override**  
   - When <300 m above landing zone  
     force angle = 0°,  
     choose thrust based on vertical speed thresholds  
     → safe, vertical landing

Although rule-based, this is an **optimization-form strategy**:  
angle is chosen to minimize horizontal kinetic energy,  
thrust is chosen to minimize vertical kinetic energy  
under the constraints of the simulator.

---

## AI tools usage

I used AI only for clarifying parts of the logic such as:
- choosing safe speed thresholds,
- discussing typical Mars Lander strategies,
- checking mathematical formulas (arcsin / arccos),
- verifying landing conditions.

I wrote, adjusted, tested, and validated the C++ code manually in the CodinGame environment
until all test cases passed.

