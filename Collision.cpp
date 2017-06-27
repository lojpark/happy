#include "stdafx.h"

bool collisionA(double x1, double y1, double w1, double h1, double x2, double y2){
	if( x1-w1/2 <= x2 && x2 <= x1+w1/2 && y1-h1/2 <= y2 && y2 <= y1+h1/2 ){
		return true;
	}
	return false;
}

bool collisionB(double x1, double w1, double x2, double w2){
	if( x2-w2/2 <= x1+w1/2 && x1+w1/2 <= x2+w2/2 ){
		return true;
	}
	if( x1-w1/2 <= x2+w2/2 && x2+w2/2 <= x1+w1/2 ){
		return true;
	}
	return false;
}