#include <math.h>
#include <iostream>
#include "R2Graph.h"

using namespace std; 

int main() {
R2Point a, b ,c, cntr;
cout << "Input a, b and c. Each on one line with a space between x and y coordinate.\n";
cin>>a>>b>>c;
R2Vector ab=(b-a); 
R2Vector bc=(c-b); 
R2Vector ac=(c-a);

R2Vector Nab= ab.normal();
R2Vector Nbc= bc.normal();
R2Vector Nac=ac.normal();

R2Point AB=(a+b)*0.5; 
R2Point BC=(b+c)*0.5; 
R2Point AC=(a+c)*0.5;
intersectStraightLines(BC, Nbc, AB, Nab, cntr);
Nab.normalize();
cout << "Center:"<<cntr  << "radius:"<<fabs((cntr - a)*Nab)<<endl;
return 0;
}
