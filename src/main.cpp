#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

struct CpuSample { long long idle{}, total{}; };

CpuSample cpuSample() {
    std::ifstream f("/proc/stat");
    std::string cpu; long long user,nice,system,idle,iowait,irq,softirq,steal;
    f >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    return {idle + iowait, user + nice + system + idle + iowait + irq + softirq + steal};
}

double cpuUsage() {
    auto a = cpuSample();
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    auto b = cpuSample();
    auto total = b.total - a.total, idle = b.idle - a.idle;
    return total ? 100.0 * (total - idle) / total : 0.0;
}

void memory(double& usedGb, double& totalGb) {
    std::ifstream f("/proc/meminfo");
    std::string key, unit; long long value, total=0, available=0;
    while (f >> key >> value >> unit) {
        if (key == "MemTotal:") total = value;
        if (key == "MemAvailable:") available = value;
    }
    totalGb = total / 1048576.0; usedGb = (total - available) / 1048576.0;
}

double uptimeHours() { std::ifstream f("/proc/uptime"); double s=0; f >> s; return s/3600.0; }

int processCount() {
    int count=0;
    for (auto const& e : std::filesystem::directory_iterator("/proc")) {
        if (!e.is_directory()) continue;
        auto n=e.path().filename().string();
        if (!n.empty() && n.find_first_not_of("0123456789")==std::string::npos) ++count;
    }
    return count;
}

void render() {
    double used,total; memory(used,total);
    std::cout << "\033[2J\033[H";
    std::cout << "C++ System Monitor\n==================\n";
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "CPU:       " << cpuUsage() << "%\n";
    double memoryPercent = total > 0 ? (used / total) * 100.0 : 0.0;
    std::cout << "Memory:    " << used << " / " << total << " GB (" << memoryPercent << "%)\n";
    std::cout << "Uptime:    " << uptimeHours() << " hours\n";
    std::cout << "Processes: " << processCount() << "\n";
}

int main(int argc, char** argv) {
    bool once=false; int interval=1;
    for(int i=1;i<argc;i++){ std::string a=argv[i]; if(a=="--once") once=true; else if(a=="--interval"&&i+1<argc) interval=std::max(1,std::stoi(argv[++i])); }
    do { render(); if(!once) std::this_thread::sleep_for(std::chrono::seconds(interval)); } while(!once);
}
