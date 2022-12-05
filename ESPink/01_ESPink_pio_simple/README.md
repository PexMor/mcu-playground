# ESPink under patform.io

Simple build without IDE (GUI), reduced example.

## Install PlaformIO

```bash
conda create -n cpio python=3.10
conda activate cpio
pip install platformio
```

## Build the example

```bash
pio device list
pio boards esp32dev

# search for library
pio pkg search "header/GxEPD2.h"

# verbose
pio run -vv

# if not matchin platformio.ini
# pio run --upload-port /dev/ttyUSB0 -t upload
pio run -t upload

# if not matchin platformio.ini
# pio device monitor -p /dev/ttyUSB0 -b 115200
pio device monitor
```

