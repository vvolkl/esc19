#include<random>
#include<cstdint>
#include<algorithm>
#include<iostream>
#include<chrono>
#include<cassert>
#include<list>
#include<memory>




#define Float float

struct Points {

  std::unique_ptr<Float[]> x, y, z;
  std::unique_ptr<bool[]>  ok;
  int ntot;
};


constexpr int N=200000;
std::mt19937 reng;
std::poisson_distribution<int> aGen(N);
std::uniform_real_distribution<Float> ugen(Float(-1),Float(1));
std::uniform_int_distribution<int> igen(1,10);



Points generate() {

  Points cont;
  // generate
  int ntot = aGen(reng);
  cont.ntot = ntot;
  cont.x = std::make_unique<Float[]>(ntot);
  cont.y = std::make_unique<Float[]>(ntot);
  cont.z = std::make_unique<Float[]>(ntot);
  cont.ok = std::make_unique<bool[]>(ntot);

  for (int i=0; i<ntot; ++i) {
    cont.x[i] =  ugen(reng);
    cont.y[i] =  ugen(reng);
    cont.z[i] =  ugen(reng);
    auto r = igen(reng);
    cont.ok[i] = r<7;
  }
  
  return cont;

}



int main() {

  auto start = std::chrono::high_resolution_clock::now();

  auto delta = start-start;

  auto points = generate();
  

  for (int k=0; k<10000; ++k) {
    delta -= (std::chrono::high_resolution_clock::now()-start);
    for (int i=0; i<points.ntot; ++i) {
      points.x[i] += k;
    }  
   delta += (std::chrono::high_resolution_clock::now()-start);
  }

  std::cout << " elapsted time (ms) " << std::chrono::duration_cast<std::chrono::milliseconds>(delta).count() << std::endl;

  return 0;
}
