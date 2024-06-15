# Phoenix Graphics Engine

---

OpenGL Testbed

## Prequisites (Ubuntu / Mint)

```bash
sudo apt install libgtk-3-dev
```

## Running (Linux)

To Start in Debug Run:

```bash
./run
```

To run release run:

```bash
./run release
```

to clean output files:

```bash
./run clean
```

to debug with GDB:

```bash
./run gdb
```

> At the current time, the build is unstable at launch - if it crashes on startup, keep running
> the `./run` script.

## Running (Windows)

At the moment, Windows is NOT Supported, though work will be done to support it once I have access to a development machine.

## Known Issues

- Textures Not Appearing inside Viewport on AMD RX590 GPUs - GH-#1

## TO-DO

- [ ] Lua Scripting Integration
- [ ] EnTT Integration
- [ ] Improved Renderer2D API
- [ ] Testing on AMD Graphics Cards
- [ ] Windows Support
- [ ] Vulkan 1.0 Support
