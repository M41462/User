# Ghost Rendering & Animation — Complete Guide

## 1. What is a spritesheet?

Your ghost PNG files are **spritesheets**: one image that contains many smaller pictures inside it.

```
ghost_red_ss.png  →  288 pixels wide × 24 pixels tall
```

This image is 288px wide but only 24px tall. Inside it are **12 frames**, each **24×24 pixels**:

```
| frame 0 | frame 1 | frame 2 | frame 3 | frame 4 | frame 5 | frame 6 | frame 7 | ... | frame 11 |
| 0-23px  | 24-47px | 48-71px | 72-95px |96-119px |120-143px|144-167px|168-191px|     |264-287px |
<----------------------------------------288px----------------------------------------------------->
```

Each frame is a different ghost pose (different direction or animation step).

---

## 2. What does `setTextureRect` do? (Detailed)

```cpp
ghostsShape[i].setTextureRect(
    sf::IntRect(sf::Vector2i(0, 0),    // (left, top) = where to START cropping
                sf::Vector2i(24, 24))  // (width, height) = how big the crop is
);
```

Think of it like a **pair of scissors cutting a photo out of a newspaper**:

- The PNG file `ghost_red_ss.png` is the **full newspaper page** (288×24)
- `sf::IntRect` defines a **rectangle** with 4 values: `left`, `top`, `width`, `height`
- `sf::Vector2i(0, 0)` → start at left=0, top=0 (the very top-left pixel of the image)
- `sf::Vector2i(24, 24)` → cut out a piece that is 24px wide and 24px tall

So the sprite now only shows **pixels from (0,0) to (23,23)** — which is frame 0 — instead of the whole 288px strip.

**Without this line:** SFML draws the entire 288×24 image → you see 12 ghosts in a row (looks broken)

**With this line:** SFML only draws the 24×24 area you specified → you see 1 ghost

To show a **different frame**, change the **X position** (the first number):

| Frame | X position (left) | Code |
|-------|-------------------|------|
| 0     | 0                 | `sf::Vector2i(0, 0)` |
| 1     | 24                | `sf::Vector2i(24, 0)` |
| 2     | 48                | `sf::Vector2i(48, 0)` |
| 3     | 72                | `sf::Vector2i(72, 0)` |
| 4     | 96                | `sf::Vector2i(96, 0)` |
| 5     | 120               | `sf::Vector2i(120, 0)` |
| 6     | 144               | `sf::Vector2i(144, 0)` |
| 7     | 168               | `sf::Vector2i(168, 0)` |
| ...   | ...               | ... |

Formula: `frameIndex × 24` = X position of that frame.

---

## 3. Frame layout (which frame = which direction)

The 12 frames in your spritesheet are ordered like this:

| Frame(s) | Direction | Ghost faces |
|----------|-----------|-------------|
| 0–1      | DOWN      | ↓           |
| 2–3      | LEFT      | ←           |
| 4–5      | RIGHT     | →           |
| 6–7      | UP        | ↑           |
| 8–11     | Reserved  | (eyes, etc) |

Each direction has **2 frames** (frame A and frame B). When you flip between them, the ghost's feet move → walking animation.

```
DOWN:  frame 0 (feet apart) → frame 1 (feet together) → frame 0 → frame 1 ...
LEFT:  frame 2 (feet apart) → frame 3 (feet together) → frame 2 → frame 3 ...
RIGHT: frame 4 (feet apart) → frame 5 (feet together) → frame 4 → frame 5 ...
UP:    frame 6 (feet apart) → frame 7 (feet together) → frame 6 → frame 7 ...
```

The Direction enum values match these pairs:
```cpp
enum class Direction {
    DOWN  = 0,    // uses frames 0-1
    LEFT  = 1,    // uses frames 2-3
    RIGHT = 2,    // uses frames 4-5
    UP    = 3,    // uses frames 6-7
    NONE  = 4     // no movement
};
```

Formula to get the X position of the correct frame:
```
frameX = (directionEnumValue × 2 + animFrame) × 24
```

---

## 4. How animation works (step by step)

Animation is just **rapidly switching which frame you show**.

### Step 1: Add a counter that grows each frame

```cpp
static float animTimer = 0;   // "static" = keeps its value between calls
animTimer += 0.15f;            // increase by 0.15 every time drawGhosts() runs
```

- `0.15f` controls speed. Higher = faster animation
- The timer never stops growing: 0, 0.15, 0.30, 0.45, 0.60, 0.75, 0.90, 1.05, ...

### Step 2: Convert timer to 0 or 1

```cpp
int animFrame = static_cast<int>(animTimer) % 2;
```

- `static_cast<int>(animTimer)` cuts off the decimal: `0.15 → 0`, `0.30 → 0`, `0.60 → 0`, `1.05 → 1`, `1.20 → 1`, `1.50 → 1`, `1.80 → 1`, `2.10 → 2`...
- `% 2` (modulo 2) keeps only 0 or 1: `0→0, 1→1, 2→0, 3→1, 4→0, 5→1...`

Result: `animFrame` flips: 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0...

### Step 3: Pick the right frame for the ghost's direction

```cpp
int dirIndex = static_cast<int>(ghostsDirection[i]);  // 0=DOWN, 1=LEFT, 2=RIGHT, 3=UP
int frameX = (dirIndex * 2 + animFrame) * 24;
```

Examples:
- If direction = LEFT (dirIndex=1) and animFrame=0: `(1×2 + 0) × 24 = 48` → frame 2 (LEFT, feet apart)
- If direction = LEFT (dirIndex=1) and animFrame=1: `(1×2 + 1) × 24 = 72` → frame 3 (LEFT, feet together)

### Step 4: Apply the crop and draw

