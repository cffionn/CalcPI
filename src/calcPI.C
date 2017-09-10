#include <iostream>
#include <cmath>
#include <time.h>
#include <vector>
#include <thread>

#include "boost/random.hpp"

void calcPI(const unsigned long long nEvt, unsigned long long& inCircle, bool doClock)
{
  clock_t t;
  t = clock();
  
  //NOTE: I HAVE NOT TIED SEED TO CLOCK - WILL PRODUCE SAME RESULT EVERY TIME
  boost::mt19937 generator;
  boost::uniform_real<> dist(-1.,1.);
  boost::variate_generator<boost::mt19937&, boost::uniform_real<> > random(generator,dist);

  if(doClock) std::cout << "Clock start and seed - " << t << std::endl;
  random.engine().seed(t);
  random.distribution().reset();
  
  for(unsigned long long i = 0; i < nEvt; ++i){
    double x = random();
    double y = random();
    if(std::sqrt(x*x + y*y) < 1.) ++inCircle;

    if(clock() - t > 10*CLOCKS_PER_SEC && doClock){
      std::cout << "Processing event " << i << "/" << nEvt << std::endl;
      t = clock();
    }
  }  
  
  return;
}

int main(int argc, char* argv[])
{
  if(argc != 2){
    std::cout << "Usage: ./bin/calcPI.exe <Precision>" << std::endl;
    return 1;
  }

  unsigned long long nEvt = 4./(std::stof(argv[1])*std::stof(argv[1])) + 1;
  std::vector<std::thread> threads;
  std::vector<unsigned long long> inCircs;

  for(int i = 0; i < 4; ++i){
    inCircs.push_back(0);
  }
  std::thread first(calcPI, nEvt, std::ref(inCircs.at(0)), true);
  std::thread second(calcPI, nEvt, std::ref(inCircs.at(1)), false);
  std::thread third(calcPI, nEvt, std::ref(inCircs.at(2)), false);
  std::thread fourth(calcPI, nEvt, std::ref(inCircs.at(3)), false);
  
  first.join();
  second.join();
  third.join();
  fourth.join();
  
  unsigned long long tot = 0;
  
  for(int i = 0; i < 4; ++i){
    tot += inCircs.at(i);
  }

  std::cout << "PI = 4*(" << tot << " +- " << std::sqrt(double(4.*nEvt)) << ")/" << 4*nEvt << std::endl;

  return 0;
}
