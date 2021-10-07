#include "distributions.hpp"
#include <string>
#include <vector>
int main() {
  std::vector<DistributionPair> uniform =
      generateUniformDistribution(1000, 0, 29, 5);
  plotDistribution("--- Uniform ---", uniform, 80);

  std::vector<DistributionPair> normal =
      generateNormalDistribution(100000, 100, 7, 30);
  plotDistribution("--- Normal ---", normal, 80);

  std::vector<DistributionPair> poisson =
      generatePoissonDistribution(100000, 8, 50);
  plotDistribution("--- Poisson ---", poisson, 80);

  return 0;
}
