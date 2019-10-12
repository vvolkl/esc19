#include <cmath>

struct Point {

   double norm() const { return std::sqrt(x*x+y*y+z*z);}
   
   double x,y,z;

};

#include<random>

std::mt19937 reng;
std::normal_distribution<double> gauss(10.,1.);

void fill(Point & p) {
  p.x = gauss(reng);
  p.y = gauss(reng);
  p.z = gauss(reng);
}

#include<vector>
#include <chrono>
#include<iostream>


int main() {

 auto start = std::chrono::high_resolution_clock::now();
 auto delta=start-start;

  std::vector<Point> pointsI(1024*8);
  std::vector<Point> pointsO(1024*8);
  for (auto &p : pointsI) fill(p);
  double sum=0;
  for (int k=0; k<10000; ++k) {
    if (k>0) delta -= (std::chrono::high_resolution_clock::now()-start);    
    for (int i=0, n=pointsI.size(); i<n; ++i) {
      pointsO[i].x = pointsI[i].x/pointsI[i].norm();
      pointsO[i].y = pointsI[i].y/pointsI[i].norm();
      pointsO[i].z = pointsI[i].z/pointsI[i].norm();
    }
    if (k>0) delta += (std::chrono::high_resolution_clock::now()-start);
    for (auto &p : pointsO) sum+=p.x;

  }
   
 auto deltaF = std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
 std::cout << "time " << deltaF << " " << sum << std::endl;

}
