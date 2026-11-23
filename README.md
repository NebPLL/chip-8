# CHIP-8 Emulator

A CHIP-8 interpreter written in C11, using [raylib](https://www.raylib.com/) for graphics, input and sound.

<!-- Add a screenshot or GIF here, e.g. ![Brix](docs/brix.gif) -->

## Features

- All standard CHIP-8 instructions (except the legacy `0NNN` SYS call)
- Loads `.ch8` ROM files from the command line
- Adjustable speed (instructions per frame)
- 64×32 display, scaled 10× and rendered at 60 FPS
- Delay and sound timers at 60 Hz, with an audible beep
- Built-in disassembler (opcode → mnemonics like `DRW V0, V1, 4`)
- Live terminal debug view showing PC, I, the current instruction, timers, registers, stack and key states

## Building

Requirements: a C compiler, `make`, `pkg-config` and raylib.

```sh
make          # builds and runs the IBM logo ROM
make clean    # removes the build directory
```

## Usage

```sh
./build/main <rom.ch8> <instructions-per-frame>
./build/main resources/Brix.ch8 11
```

Or through `make`:

```sh
make run ROM=resources/Breakout.ch8 SPEED=15
```

The instructions per frame (1–1000) control the emulation speed. Around 11 (~660 Hz) works well for most games. Run the emulator from the project root so it can find `resources/beep.wav`. A few sample ROMs are included in `resources/`.

## Controls

The original 16-key hex keypad is mapped to the left side of a QWERTY keyboard:

```
CHIP-8        Keyboard
1 2 3 C       1 2 3 4
4 5 6 D   →   Q W E R
7 8 9 E       A S D F
A 0 B F       Z X C V
```

## Implementation notes

- Each instruction lives in its own function (`instructions.c`), dispatched from a switch in `chip8.c`
- Quirks follow modern SUPER-CHIP behavior: `8XY6`/`8XYE` shift VX in place, `BNNN` jumps to NNN + VX, `FX55`/`FX65` leave I unchanged
