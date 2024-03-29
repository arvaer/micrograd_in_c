


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
	float saved = 0;
	float c = cost(m, ti, to);
	for (size_t i = 0; i < m.w1.rows ; i++){
		for(size_t j = 0; j < m.w1.cols; j++){
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
