# Mars Lander – Tuning Notes

## Parameters

- SEQ_LEN = 60
  - Shorter sequences (20–30) were sometimes too myopic.
  - Longer sequences (>80) were slower and did not noticeably improve results.

- TEMP_START = 120.0, TEMP_END = 0.1
  - Higher starting temperature -> more exploratory mutations.
  - Lower end temperature -> stable behavior near the end of each turn.

- ITERATIONS = 2500
  - Tested 1500, 2000, 2500.
  - 2500 was still okay within CodinGame time limits and gave slightly better stability.

## Mutations

- Mutate `count = 1 + T/20` moves.
- Each mutation:
  - Δrotation in {-15, 0, 15}
  - Δpower in {-1, 0, 1}

More aggressive mutations at high T helped escape bad local patterns early.

## Scoring

Score components:

- Horizontal distance to landing zone (×3)
- |horizontal_speed| (×4)
- |vertical_speed| (×6)
- strong crash penalty when below platform

I tried smaller speed penalties first, but the lander often hit the ground too fast.
Increasing vertical speed penalty improved landing stability.
