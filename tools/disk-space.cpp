#include <sys/statvfs.h>
#include <iomanip>
#include <iostream>

int main() {
    struct statvfs info {};
    if (statvfs("/", &info) != 0) {
        std::cerr << "Could not read filesystem information for /.\n";
        return 1;
    }
    const double total = static_cast<double>(info.f_blocks) * info.f_frsize;
    const double available = static_cast<double>(info.f_bavail) * info.f_frsize;
    const double used = total - available;
    const double percent = total > 0 ? (used / total) * 100.0 : 0.0;
    std::cout << std::fixed << std::setprecision(1)
              << "Root filesystem (/):\n"
              << "  Total: " << total / (1024.0 * 1024 * 1024) << " GiB\n"
              << "  Available to user: " << available / (1024.0 * 1024 * 1024) << " GiB\n"
              << "  Used: " << percent << "%\n";
    if (percent >= 90.0) std::cout << "  Warning: filesystem usage is at least 90%.\n";
    return 0;
}
