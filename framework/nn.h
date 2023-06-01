#ifndef NN_H_
#define NN_H_

#include <stddef.h>
#include <stdio.h>
#include <math.h>

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc //stb style usually has malloc define
#endif // NN_MALLOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif //NN_ASSERT

#define MAT_AT(m,i,j) m.es[(i)*(m).stride + (j)] 
#define ARRAY_LEN(xs) sizeof(xs) / sizeof(xs[0])
#define MAT_PRINT(m) mat_print(m, #m, 0)
#define NN_PRINT(nn) nn_print(nn, #nn)
#define NN_INPUT(nn) (nn).as[0]
#define NN_OUTPUT(nn) (nn).as[(nn).count]

typedef struct {
	size_t rows; //float 64
	size_t cols; //float 64
	size_t stride;
	float *es;  //pointer to the beginning of the data of the matrix
} Mat;
typedef struct {
	size_t count;
	Mat *ws;
	Mat *bs;
	Mat *as; // THE amount of activations is count + 1
} NN;



float rand_float(void);
float signmoidf(float x);
Mat mat_alloc(size_t rows, size_t cols);
void mat_rand(Mat m, float low, float high);
void mat_dot(Mat dst, const Mat a, const Mat b);
void mat_sum(Mat dst, const Mat a);
void mat_fill(Mat m, float val);
void mat_print(Mat m, const char* name, size_t padding);
void mat_sig(Mat m);
Mat mat_row(Mat m, size_t row);
void mat_copy(Mat dst, Mat src);





void nn_print(NN nn, const char *name);
void nn_rand(NN nn, float low, float high);
void nn_forward(NN nn);
float nn_cost(NN n, Mat in, Mat out);
void nn_finite_diff(NN n, NN g, Mat input, Mat output, float eps);
void nn_learn(NN n, NN g, float rate);

#endif // NN_H_
#ifdef NN_IMPLEMENTATION
float rand_float(void){
	return (float) rand() / (float) RAND_MAX;
}
float sigmoidf(float x){
	return 1.f / (1.f + expf(-x));
}
Mat mat_alloc(size_t rows, size_t cols){
	Mat m;
	m.rows = rows;
	m.cols = cols;
	m.stride = cols;
	m.es = NN_MALLOC(sizeof(*m.es)*rows*cols); //dereference to get the sizeof the block
	NN_ASSERT(m.es != NULL);
	return m;
}

void mat_rand(Mat m, float low, float high){
	for (size_t i = 0; i < m.rows ; i++){
		for(size_t j = 0; j < m.cols; j++){
			MAT_AT(m,i,j) = rand_float() * (high - low) + low;
		}}
}
//abstract later for more activation functions
void mat_sig(Mat m){
	for (size_t i = 0; i < m.rows ; i++){
		for(size_t j = 0; j < m.cols; j++){
			MAT_AT(m,i,j) = sigmoidf(MAT_AT(m,i,j));
		}}
}

Mat mat_row(Mat m, size_t row){
	return (Mat){
	.rows = 1,
	.cols = m.cols,
	.stride = m.stride,
	.es = &MAT_AT(m,row,0)};
}

