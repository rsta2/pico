Pico
====

> Raspberry Pi is a trademark of the Raspberry Pi Foundation.

Overview
--------

Some small programs for the Raspberry Pi Pico.

Programs
--------

| Directory        | Description                                              |
|------------------|----------------------------------------------------------|
| spi_slave_pio/   | SPI slave, which is compatible with the Raspberry Pi 0-4 |

Building
--------

```
export PICO_SDK_PATH=/absolute/path/to/pico-sdk
mkdir build
cd build
cmake ..
make
```
