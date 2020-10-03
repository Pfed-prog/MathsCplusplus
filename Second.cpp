#include <cmath>
#include <iostream>
#include "R3Graph.h"
#include "R2Graph.h"
using namespace std; 
using namespace R3Graph;

R3Vector radiusVector(double lat, double lon);

const double EARTH_RADIUS = 6378000.0;
const double PI = 3.14159265358979323846;

void earth2map(
	double lat, double lon,
	double mapLat, double mapLon,
	R2Point& mapPoint
);

int main() {
	while(true){
		double mapLat, mapLon;
		cout << "Input mLat and mLon\n";
		cin>>mapLat>>mapLon;
		if (!cin.good())
			break;
		double lat, lon;
		cout << "Input lat and lon\n";
		cin >> lat>>lon;
		R2Point p;
		earth2map(
			lat, lon,
			mapLat, mapLon,
			p
		);
		cout << p<<endl;
	}
	return 0;
}
R3Vector radiusVector(double lat, double lon){
	double phi = lon*PI/180;
	double theta = lat*PI/180;
	double cosTheta = cos(theta);
	return R3Vector(cos(phi)*cos(theta), sin(phi)*cos(theta),sin(theta));
}

void earth2map(
	double lat, double lon,
	double mapLat, double mapLon,
	R2Point& mapPoint
){
	R3Vector mapCenter = radiusVector(mapLat, mapLon);
	R3Vector mapNormal = mapCenter;
	mapNormal.normalize();
	R3Point centerPoint = R3Point(0.,0.,0.)+mapCenter*EARTH_RADIUS;
	R3Point mapR3Point;
	intersectPlaneAndLine(
		centerPoint, mapNormal,
		R3Point(0.,0.,0.), radiusVector(lat, lon),
		mapR3Point
	);
	R3Vector nord(0.,0.,1.);
	R3Vector ex = nord.vectorProduct(mapNormal);
	ex.normalize();
	R3Vector ey = mapNormal.vectorProduct(ex);
	ey.normalize();
	double x = (mapR3Point - centerPoint)*ex;
	double y = (mapR3Point - centerPoint)*ey;
	mapPoint = R2Point(x,y);
}
