#include <iostream>
#include <Windows.h>
#include "time.h"
#include "detection.h"
#include "fileManagement.h"

using namespace std;


int main()
{
  /*
  unsigned int newTime = 0;
  startTime();

  newTime = calculateElapsedTime();
  cout <<newTime<<endl;

  int const nombre(2);
  double object[nombre];
  object[0] = -1.5;
  object[1] = -1;
  vector<double> result(2);
  result = positionMoveObject (object,0.5,33,50);
  cout << "x : " << result[0] << endl;
  cout << "y : " << result[1] << endl;
  */
  int const nombre(2);
  int const nombre2(5);
  double object[nombre2][nombre];
  object[0][0] = -1.5;
  object[0][1] = -1;
  object[1][0] = 1.5;
  object[1][1] = 1;
  object[2][0] = 2;
  object[2][1] = 3;
  object[3][0] = 5;
  object[3][1] = 5;
  object[4][0] = -5;
  object[4][1] = -4;
  double object2[nombre];
  object2[0] = 5;
  object2[1] = 1;
  string nameF;
  nameF=nameFile ("C:/Users/Caroline Duprat/Desktop/",object,nombre2,30,5.6,3.2,object2,20,2);
  cout << nameF<< endl;
  return 0;
}


