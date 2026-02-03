# 🔥 Fireplace — Terminal Fire Simulation in ASCII
Fireplace is a lightweight C program that generates an animated ASCII fire in your terminal.

This project was inpired by this article : [How DOOM fire was done](https://fabiensanglard.net/doom_fire_psx/)


### Usage
```bash
fireplace heat_decay direction
```

**heat_decay**: How quickly the heat decays per frame (short). Higher values make the fire burn out faster.

**direction** (optional): The wind direction affecting the flames. Positive values push flames to the right, negative to the left, and 0 for no wind.

Example:
``` bash
fireplace 2 1
```
