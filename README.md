## Customizable Gauge

A small Qt-based gauge widget that lets you control the gauge shape, colors, zones, and labels programmatically.
The current implementation provides a radial gauge.

![Example Gauge Implementation](image.png)

### Features

- Configurable gauge appearance (shape, color, zones, labels).
- Radial gauge implementation with an example screenshot.

### Development

#### Prerequisites

- CMake
- A C++ compiler
- Qt (Qt 5 or Qt 6)

#### Build

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

### Contribution

Contributions are welcome. If you plan a larger change, please open an issue or start a discussion first.

#### Guidelines

- Keep changes focused and add/update documentation when behavior changes.
- Follow the existing code style and keep the build passing.
- Include examples or screenshots when modifying visuals.
