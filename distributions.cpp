//////////////
// c++ assignment 3
// author: Nick Sorenson
// A02287085
//////////////
#include "distributions.hpp"
#include <iostream>
#include <random>
#include <string>
#include <vector>

DistributionPair::DistributionPair(std::uint32_t minValue,
                                   std::uint32_t maxValue)
    : minValue(minValue), maxValue(maxValue), count(0) {}

bool isEven(unsigned int x) { return (x % 2 == 0); }
std::vector<DistributionPair>
generateUniformDistribution(std::uint32_t howMany, std::uint32_t min,
                            std::uint32_t max, std::uint8_t numberBins) {
  std::vector<DistributionPair> myBins;
  int myMin = min;
  std::uint32_t width = ((max - min) / numberBins);
  for (int i = 0; i < numberBins; i++) {
    DistributionPair *bin = new DistributionPair(myMin, myMin + width);
    myMin += width + 1;
    myBins.push_back(*bin);
  }
  std::random_device rd;
  std::mt19937 engine(rd());
  std::uniform_int_distribution<unsigned int> dist(min, max);

  for (unsigned int i = 0; i < myBins.size(); i++) {
    std::cout << "[" << myBins[i].minValue << ", " << myBins[i].maxValue << "]"
              << std::endl;
  }
  for (unsigned int i = 0; i < howMany; i++) {
    // Creating howMany random nums
    unsigned int myRandN = dist(engine);
    unsigned int myIndex = ((myRandN - min) / (width + 1));
    if (myRandN > myBins.at(myBins.size() - 1).maxValue) {
      myBins.at(myBins.size() - 1).count++;
    } else {

      myBins.at(myIndex).count++;
    }
  }
  return myBins;
}
std::vector<DistributionPair>
generateNormalDistribution(std::uint32_t howMany, float mean, float stdev,
                           std::uint8_t numberBins) {
  std::uint32_t max = static_cast<std::uint32_t> ((mean + (4 * stdev)));
  std::uint32_t min = static_cast<std::uint32_t> ((mean - (4 * stdev)));
  std::uint32_t size = (max - min) / numberBins;

  std::vector<DistributionPair> mybins;
  for (std::uint32_t num = min; num < max; num += size) {
    DistributionPair *mypair = new DistributionPair(num, num + (size - 1));
    mybins.push_back(*mypair);
  }
  std::random_device rd;
  std::mt19937 engine(rd());
  std::normal_distribution<> distNorm(mean, stdev);
  // double myRandN = dist(engine);
  for (unsigned int i = 0; i < howMany; i++) {

    auto myRandN = distNorm(engine);
    unsigned int myRandNFloored = (static_cast<unsigned int>(myRandN));
    if (myRandNFloored > mybins.at(mybins.size() - 1).maxValue) {
      mybins.at(mybins.size() - 1).count++;
      continue;
    } else if (myRandNFloored < mybins.at(0).minValue) {
      mybins.at(0).count++;
      continue;
    }
    unsigned int index = (myRandNFloored - min) / size;
    mybins.at(index).count++;
  }
  return mybins;
}
std::vector<DistributionPair>
generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften,
                            std::uint8_t numberBins) {
  std::cout << "generating Poission Distributions..." << std::endl;
  int min = 0;
  // int max = numberBins - 1;
  int size = 1;
  //   std::cout << "bin size: " << size << std::endl;
  std::vector<DistributionPair> mybins;
  for (int i = min; i < numberBins; i += size) {
    DistributionPair *bin = new DistributionPair(i, i + (size - 1));
    mybins.push_back(*bin);
  }
  std::random_device rd;
  std::mt19937 engine(rd());
  std::poisson_distribution<int> dist(howOften);
  for (unsigned int i = 0; i < howMany; i++) {
    unsigned int myrandN = static_cast<unsigned int> (dist(engine));
    if (myrandN > mybins.at(mybins.size() - 1).maxValue) {
      mybins.at(mybins.size() - 1).count++;
      continue;
    } else if (myrandN < mybins.at(0).minValue) {
      mybins.at(0).count++;
      continue;
    }
    unsigned int index = (unsigned int)((myrandN - min) / size);
    mybins.at(index).count++;
  }
  return mybins;
}
void plotDistribution(std::string title,
                      const std::vector<DistributionPair> &distribution,
                      const std::uint8_t maxPlotLineSize) {
  std::uint32_t max = 0;
  std::uint32_t index = 0;
  for (int i = 0; i < distribution.size(); i++) {
    if (distribution[i].count > max) {
      max = distribution[i].count;
      index = i;
    }
  }
  std::double_t scale =
      (double)maxPlotLineSize / (double)distribution[index].count;

  std::cout << title << std::endl;
  for (DistributionPair dp : distribution) {
    // DistributionPair dp = distribution[i];
    std::string stars((uint32_t)(dp.count * scale), '*');
    std::cout << "[" << dp.minValue << ", " << dp.maxValue << "] : " << stars
              << std::endl;
  }
  std::cout << std::endl;
}
