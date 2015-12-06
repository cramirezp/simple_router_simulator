#include <math.h>

double iacum_exp(double F, double lambda){
	if(F>=0 && F<=1.0)
		return -log(1-F)/lambda;
	else{
		printf("what!\n");
		return -1.0;
	}
}