#ifndef NN_H_
#define NN_H_

#include <stddef.h>
#include <stdio.h>

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc //stb style usually has malloc define
#endif // NN_MALLOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif //NN_ASSERT

#define MAT_AT(m,i,j) m.es[(i)*(m).cols + (j)] 
typedef struct {
	size_t rows; //float 64
	size_t cols; //float 64
	float *es;  //pointer to the beginning of the data of the matrix
} Mat;

Mat mat_alloc(size_t rows, size_t cols);
void mat_mul(Mat dst, const Mat a, const Mat b);
void mat_sum(Mat dst, const Mat a, const Mat b);




//mat alloc
Mat mat_alloc(size_t rows, size_t cols){
	Mat m;
	m.rows = rows;
	m.cols = cols;
	m.es = NN_MALLOC(sizeof(*m.es)*rows*cols); //dereference to get the sizeof the block
	NN_ASSERT(m.es != NULL);
	return m;
}
//not allocating memory in the function, instead prealloc memory for all matrixes. Multiple into mat c
//mem cpy signature
void mat_mul(Mat dst, const Mat a, const Mat b){
	(void) dst;
	(void) a;
	(void) b;

}
void mat_sum(Mat dst, const Mat a, const Mat b){
	(void) dst;
	(void) a;
	(void) b;

}
void mat_print(const Mat m){
	for (size_t i = 0; i < m.rows; i++){
		for(size_t j = 0; j < m.cols; j++){
			printf("%f ", MAT_AT(m,i,j));
			}
		printf("\n");
	}
}
	



#endif // NN_H_

#ifdef NN_IMPLEMENTATION

#endif // NN_IMPLEMENTATION
