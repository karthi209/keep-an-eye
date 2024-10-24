#include <iostream>
#include <fstream>

std::string getCPUInfo() {

    std::string line;
    std::string model;

    std::ifstream procCpuInfo("/proc/cpuinfo");

    while (std::getline (procCpuInfo, line)) {
      if(line.substr(0,10) == "model name"){
        model = line.substr(line.find(":") + 2);
        break;
      }
    }
    procCpuInfo.close();

    return model;
}

int main() {
  std::string cpuInfo = getCPUInfo();
  std::cout << cpuInfo << std::endl;
  return 0;
}