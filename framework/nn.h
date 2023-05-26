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

#define MAT_AT(m,i,j) m.es[(i)*(m).cols + (j)] 

float rand_float(void);
float signmoidf(float x);
typedef struct {
	size_t rows; //float 64
	size_t cols; //float 64
	float *es;  //pointer to the beginning of the data of the matrix
} Mat;

Mat mat_alloc(size_t rows, size_t cols);
void mat_rand(Mat m, float low, float high);
void mat_dot(Mat dst, const Mat a, const Mat b);
void mat_sum(Mat dst, const Mat a);
void mat_fill(Mat m, float val);
void mat_print(Mat m, const char* name);
void mat_sig(Mat m);

#define MAT_PRINT(m) mat_print(m, #m)

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
	(void) dst;
	(void) a;

}
void mat_print(const Mat m, const char* name){
	printf("%s = [\n", name);
	for (size_t i = 0; i < m.rows; i++){
		for(size_t j = 0; j < m.cols; j++){
				printf("    %f ", MAT_AT(m,i,j));
			}
		printf("\n");
	}
	printf("]\n");
}

void mat_fill(Mat m, float val){
	for (size_t i = 0; i < m.rows; i++){
		for(size_t j = 0; j < m.cols; j++){
			MAT_AT(m, i, j) = val;	
		}
	}
}

#endif // NN_IMPLEMENTATION
