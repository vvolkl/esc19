#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <execution>
#include <chrono>

int main()
{
  // define a pseudo-random number generator engine and seed it using an actual
  // random device
  std::random_device rd;
  std::mt19937 eng{rd()};

  int const MAX_N = 100;
  std::uniform_int_distribution<int> uniform_dist{1, MAX_N};

  // fill a vector with SIZE random numbers
  int const SIZE = 10000000;
  std::vector<int> v;
  v.reserve(SIZE);
  std::generate_n(std::back_inserter(v), SIZE, [&]() { return uniform_dist(eng); });

  {
    std::cout << "sum all the elements of the vector with std::accumulate" << std::endl;
    auto t0 = std::chrono::high_resolution_clock::now();
    // sum all the elements of the vector with std::accumulate
    std::accumulate(v.begin(), v.end(), 0);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> d = t1 - t0;
    std::cout << " \t in " << d.count() << " s\n";
  }

  {
    std::cout << "sum all the elements of the vector with std::reduce, sequential policy" << std::endl;
    auto t0 = std::chrono::high_resolution_clock::now();
    double result = std::reduce(std::execution::sequenced_policy, v.begin(), v.end());
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> d = t1 - t0;
    std::cout << " \t in " << d.count() << " s\n";
  }

  {
    std::cout << "sum all the elements of the vector with std::reduce, parallel policy" << std::endl;
    auto t0 = std::chrono::high_resolution_clock::now();
    double result = std::reduce(std::execution::par, v.begin(), v.end());
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> d = t1 - t0;
    std::cout << " \t in " << d.count() << " s\n";
  }

  {
    std::cout << "sort the vector with std::sort " << std::endl;
    auto t0 = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> d = t1 - t0;
    std::cout << " \t in " << d.count() << " s\n";
  }

  {
    std::cout << "sort the vector with std::sort, parallel policy" << std::endl;
    auto t0 = std::chrono::high_resolution_clock::now();
    std::sort(std::execution::par, v.begin(), v.end());
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> d = t1 - t0;
    std::cout << " \t in " << d.count() << " s\n";
  }
}

