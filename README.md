# Soundgenerator

Simple platform-independent tone generator built with **Qt 6** (Widgets + Multimedia).
On launch it synthesizes a short melody as signed 16-bit PCM and plays it through the default audio output.

## Requirements

- Qt 6 with the **Widgets** and **Multimedia** modules
- CMake 3.16+ (recommended) or qmake
- A C++17 compiler

## Build with CMake

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x/gcc_64
cmake --build build
./build/Soundgenerator
```

## Build with qmake

```bash
qmake Soundgenerator.pro
make
./Soundgenerator
```

## Usage

The demo window starts playback automatically. The core API lives in `SoundGenerator`:

```cpp
SoundGenerator generator;
generator.appendSound(/* amplitude 0.0–1.0 */ 0.5, /* Hz */ 440, /* ms */ 400);
generator.appendPause(100);
generator.play(); // asynchronous
```

For a one-shot tone without managing an instance:

```cpp
SoundGenerator::playSound(0.5, 440, 400);
```

Keep the `SoundGenerator` alive until playback finishes.
