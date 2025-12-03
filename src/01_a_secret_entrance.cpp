#include <fstream>
#include <iostream>
#include <string>

// Day 1: Secret Entrance
class Solution {
private:
  int curr_arrow;
  int soln;

  const int parse_cmd(const std::string &str) const {
    return ((str[0] == 'L') ? -1 : 1) *
           std::stoi(str.substr(1));
  }

  void process_cmd(const int cmd) {
      curr_arrow += cmd;
      curr_arrow %= 100;
      if (curr_arrow < 0) {
        curr_arrow += 100;
      }

      soln += (curr_arrow == 0) ? 1 : 0;
  }

  void run(const std::string &datapath) {
    std::ifstream infile(datapath);

    std::string line;
    while (std::getline(infile, line)) {
      const int cmd = parse_cmd(line);
      process_cmd(cmd);
    }
    std::cout << "Solution: " << soln << "\n";
  }



public:
  Solution(const std::string &datapath) : curr_arrow(50), soln(0) {
    run(datapath);
  }
};

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Please provide an input file path" << std::endl;
    return 1;
  }
  const std::string datapath(argv[1]);
  const Solution s = Solution(datapath);
  return 0;
}
