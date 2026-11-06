# LVGL Linux Project

A ready-to-build Linux application for [LVGL](https://github.com/lvgl/lvgl)
and the [LVGL Editor](https://lvgl.io/pro). The primary target is embedded
Linux, it ships DRM/KMS and framebuffer backends for bare-metal boards but
it also runs on desktop Linux via SDL2, Wayland, or X11, so you can develop
and iterate without hardware. LVGL itself is downloaded automatically by CMake;
dependencies are resolved automatically based on the configuration you choose,
CMake first tries `find_package`, then `pkg-config`, and finally fetches and
builds the library from source for those that support it. Kernel-coupled
libraries like libdrm must be installed on the system (or present in your
sysroot when cross-compiling) and are not fetched automatically. Export your UI
from the LVGL Editor into the `ui/` folder and it is picked up automatically.

> **Windows / macOS:** cross-compilation from a Linux host (or WSL2 on
> Windows) is the recommended path for embedded targets. Native Windows and
> macOS builds are not officially supported at this time; the
> LVGL Simulator for VSCode is a better starting point if you only need a desktop preview.

## Requirements

- **CMake** ≥ 3.18
- **Python 3** — used by LVGL to generate `lv_conf.h` from `lv_conf.defaults`
- A **C/C++ compiler** (GCC or Clang)
- Any system libraries required by the backends you enable (see below)

On first configure, CMake fetches LVGL and any enabled optional libraries
automatically via `FetchContent`. No manual cloning is needed.

## System dependencies

CMake, Python 3, and python3-venv are required regardless of configuration.
Ninja is optional but recommended to speed-up building

Install all system dependencies in one go:

```bash
# Debian / Ubuntu
sudo apt install \
  build-essential cmake python3 python3-venv ninja-build \
  libsdl2-dev \
  libwayland-dev libxkbcommon-dev wayland-protocols \
  libx11-dev \
  libdrm-dev libgbm-dev \
  libevdev-dev \
  libwebp-dev \
  libegl-dev libgles-dev libgl-dev
```

```bash
# Arch
sudo pacman -S \
    git cmake python ninja \
    sdl2 \
    wayland wayland-protocols libxkbcommon \
    libx11 \
    libdrm \
    libevdev \
    libwebp \
    mesa
```

```bash
# Fedora
sudo dnf install \
  @development-tools gcc-c++ cmake python3 python3-devel ninja-build \
  SDL2-devel \
  wayland-devel wayland-protocols-devel libxkbcommon-devel \
  libX11-devel \
  libdrm-devel \
  libevdev-devel \
  libwebp-devel \
  mesa-libEGL-devel mesa-libGLES-devel mesa-libGL-devel mesa-libgbm-devel
```

Libraries that can be fetched from source (FreeType, libpng, libjpeg-turbo, ...) are built automatically by CMake if not found on the system.

FFmpeg and GStreamer must be installed manually if you enable them:

```bash
# Debian / Ubuntu
sudo apt install libavcodec-dev libavformat-dev libavutil-dev libswscale-dev
sudo apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
# Arch
sudo pacman -S ffmpeg gstreamer gst-plugins-base
# Fedora
sudo dnf install ffmpeg-devel gstreamer1-devel gstreamer1-plugins-base-devel
```

## Configuration

LVGL is configured through `lv_conf.defaults` in the project root. CMake
merges this file with LVGL's `lv_conf_template.h` at configure time to produce
`build/lv_conf.h`. Only options that differ from LVGL's defaults need to be
listed; everything else is inherited automatically.

Commonly changed options:

| Option                                 | Default | Description                            |
| -------------------------------------- | ------- | -------------------------------------- |
| `LV_USE_SDL`                           | `1`     | SDL2 backend                           |
| `LV_USE_WAYLAND`                       | `1`     | Wayland backend                        |
| `LV_USE_X11`                           | `1`     | X11 backend                            |
| `LV_USE_LINUX_DRM`                     | `1`     | DRM/KMS backend                        |
| `LV_USE_LINUX_FBDEV`                   | `1`     | Framebuffer backend                    |
| `LV_USE_EVDEV`                         | `1`     | evdev input (needed for DRM and fbdev) |
| `LV_USE_FREETYPE`                      | `1`     | Runtime TTF/OTF font loading           |
| `LV_USE_LIBPNG`                        | `1`     | PNG decoding                           |
| `LV_USE_LIBJPEG_TURBO`                 | `1`     | JPEG decoding                          |
| `LV_USE_FFMPEG`                        | `0`     | Video playback via FFmpeg              |
| `LV_USE_GSTREAMER`                     | `0`     | Video playback via GStreamer           |
| `LV_USE_OPENGLES`                      | `1`     | OpenGL ES display driver               |
| `LV_USE_NANOVG` / `LV_USE_DRAW_NANOVG` | `0`     | GPU vector draw backend                |
| `LV_USE_GLTF` / `LV_USE_3DTEXTURE`     | `0`     | 3D model and texture support           |

**Backend selection at runtime:** all enabled backends are compiled in and
tried in order at startup until one initialises successfully:
SDL → Wayland → X11 → DRM → fbdev. It is safe to leave all backends enabled;
the right one is picked automatically.

**3D support** requires `LV_USE_OPENGLES`, `LV_USE_NANOVG`, and
`LV_USE_DRAW_NANOVG`. Only the SDL, Wayland, and DRM backends support OpenGL
ES, disable X11 and fbdev when targeting 3D. Wayland also needs
`LV_WAYLAND_USE_EGL 1`.

CMake cache variables (pass with `-D` on the command line):

| Variable            | Default  | Description                         |
| ------------------- | -------- | ----------------------------------- |
| `LV_HOR_RES`        | `800`    | Display horizontal resolution       |
| `LV_VER_RES`        | `480`    | Display vertical resolution         |
| `UI_DIR`            | `ui`     | Path to the exported LVGL Editor UI |
| `UI_PROJECT_NAME`   | _(auto)_ | Override the UI init function name  |
| `UI_DEFAULT_SCREEN` | _(auto)_ | Override the default screen to load |

## How to build

### Native build

```bash
cmake -B build -GNinja
cmake --build build
./build/lvgl_linux
```

Pass resolution or other options at configure time:

```bash
cmake -B build -DLV_HOR_RES=1280 -DLV_VER_RES=800
cmake --build build -j$(nproc)
```

Run the binary from the **project root** so that the `A:ui` asset path
resolves to the `ui/` folder.

### Cross-compilation

Cross-compilation requires a CMake toolchain file that sets the target
compiler, sysroot, and architecture. A minimal example for an ARMv7 target:

```cmake
# toolchain-armv7.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER   arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

set(CMAKE_SYSROOT /opt/sysroots/armv7)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

Then configure with:

```bash
cmake -B build-arm -GNinja \
  -DCMAKE_TOOLCHAIN_FILE=toolchain-armv7.cmake \
  -DLV_HOR_RES=480 -DLV_VER_RES=272
cmake --build build-arm
```

The resulting binary can be copied to the target device directly.
Dependencies that are fetched by CMake (LVGL, FreeType, etc.) are compiled for
the target architecture automatically. System libraries (libdrm, libwayland,
...) must be present in the sysroot.

For Yocto and Buildroot environments a toolchain file is typically generated by
the SDK (`environment-setup-*` for Yocto, `output/host/usr/share/buildroot/toolchainfile.cmake`
for Buildroot) and can be passed directly to CMake.

## Using your LVGL Editor UI

Export C code from the LVGL Editor into the [`ui/`](ui/) folder. The build
system detects it automatically and links it into the application.
`main.c` calls the UI's init function and loads the default screen. You can
override both at configure time:

```bash
cmake -B build -DUI_PROJECT_NAME=my_project -DUI_DEFAULT_SCREEN=main_screen
```

See the LVGL documentation on
[using exported C code](https://lvgl.io/docs/pro/integration/using-exported-c-code).

## Support

- LVGL Open documentation: [https://lvgl.io/docs/open](https://lvgl.io/docs/open)
- LVGL Pro documentation: [https://lvgl.io/docs/pro](https://lvgl.io/docs/pro)
- LVGL forum: [https://forum.lvgl.io](https://forum.lvgl.io)
- Report issues for this template: [https://github.com/lvgl/lvgl_editor/issues](https://github.com/lvgl/lvgl_editor/issues)
- Report issues for LVGL: [https://github.com/lvgl/lvgl/issues](https://github.com/lvgl/lvgl/issues)
