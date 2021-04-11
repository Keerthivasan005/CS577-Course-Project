#define ROWS 512
#define COLS 512

void am_filter(int input_img[ROWS][COLS], int output_img[ROWS][COLS])
{
#pragma HLS INTERFACE bram port=output_img
#pragma HLS INTERFACE ap_memory port=input_img
	int j;
	int i;

	int temp0 = input_img[i][0];
	int temp1 = input_img[i][1];
	int temp2 = input_img[i][2];
	int temp3 = input_img[i][3];
	int temp4;
	
	for(i=0; i<ROWS; i++)
	{
		for(j=4; j<COLS-5; j++)
		{
			temp4 = input_img[i][j];

			output_img[i][j] = (temp4 + temp3 + temp2 + temp1 + temp0) / 5;
			temp0 = temp1;
			temp1 = temp2;
			temp2 = temp3;
			temp3 = temp4;

		
//		output_img[i][j] = (input_img[i][j+4] + input_img[i][j+3] + input_img[i][j+2] + input_img[i][j+1] + input_img[i][j]) / 5;

	    }
	}
}
