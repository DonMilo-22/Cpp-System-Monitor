# 🖥️ C++ System Monitor

> Lightweight Linux system monitor written in modern C++.

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.16%2B-064F8C?logo=cmake)
![License](https://img.shields.io/badge/license-MIT-green)

A compact terminal utility that reads Linux system information directly from `/proc` and displays CPU load, memory usage, uptime and process count.

## ✨ Features

- CPU usage sampling
- RAM usage and totals
- System uptime
- Running process count
- Refresh loop with configurable interval
- No third-party runtime dependencies

## 🚀 Build

```bash
cmake -S . -B build
cmake --build build
./build/system-monitor
```

Run once:

```bash
./build/system-monitor --once
```

Custom refresh interval:

```bash
./build/system-monitor --interval 2
```

## 🧠 How it works

The program reads Linux virtual files such as `/proc/stat`, `/proc/meminfo` and `/proc/uptime`. CPU usage is calculated from two samples instead of relying on an external library.

## 🛠️ Requirements

- Linux
- C++17 compiler
- CMake 3.16+

> Windows and macOS expose system metrics differently, so this implementation intentionally targets Linux.

## 📄 License

MIT.
