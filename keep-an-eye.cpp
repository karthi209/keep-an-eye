#include <iostream>
#include <fstream>
#include <tuple>
#include <string>

std::tuple<int, int, int, int, int, int, int> getMemStat() {

    std::string line;
    int totalmem;
    int freemem;
    int availmem;
    int buffermem;
    int cachemem;
    int swapTotalMem;
    int swapFreeMem;

    std::ifstream procMemStat("/proc/meminfo");

    if (!procMemStat) {
      std::cout << "Failed to read file" << std::endl;
      return std::make_tuple(0, 0, 0, 0, 0, 0, 0);
    }

    while (std::getline (procMemStat, line)) {
      if(line.substr(0,8) == "MemTotal"){
        totalmem = std::stoi(line.substr(line.find(":") + 2));
      } else if (line.substr(0,7) == "MemFree") {
          freemem = std::stoi(line.substr(line.find(":") + 2));
      } else if (line.substr(0,12) == "MemAvailable") {
          availmem = std::stoi(line.substr(line.find(":") + 2));
      } else if (line.substr(0,7) == "Buffers") {
          buffermem = std::stoi(line.substr(line.find(":") + 2));
      } else if (line.substr(0,6) == "Cached") {
          cachemem = std::stoi(line.substr(line.find(":") + 2));
      } else if (line.substr(0,9) == "SwapTotal") {
          swapTotalMem = std::stoi(line.substr(line.find(":") + 2));
      } else if (line.substr(0,9) == "SwapFree") {
          swapFreeMem = std::stoi(line.substr(line.find(":") + 2));
      }
    }
    procMemStat.close();

    return std::make_tuple(totalmem/1000, freemem/1000, availmem/1000, buffermem/1000, cachemem/1000, swapTotalMem/1000, swapFreeMem/1000);

}

int main() {
  std::tuple <int, int, int, int, int, int, int> memInfo = getMemStat();

  std::cout << "Total Memory: " << std::get<0>(memInfo) << "MB" << std::endl;
  std::cout << "Free Memory: " << std::get<1>(memInfo) << "MB" <<  std::endl;
  std::cout << "Available Memory: " << std::get<2>(memInfo) << "MB" <<  std::endl;
  std::cout << "Buffer: " << std::get<3>(memInfo) << "MB" <<  std::endl;
  std::cout << "Cached: " << std::get<4>(memInfo) << "MB" <<  std::endl;
  std::cout << "Total Swap: " << std::get<5>(memInfo) << "MB" <<  std::endl;
  std::cout << "Free Swap: " << std::get<6>(memInfo) << "MB" <<  std::endl;
  
  return 0;
}