void mat_copy(Mat dst, Mat src){
	NN_ASSERT(dst.rows == src.rows);
	NN_ASSERT(dst.cols == src.cols);
	for(size_t i = 0; i < dst.rows ; i ++){
		for(size_t j = 0; j < dst.cols ; j++){
		MAT_AT(dst, i, j) = MAT_AT(src, i, j);
		}
	}
}
//not allocating memory in the function, instead prealloc memory for all matrixes. Multiple into mat c
//mem cpy signature
void mat_dot(Mat dst, const Mat a, const Mat b){
	//not defined unless the inner sizes are equal
	//i.e a.cols ==  b.rows
	NN_ASSERT(a.cols == b.rows);
	//make sure that dst size is a.cols, b.rows
	NN_ASSERT(dst.rows = a.cols);
	NN_ASSERT(dst.cols = b.rows);

	size_t n = a.cols;
	for(size_t i = 0; i < dst.rows; i++){
		for(size_t j = 0; j < dst.cols; j++){
			MAT_AT(dst, i, j) = 0;
			for(size_t k = 0; k < n; k++){
				MAT_AT(dst, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
			}
		}
	}

}
void mat_sum(Mat dst, const Mat a){
	//1 x 2 * 2 * x
	NN_ASSERT(dst.rows == a.rows);
	NN_ASSERT(dst.cols == a.cols);
	for(size_t i = 0; i < dst.rows; i ++){
		for(size_t j = 0; j < dst.cols; j++){
			MAT_AT(dst, i, j) += MAT_AT(a, i, j);
		}
	}

}
void mat_print(const Mat m, const char* name, size_t padding){
	printf("%*s%s = [\n", (int) padding, "", name);
	for (size_t i = 0; i < m.rows; i++){
	printf("%*s   ", (int) padding, "");
		for(size_t j = 0; j < m.cols; j++){
				printf("%f ", MAT_AT(m,i,j));
			}
		printf("\n");
	}
	printf("%*s]\n", (int) padding, "");
}

void mat_fill(Mat m, float val){
	for (size_t i = 0; i < m.rows; i++){
		for(size_t j = 0; j < m.cols; j++){
			MAT_AT(m, i, j) = val;	
		}
	}
}



NN nn_alloc(size_t *arch, size_t arch_count){
	//initialization
	NN nn;
	NN_ASSERT(arch_count > 0);
	nn.count = arch_count - 1;
	nn.ws = NN_MALLOC(sizeof(*nn.ws)*nn.count);
	NN_ASSERT(nn.ws != NULL);
	nn.bs = NN_MALLOC(sizeof(*nn.bs)*nn.count);
	NN_ASSERT(nn.bs != NULL);
	nn.as = NN_MALLOC(sizeof(*nn.as)*(nn.count+1));
	NN_ASSERT(nn.as != NULL);
	nn.as[0] = mat_alloc(1,arch[0]);
	for (size_t i = 1; i < arch_count; i++){
		nn.ws[i-1] = mat_alloc(nn.as[i-1].cols, arch[i]);
		nn.bs[i-1] = mat_alloc(1, arch[i]);
		nn.as[i] = mat_alloc(1, arch[i]);
	}
	return nn;
}

void nn_print(NN nn, const char *name){
	printf("%s = [\n", name);
	char buf[256];
	for (size_t i = 0; i < nn.count; i++){
		snprintf(buf, sizeof(buf), "ws%zu", i);
		mat_print(nn.ws[i], buf, 4);
		snprintf(buf, sizeof(buf), "bs%zu", i);
		mat_print(nn.bs[i], buf, 4);
	}

}

void nn_rand(NN nn, float low, float high){
	size_t n = nn.count;
	for(size_t i = 0; i < n; i++){
		mat_rand(nn.ws[i], low, high);
		mat_rand(nn.bs[i], low, high);
	}
}
// Forward defined as sigf(X*W + B)
//	     [w11, w12
//[x1, x2] *   		+ [b1, b2] = [a1, a2]
//	     w21, w22]
//
//
//
void nn_forward(NN nn){
	for(size_t i = 0; i < nn.count; i++){
		mat_dot(nn.as[i+1], nn.as[i], nn.ws[i]);
		mat_sum(nn.as[i+1], nn.bs[i]);
		//doesnt overflow because activations is count+1
		mat_sig(nn.as[i+1]);
	}
}
float nn_cost(NN nn, Mat ti, Mat to){
	//make sure each row is the same, they are training samples
	assert(ti.rows == to.rows);
	assert(to.cols == NN_OUTPUT(nn).cols);
	size_t n = ti.rows;
	float cost = 0;
	for(size_t i = 0; i < n; i++){
		Mat x = mat_row(ti, i);		
		Mat y = mat_row(to, i);
		mat_copy(NN_INPUT(nn),x);
		nn_forward(nn);
	size_t q = to.cols;
	for(size_t j = 0; j < q; j++){
		float d = MAT_AT(NN_OUTPUT(nn),0,j) - MAT_AT(y,0,j);
		cost += d*d;
	}
	}
	return cost/n;
}

void nn_finite_diff(NN nn, NN g, Mat ti, Mat to, float eps){
	float saved = 0.0;
	float c = nn_cost(nn, ti, to);
	
	for(size_t a = 0; a < nn.count ; a++){
		size_t wrows = nn.ws[a].rows;
		size_t wcols = nn.ws[a].cols;

		size_t brows = nn.bs[a].rows;
		size_t bcols = nn.bs[a].cols;

		for(size_t i = 0; i < wrows; i++){
			for(size_t j = 0; j<wcols; j++){
				saved = MAT_AT(nn.ws[a], i, j);
				MAT_AT(nn.ws[a], i, j) += eps;
				MAT_AT(g.ws[a], i, j) = (nn_cost(nn, ti, to) - c)/eps;
				MAT_AT(nn.ws[a], i, j) = saved;
			}
		}
		for(size_t i = 0; i < brows; i++){
			for(size_t j = 0; j<bcols; j++){
				saved = MAT_AT(nn.bs[a], i, j);
				MAT_AT(nn.bs[a], i, j) += eps;
				MAT_AT(g.bs[a], i, j) = (nn_cost(nn, ti, to) - c)/eps;
				MAT_AT(nn.bs[a], i, j) = saved;
			}
			

		}
	}
}

void nn_learn(NN nn, NN g, float rate){
	for(size_t a = 0; a < nn.count; a++){
		size_t wrows = nn.ws[a].rows;
		size_t wcols = nn.ws[a].cols;
		size_t brows = nn.bs[a].rows;
		size_t bcols = nn.bs[a].cols;

		for(size_t i = 0; i < wrows; i++){
			for(size_t j = 0; j<wcols; j++){
				MAT_AT(nn.ws[a], i, j) -= rate * MAT_AT(g.ws[a], i, j);

			}
		}
		for(size_t i = 0; i < brows; i++){
			for(size_t j = 0; j<bcols; j++){
				MAT_AT(nn.bs[a], i, j) -= rate*MAT_AT(g.bs[a], i, j);
			}
	}
}
}


#endif // NN_IMPLEMENTATION
