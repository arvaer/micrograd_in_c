#define NN_IMPLEMENTATION
#include "nn.h"
#include <time.h>


typedef struct {
	Mat a0;
	Mat w1, b1, a1;
	Mat w2, b2, a2;
	Mat w3, b3, a3;

} Xor;

// Forward defined as sigf(X*W + B)
//	     [w11, w12
//[x1, x2] *   		+ [b1, b2] = [a1, a2]
//	     w21, w22]
//
float forward_xor(Xor m, float x1, float x2){

	MAT_AT(m.a0, 0, 0) = x1;
	MAT_AT(m.a0, 0, 1) = x2;
	//m.a1 is the dot product of m.ao(inputs) [x1, x2] and weights m.w1
	mat_dot(m.a1, m.a0, m.w1);
	//add biases to m.ai
	mat_sum(m.a1, m.b1);
	//take sigf of m.a1
	mat_sig(m.a1);

	mat_dot(m.a2, m.a1, m.w2);
	mat_sum(m.a2, m.b2);
	mat_sig(m.a2);


	float y = *m.a2.es;
	return y;
}

int main(void){
	srand(time(0));
	Xor m;
	//initialization
	m.a0 = mat_alloc(1,2); //input
	m.a1 = mat_alloc(1,2);
	m.a2 = mat_alloc(1,1);
	m.w1 = mat_alloc(2,2);
	m.b1 = mat_alloc(1,2);
	m.w2 = mat_alloc(2,1);
	m.b2 = mat_alloc(1,1);
	mat_rand(m.w1, 0 ,1);
	mat_rand(m.b1, 0, 1);
	mat_rand(m.w2, 0, 1);
	mat_rand(m.b2, 0, 1);
	
	for (size_t i = 0; i < 2; i ++){
		for(size_t j = 0; j< 2; j++){
			printf("%zu ^ %zu = %f\n", i, j, forward_xor(m,i,j));
		}}

	return 0;
}
