---這是測試用專案---
# linux-sysmon

🚀 A lightweight Linux system monitoring CLI tool built with C++.

This tool monitors basic system resource usage such as:

- CPU usage
- Memory usage
- Disk usage (basic)
- Network I/O (planned)

## 🔧 Features

- Display real-time CPU, memory, and disk usage
- Read directly from `/proc` file system
- Color-coded CLI output
- Easy to extend with more metrics

## 🛠️ Build & Run

```bash
git clone https://github.com/<your-username>/linux-sysmon.git
cd linux-sysmon
mkdir build && cd build
cmake ..
make
./linux-sysmon
```
