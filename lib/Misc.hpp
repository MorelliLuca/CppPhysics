#ifndef MISC_HPP
#define MISC_HPP

#include <iomanip>
#include <iostream>

namespace Misc
    // Progress Bar
    void
    progressBar(double status, double max) {
  std::cout << "\033[34m" << std::fixed << std::setprecision(0)
            << status / max * 100 << "%\033[0m|";
  for (double i{0}; i != 30; ++i) {
    if (status / max < i / 30.)
      std::cout << " ";
    else
      std::cout << "\033[7;32m \033[0m";
  }
  if (status != max - 1)
    std::cout << "|\r";
  else
    std::cout << "|\n";
} // namespace )
}

#endif MISC_HPP