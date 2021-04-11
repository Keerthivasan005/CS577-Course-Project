#include <stdio.h>
#include <math.h>

#define m 10
#define n 10

const double pi = 3.143;

void dctTransform(int matrix[10][10], float dct[10][10])
{
    int i, j, k, l;
    const float a = pi/(2*m);
    const float b = pi/(2*n);
    float ci, cj, dct1, sum;
    for (i = 0; i < m; i++) {
#pragma HLS PIPELINE
        for (j = 0; j < n; j++) {
#pragma HLS PIPELINE
            if (i == 0)
                ci = 1 / sqrt(m);
            else
                ci = sqrt(2) / sqrt(m);
            if (j == 0)
                cj = 1 / sqrt(n);
            else
                cj = sqrt(2) / sqrt(n);
            sum = 0;
            for (k = 0; k < m/2 - 1; k++) {
                for (l = 0; l < n; l++) {
                    dct1 = matrix[k][l] *
                           cos((2 * k + 1) * i * a) *
                           cos((2 * l + 1) * j * b);
                    sum = sum + dct1;
                }
            }
            for (k = m/2; k < m ; k++ ){
            	for (l = 0; l < n; l++) {
            		dct1 = matrix[k][l] *
            		       cos((2 * k + 1) * i * a) *
						   cos((2 * l + 1) * j * b);
						sum = sum + dct1;
            	}
            }
            dct[i][j] = ci * cj * sum;
        }
    }
}
