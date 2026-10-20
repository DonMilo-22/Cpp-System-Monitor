#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream file("/proc/meminfo");
    if (!file) {
        std::cerr << "Cannot read /proc/meminfo. This helper requires Linux.\n";
        return 1;
    }
    long long total = 0, available = 0;
    std::string key, unit;
    long long value;
    while (file >> key >> value >> unit) {
        if (key == "MemTotal:") total = value;
        else if (key == "MemAvailable:") available = value;
    }
    if (total <= 0 || available < 0) {
        std::cerr << "Memory information was incomplete.\n";
        return 1;
    }
    const double used = 100.0 * (total - available) / total;
    std::cout << "RAM total: " << total / 1024 << " MiB\n"
              << "RAM available: " << available / 1024 << " MiB\n"
              << "RAM usage: " << used << "%\n";
    if (used >= 90.0) std::cout << "Warning: RAM usage is at least 90%.\n";
}
