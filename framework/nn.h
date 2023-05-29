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
#define MAT_PRINT(m) mat_print(m, #m)
float rand_float(void);
float signmoidf(float x);
typedef struct {
	size_t rows; //float 64
	size_t cols; //float 64
	size_t stride;
	float *es;  //pointer to the beginning of the data of the matrix
} Mat;
Mat mat_alloc(size_t rows, size_t cols);
void mat_rand(Mat m, float low, float high);
void mat_dot(Mat dst, const Mat a, const Mat b);
void mat_sum(Mat dst, const Mat a);
void mat_fill(Mat m, float val);
void mat_print(Mat m, const char* name);
void mat_sig(Mat m);
Mat mat_row(Mat m, size_t row);
void mat_copy(Mat dst, Mat src);


typedef struct {
	size_t count;
	Mat *ws;
	Mat *bs;
	Mat *as; // THE amount of activations is count + 1
} NN;
void nn_print(NN nn, const char *name);
#define NN_PRINT(nn) nn_print(nn, #nn)





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
	for (size_t i = 0; i < nn.count; i++){
		MAT_PRINT(*nn.ws);
		MAT_PRINT(*nn.bs);
	}

}
#endif // NN_IMPLEMENTATION
