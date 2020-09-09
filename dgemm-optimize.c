#include <stdlib.h>

//REORDERING
void reordering(int m, int n, float *A, float *C) {
  for (int k = 0; k < n; k++) 
    for (int j = 0; j < m; j++) 
      for (int i = 0; i < m; i++) 
        C[i+j*m] += A[i+k*m] * A[j+k*m];
}

//UNROLLING
void unrolling(int m, int n, float *A, float *C) {
  int unrolled = m / 6;
  int i,j,k;
  for (k = 0; k < n; ++k) {
    for(j = 0; j < m; ++j) {
      for(i = 0; i < unrolled; i += 6) {
        C[i+j*m] += A[i+k*m] * A[j+k*m];
        C[(i+1)+j*m] += A[(i+1)+k*m] * A[j+k*m];
        C[(i+2)+j*m] += A[(i+2)+k*m] * A[j+k*m];
        C[(i+3)+j*m] += A[(i+3)+k*m] * A[j+k*m];
        C[(i+4)+j*m] += A[(i+4)+k*m] * A[j+k*m];
        C[(i+5)+j*m] += A[(i+5)+k*m] * A[j+k*m];
      }
      while (i<m) {
        C[i+j*m] += A[i+k*m] * A[j+k*m];
      	i++;
      }
    }
  }
}

//PADDING MATRIX
void matrixPad(int m, int n, float *A, float *C) {

  //If number of columns is odd.
	if (n%2) {
    int newSize = n+1;
    // Then initialize an array with an even number of columns with zero value.
		float *B = (float*)malloc(m * (newSize) * sizeof(float));
		for (int i = 0; i < (m * (newSize)); i++) {
				B[i] = 0;		
		}

    // Copy the matrix element in this array.
		for (int i = 0; i < (m * n); i++) {
				B[i] = A[i];
			
		}
	}
	else if (m%2) {
    int newSize = m+1;
		
		float *B = (float*)malloc(n * (newSize) * sizeof(float));

		for (int i = 0; i < ((newSize) * n); i++) {
				B[i] = 0;
		}

    for (int i = 0; i < (m * n); i++) {
          B[i] = A[i];
        
      }
	}  
		// Do the matrix multiplication.
	for (int i = 0; i < m; i++)
		for (int k = 0; k < n; k++)
			for (int j = 0; j < m; j++)
				C[i + j * m] += A[i + k * m] * A[j + k * m];
	

}

void dgemm(int m, int n, float *A, float *C ){
	// reordering(m,n,A,C);
  //unrolling(m,n,A,C);
	 matrixPad(m,n,A,C);

}






 