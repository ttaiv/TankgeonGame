# Levels

This folder contains levels of the game as text files.
Level files contain exactly 9 rows and 32 columns, outer bounds being `#` chars. 

## Character Meanings

Each character in the level files represents a different element of the game:

- `#`: Outer bounds (walls) of the level
- ` `: Empty space where the player can move
- `P`: The player's starting position
- `r`: Red sniper tank start position
- `b`: Blue stationary tank position
- `s`: shield
- `c`: yellow burst tank
- `w`: wall
- `h`: hole (implemented with spike class)
