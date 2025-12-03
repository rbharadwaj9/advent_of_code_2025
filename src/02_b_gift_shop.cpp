#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <utility>

class Solution {
private:
  const std::string datapath;
  long answer;

  void find_ids(const long low, const long high) {
    assert(low >= 0);
    assert (low <= high);
    static const std::regex pattern(R"(^(\d+)\1+\b$)");
    for (long curr = low; curr <= high; ++curr) {
      const std::string curr_s = std::to_string(curr);
      if (std::regex_match(curr_s.data(), pattern)) {
        answer += curr;
      }
    }
  }

  std::pair<long, long> parse_phrase(const std::string &phrase) const {
    std::istringstream iss(phrase);
    std::string num_str;
    std::getline(iss, num_str, '-');
    assert(!num_str.empty());
    long low = std::stol(num_str);

    std::getline(iss, num_str, '-');
    assert(!num_str.empty());
    long high = std::stol(num_str);

    return {low, high};
  }

  void parse_text() {
    std::ifstream fs(datapath);
    std::string line;
    while (std::getline(fs, line)) {

      std::istringstream iss(line);

      std::string curr_phrase;
      while (std::getline(iss, curr_phrase, ',')) {
        auto [low, high] = parse_phrase(curr_phrase);
        find_ids(low, high);
      }
    }

    std::cout << "Answer: " << answer << "\n";
  }

public:
  Solution(const std::string &datapath_i) : datapath(datapath_i), answer(0) {
    parse_text();
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
