

## 2026-10-18

- Added `tools/disk-space.cpp`, a standalone Linux helper that reports root filesystem capacity and warns at 90% usage.
# Historial de cambios

Entradas originales conservadas en inglés. Las fechas corresponden al historial existente; la última entrada no tenía fecha registrada.

### 2026-10-09

- Added the machine hostname to the monitor header.

### 2026-10-08

- Added root filesystem disk usage to the live system summary.

### 2026-10-07

- Each monitor refresh now prints a local timestamp so continuous logs are easier to read.

### 2026-10-06

- Added `--no-clear` to keep previous readings visible when running continuously.

### 2026-10-05

- Added the 1, 5 and 15 minute Linux load averages from `/proc/loadavg`.

### 2026-10-04

- Added swap memory usage and its percentage to the terminal monitor.

### Actualización anterior (sin fecha registrada)

- Memory output now shows the percentage of RAM currently in use.
