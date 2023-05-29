#define NN_IMPLEMENTATION
#include "nn.h"
#include <time.h>


typedef struct {
	Mat a0;
	Mat w1, b1, a1;
	Mat w2, b2, a2;
	Mat w3, b3, a3;

} Xor;
Xor xor_alloc(void){
	//initialization
	Xor m;
	m.a0 = mat_alloc(1,2); //input
	m.a1 = mat_alloc(1,2);
	m.a2 = mat_alloc(1,1);
	m.w1 = mat_alloc(2,2);
	m.b1 = mat_alloc(1,2);
	m.w2 = mat_alloc(2,1);
	m.b2 = mat_alloc(1,1);
	return m;
}

// Forward defined as sigf(X*W + B)
//	     [w11, w12
//[x1, x2] *   		+ [b1, b2] = [a1, a2]
//	     w21, w22]
//
void forward_xor(Xor m){
	//m.a1 is the dot product of m.ao(inputs) [x1, x2] and weights m.w1
	mat_dot(m.a1, m.a0, m.w1);
	//add biases to m.ai
	mat_sum(m.a1, m.b1);
	//take sigf of m.a1
	mat_sig(m.a1);

	mat_dot(m.a2, m.a1, m.w2);
	mat_sum(m.a2, m.b2);
	mat_sig(m.a2);
}

//Accept Xor m, Training Input, Training Output
float cost(Xor m, Mat ti, Mat to){
	//make sure each row is the same, they are training samples
	assert(ti.rows == to.rows);
	assert(to.cols == m.a2.cols);
	size_t n = ti.rows;
	float cost = 0;
	for(size_t i = 0; i < n; i++){
		Mat x = mat_row(ti, i);		
		Mat y = mat_row(to, i);
		mat_copy(m.a0,x);
		forward_xor(m);
	size_t q = to.cols;
	for(size_t j = 0; j < q; j++){
		float d = MAT_AT(m.a2,0,j) - MAT_AT(y,0,j);
		cost += d*d;
	}
	}
	return cost/n;
}
void finite_diff(Xor m, Xor g, Mat ti, Mat to,float eps){
	float saved;
	float c = cost(m, ti, to);
	for (size_t i = 0; i < m.w1.rows ; i++){
		for(size_t j = 0; j < m.w1.cols; j++){
			saved = MAT_AT(m.w1, i, j);
			MAT_AT(m.w1, i, j) += eps;
			MAT_AT(g.w1,i,j) = (cost(m,ti,to) - c)/eps;
			MAT_AT(m.w1, i, j) = saved;
		}
	}
	for (size_t i = 0; i < m.b1.rows ; i++){
		for(size_t j = 0; j < m.b1.cols; j++){
			saved = MAT_AT(m.b1, i, j);
			MAT_AT(m.b1, i, j) += eps;
			MAT_AT(g.b1,i,j) = (cost(m,ti,to) - c)/eps;
			MAT_AT(m.b1, i, j) = saved;
		}
	}
	for (size_t i = 0; i < m.w2.rows ; i++){
		for(size_t j = 0; j < m.w2.cols; j++){
			saved = MAT_AT(m.w2, i, j);
			MAT_AT(m.w2, i, j) += eps;
			MAT_AT(g.w2,i,j) = (cost(m,ti,to) - c)/eps;
			MAT_AT(m.w2, i, j) = saved;
		}
	}
	for (size_t i = 0; i < m.b2.rows ; i++){
		for(size_t j = 0; j < m.b2.cols; j++){
			saved = MAT_AT(m.b2, i, j);
			MAT_AT(m.b2, i, j) += eps;
			MAT_AT(g.b2,i,j) = (cost(m,ti,to) - c)/eps;
			MAT_AT(m.b2, i, j) = saved;
		}
	}
}

void xor_learn(Xor m, Xor g, float rate){
	for (size_t i = 0; i < m.w1.rows ; i++){
		for(size_t j = 0; j < m.w1.cols; j++){
			MAT_AT(m.w1, i, j) -= rate*MAT_AT(g.w1,i,j);
		}
	}
	for (size_t i = 0; i < m.b1.rows ; i++){
		for(size_t j = 0; j < m.b1.cols; j++){
			MAT_AT(m.b1, i, j) -= rate*MAT_AT(g.b1, i, j);
		}
	}
	for (size_t i = 0; i < m.w2.rows ; i++){
		for(size_t j = 0; j < m.w2.cols; j++){
			MAT_AT(m.w2, i, j) -= rate*MAT_AT(g.w2, i, j);
		}
	}
	for (size_t i = 0; i < m.b2.rows ; i++){
		for(size_t j = 0; j < m.b2.cols; j++){
			MAT_AT(m.b2, i, j) -= rate*MAT_AT(g.b2, i, j);
		}
	}

}

float td[] = {
	0,0,0,
	0,1,1,
	1,0,1,
	1,1,0
};

int main(void){
	
	size_t arch[] = {2, 2, 1};
	NN nn = nn_alloc(arch, ARRAY_LEN(arch));
	//NN_PRINT(nn);
	

//	return 0;
	
//#if 0
	srand(time(0));
	size_t stride = 3;
	size_t n = sizeof(td)/sizeof(td[0])/stride;
	Mat ti = {
		.rows = n, 
		.cols = 2, 
		.stride = stride, 
		.es = td
	};
	Mat to = {
		.rows = n,
		.cols = 1,
		.stride = stride,
		.es = td+2
	};
	
	Xor m = xor_alloc();
	Xor g = xor_alloc();
	mat_rand(m.w1, 0 ,1);
	mat_rand(m.b1, 0, 1);
	mat_rand(m.w2, 0, 1);
	mat_rand(m.b2, 0, 1);
	
	float eps = 1e-3;
	float rate = 1e-3;
	printf("%f  cost \n", cost(m, ti, to));
	for(int i = 0; i < 210000*100; i ++){
		finite_diff(m,g,ti,to,eps);
		xor_learn(m,g,rate);
		printf("%f  cost\n", cost(m, ti, to));
	}

#if 0

	float x1 = .1;
	float x2 = .2;
	for (size_t i = 0; i < 2; i ++){
		for(size_t j = 0; j< 2; j++){
			MAT_AT(m.a0, 0, 0) = x1;
			MAT_AT(m.a0, 0, 1) = x2;
			forward_xor(m);
			float y = *m.a2.es;
			printf("%zu ^ %zu = %f\n", i, j, y);
		}}
#endif //0
	return 0;
}
