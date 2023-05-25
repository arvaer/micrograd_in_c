#ifndef NN_H_
#define NN_H_


// x84_64 mac
typedef struct {
	size_t rows; //float 64
	size_t cols; //float 64
	float *es;  //pointer to the beginning of the data of the matrix
} Mat;

//mat alloc
Mat mat_alloc(size_t rows, size_t cols);
//not allocating memory in the function, instead prealloc memory for all matrixes. Multiple into mat c
//mem cpy signature
void mat_doc(Mat dst, const Mat a, const Mat b);
void mat_sum(Mat dst, const Mat a, const Mat b);
void mat_print();



#endif // NN_H_

#ifdef NN_IMPLEMENTATION

#endif // NN_IMPLEMENTATION
