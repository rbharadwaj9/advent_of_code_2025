#include <cstdlib>
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
           std::stoi(str.substr(1, std::string::npos));
  }

  void process_cmd(const int &cmd) {
    // Edge case where if we start at 0 and go negative, it's not a
    // "zero-crossing". Hence ignore
    bool left_from_zero_ignore = (curr_arrow == 0) ? true : false;
    curr_arrow += cmd;

    if (curr_arrow <= 0) {
      soln += abs((curr_arrow / 100)) + ((left_from_zero_ignore) ? 0 : 1);
      curr_arrow %= 100;
      curr_arrow += (curr_arrow < 0) ? 100 : 0;
    } else {
      soln += (curr_arrow / 100);
      curr_arrow %= 100;
    }
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

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Please provide an input file path" << std::endl;
    return 1;
  }
  const std::string datapath(argv[1]);
  const Solution s = Solution(datapath);
  return 0;
}
