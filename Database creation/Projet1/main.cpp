#include <iostream>
#include <Windows.h>
#include "time.h"
#include "detection.h"

using namespace std;


int main()
{
  /*
  unsigned int newTime = 0;
  startTime();

  newTime = calculateElapsedTime();
  cout <<newTime<<endl;
  */
  int const nombre(2);
  double object[nombre];
  object[0] = -1.5;
  object[1] = -1;
  vector<double> result(2);
  result = positionMoveObject (object,0.5,33,50);
  cout << "x : " << result[0] << endl;
  cout << "y : " << result[1] << endl;
  return 0;
}


