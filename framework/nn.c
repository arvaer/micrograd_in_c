#define NN_IMPLEMENTATION
#include "nn.h"
#include <time.h>

int main(void){
	srand(time(0));
	float id_data[4] = {1, 0, 0, 1};
	Mat id = { .rows = 2, .cols = 2, .es = id_data };


	Mat a = mat_alloc(1,2);
	Mat b = mat_alloc(2, 2);
	Mat M = mat_alloc(1, 2);
	mat_rand(a, 5, 10);
	mat_fill(b,1);
	
	mat_print(a);
	printf("************ \n");
	mat_print(b);
	printf("************\n");
	mat_dot(M, a, id);
	mat_print(M);
	


	return 0;
}
