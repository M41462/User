#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>

namespace pacman {

// Utility class for score management and file operations.
class Utils {
public:
  Utils();
  ~Utils();

  // Score management
  void eatPellet();      // Increment score for regular pellet
  void eatPowerPellet(); // Increment score for power pellet
  void printScore();     // Print current score to console
  void writeScore();     // Save score to file

private:
  static inline int score = 0;                       // Current game score
  std::string dataFilePath = "assets/data/data.txt"; // Score file path
  std::ofstream dataFile; // File stream for writing score
};

} // namespace pacman

#endif // UTILS_HPP
