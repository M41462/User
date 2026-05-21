#ifndef UTILS_HPP
#define UTILS_HPP
#include <fstream>
namespace pacman {
class Utils {
public:
  Utils();
  ~Utils();
  void eatPellet();
  void eatPowerPellet();
  void printScore();
  void writeScore(); 
  
private:
    static inline int score = 0;
    std::string dataFilePath = "assets/data/data.txt"; 
    std::ofstream dataFile; 


};
} // namespace pacman

#endif // UTILS_HPP
