#include<random>
#include<cstdint>
#include<algorithm>
#include<iostream>
#include<chrono>
#include<cassert>
#include<list>
#include<memory>




#define Float float

struct BasePoint {
  virtual ~BasePoint(){}
  virtual Float x() const=0;
  virtual Float& x()=0;

  Float y,z;
  bool ok;

};

struct PointA : public BasePoint {

  ~PointA() override {}

  Float x() const override { return m_x;}
  Float & x() override { return m_x;}

  Float m_x;
};


struct PointB : public BasePoint {

  ~PointB() override {}

  Float x() const override { return m_x;}
  Float & x() override { return m_x;}

  Float m_x;
};



constexpr int N=200000;
std::mt19937 reng;
std::poisson_distribution<int> aGen(N);
std::uniform_real_distribution<Float> ugen(Float(-1),Float(1));
std::uniform_int_distribution<int> igen(1,10);


using Container = std::list<std::unique_ptr<BasePoint>>;

Container generate() {

  Container cont;
  // generate
  int ntot = aGen(reng);
  for (int i=0; i<ntot; ++i) {
    auto w = igen(reng);
    std::unique_ptr<BasePoint> p(w>5 ? (BasePoint*)(new PointA()) : (BasePoint*)(new PointB())); 
    p->x() =  ugen(reng);
    p->y =  ugen(reng);
    p->z =  ugen(reng);
    auto r = igen(reng);
    p->ok = r<7;
    cont.insert(cont.end(),std::move(p));
  }
  
  return cont;

}



int main() {

  auto start = std::chrono::high_resolution_clock::now();

  auto delta = start-start;


  auto points = generate();
  

  for (int k=0; k<2000; ++k) {
    delta -= (std::chrono::high_resolution_clock::now()-start);
    for (auto & p : points) {
      p->x() += k;
    }  
   delta += (std::chrono::high_resolution_clock::now()-start);
  }

  std::cout << " elapsted time (ms) " << std::chrono::duration_cast<std::chrono::milliseconds>(delta).count() << std::endl;

}