```cpp
ghostsShape[i].setTextureRect(
    sf::IntRect(sf::Vector2i(frameX, 0), sf::Vector2i(24, 24))
);
window.draw(ghostsShape[i]);
```

`frameX` changes every few frames, so the ghost alternates between foot positions → **walking animation**.

### Visual summary of the animation loop:

```
Frame 1: animTimer=0.15  → animFrame=0 → dir=LEFT → frameX=48  → show frame 2
Frame 2: animTimer=0.30  → animFrame=0 → dir=LEFT → frameX=48  → show frame 2
Frame 3: animTimer=0.45  → animFrame=0 → dir=LEFT → frameX=48  → show frame 2
Frame 4: animTimer=0.60  → animFrame=0 → dir=LEFT → frameX=48  → show frame 2
Frame 5: animTimer=0.75  → animFrame=0 → dir=LEFT → frameX=48  → show frame 2
Frame 6: animTimer=0.90  → animFrame=0 → dir=LEFT → frameX=48  → show frame 2
Frame 7: animTimer=1.05  → animFrame=1 → dir=LEFT → frameX=72  → show frame 3
Frame 8: animTimer=1.20  → animFrame=1 → dir=LEFT → frameX=72  → show frame 3
...
```

---

## 5. What you did right & what you missed

### ✅ What you did right:
- Added `ghostsDirection[i] = Direction::NONE;` — stops unwanted movement
- Added `Direction ghostsDirection[MAX_GHOSTS] = {};` — zero-initializes the array
- Added `Direction::NONE` to the enum — gives a safe default
- Added the `case Direction::NONE: break;` in movement — handles the NONE case
- Added `setTextureRect` — crops the spritesheet to show 1 frame

### ❌ What you missed / should know:

**1. `static` vs non-`static` for the timer**
If you put `animTimer` inside `drawGhosts()` as a **non-static local variable**, it resets to 0 every time the function runs → no animation, ghost is stuck on frame 0.
If you make it `static`, it keeps its value between calls → timer grows → animation works.

**2. The ghost shows frame 0 (DOWN face)**
`setTextureRect(sf::Vector2i(0,0), ...)` picks frame 0 which is a DOWN-facing ghost. To make it face UP, change the X to `144` (frame 6).

**3. Display vs movement are separate**
- `setTextureRect` only changes what the ghost **looks like**
- `ghostsDirection` controls which way the ghost **moves**
- They don't have to match! You can show an UP-facing ghost that moves LEFT, etc.

**4. The `_ss` in filenames means "spritesheet"**
It's your reminder that each PNG contains multiple frames, not just one image.

---

## 6. Complete animation code (copy-paste ready)

### In `src/Ghost.cpp`:

#### initGhosts() — load texture, crop to one frame, set direction

```cpp
void Ghost::initGhosts() {
  for (int i = 0; i < MAX_GHOSTS; i++) {
    if (!ghostsTexture[i].loadFromFile(ghostsTexturePath[i])) {
      throw std::runtime_error("Error Init ghosts texture");
    }
    ghostsShape[i].setTexture(ghostsTexture[i]);
    ghostsShape[i].setTextureRect(
        sf::IntRect(sf::Vector2i(0, 0),
                    sf::Vector2i(24, 24)));           // crop to frame 0
    ghostsShape[i].setPosition(ghostsPosition[i]);
    ghostsDirection[i] = Direction::NONE;              // don't move at start
  }
}
```

#### drawGhosts() — animate by direction

```cpp
void Ghost::drawGhosts(sf::RenderWindow &window) {
  static float animTimer = 0;       // keeps growing between calls
  animTimer += 0.15f;               // animation speed
  int animFrame = static_cast<int>(animTimer) % 2;  // toggles 0,1,0,1...

  for (int i = 0; i < MAX_GHOSTS; i++) {
    ghostsShape[i].setPosition(ghostsPosition[i]);

    // Pick frame based on direction + animation
    int dirIndex = static_cast<int>(ghostsDirection[i]);
    if (dirIndex >= 0 && dirIndex <= 3) {  // only animate valid directions
      int frameX = (dirIndex * 2 + animFrame) * 24;
      ghostsShape[i].setTextureRect(
          sf::IntRect(sf::Vector2i(frameX, 0),
                      sf::Vector2i(24, 24)));
    }

    window.draw(ghostsShape[i]);   // <-- THIS draws the ghost on screen
  }
}
```

### In `include/Ghost.hpp` — add the frame size constant

Add this line in the `private:` section (next to `GHOST_SPEED`):

```cpp
static constexpr int GHOST_FRAME_SIZE = 24;
```

---

## 7. Common frame X values quick reference

| Direction | Frame A (feet apart) | Frame B (feet together) |
|-----------|---------------------|------------------------|
| DOWN      | X = 0               | X = 24                 |
| LEFT      | X = 48              | X = 72                 |
| RIGHT     | X = 96              | X = 120                |
| UP        | X = 144             | X = 168                |
| Reserved  | X = 192, 216, 240, 264 |                      |

Formula: `X = (directionEnumValue × 2 + animFrame) × 24`

---

## Summary

| Concept | What it means |
|---------|--------------|
| Spritesheet | One PNG containing many 24×24 frames in a row |
| `setTextureRect` | Scissors that crop the PNG to show only 1 frame |
| frameX | X pixel position of the frame you want to show (`frameIndex × 24`) |
| `animTimer` | Counter that grows each frame |
| `animTimer % 2` | Converts growing timer into 0/1 toggle |
| `dirIndex × 2 + animFrame` | Picks the right pair of frames for the direction, then alternates |
| `window.draw(sprite)` | The actual command that puts pixels on your screen |
