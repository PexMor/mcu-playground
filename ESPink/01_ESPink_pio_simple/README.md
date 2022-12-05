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
pio pkg search "header/GxEPD2.h"
pio run -vv
pio run --upload-port /dev/ttyUSB0
pio device monitor -p /dev/ttyUSB0 -b 115200
```

