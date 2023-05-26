#define NN_IMPLEMENTATION
#include "nn.h"
#include <time.h>


typedef struct {
	Mat a0;
	Mat w1. b1. a1;
	Mat w2, b2, a2;
	Mat w3, b3, a3;

}Xor;



int main(void){
	srand(time(0));

	// Forward defined as sigf(X*W + B)
	//	     [w11, w12
	//[x1, x2] *   		+ [b1, b2] = [a1, a2]
	//	     w21, w22]
	//

	Mat x = mat_alloc(1,2); //input
	Mat a1 = mat_alloc(1,2);
	mat a2 = mat_alloc(1,1);
	Mat w1 = mat_alloc(2,2);
	Mat b1 = mat_alloc(1,2);
	Mat w2 = mat_alloc(2,1);
	Mat b2 = mat_alloc(1,1);
	mat_rand(w1, 0 ,1);
	mat_rand(b1, 0, 1);
	mat_rand(w2, 0, 1);
	mat_rand(b2, 0, 1);

	

	MAT_AT(x, 0, 0) = 0;
	MAT_AT(x, 0, 1) = 1;
	mat_dot(a1, x, w1);
	mat_sum(a1, b1);
	mat_sig(a1);

	mat_dot(a2, a1, w2);
	mat_sum(a2, b2);
	mat_sig(a2)
	
	MAT_PRINT(a1);
	MAT_PRINT(a2);


	return 0;
}
