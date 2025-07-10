# cpp-sys-monitor

🚀 A lightweight Linux system monitoring CLI tool built with C++.

This tool monitors basic system resource usage such as:

- CPU usage
- Memory usage
- Disk usage (basic)
- Network I/O (planned)

## 🔧 Features

- Display real-time CPU and memory usage
- Read directly from `/proc` file system
- Color-coded CLI output
- Easy to extend with more metrics

## 🛠️ Build & Run

```bash
git clone https://github.com/<your-username>/cpp-sys-monitor.git
cd cpp-sys-monitor
mkdir build && cd build
cmake ..
make
./cpp-sys-monitor


####
