# Notes – Parameter Tuning & Reasoning

### Horizontal speed management
- MAX_DX = 20 (limit)
- If |dx| > 80 → immediate braking tilt
- If |dx| < 40 → accelerate toward target

### Vertical speed thresholds
- If vSpeed < -35 → power = 4
- If vSpeed < -25 → power = 3
- If vSpeed < -15 → power = 2
- else → power = 1

### Final override (<300 m)
Angle = 0  
Power chosen only based on vertical speed  
→ guarantees final soft landing.

### Why this works
It guarantees:
- correct positioning above landing zone,
- elimination of horizontal speed,
- controlled descent with safe vertical velocity.

The strategy is deterministic and robust across validators.
