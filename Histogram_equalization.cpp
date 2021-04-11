#define ROWS 512
#define COLS 512

void hist_Equalization(char input_img[ROWS][COLS], char output_img[ROWS][COLS])
{
#pragma HLS INTERFACE ap_fifo port=output_img
#pragma HLS INTERFACE ap_memory port=input_img

	// Declaring array for histogram distribution
	static int hist_h1[256] = { 0 };
	static int hist_h2[256] = { 0 };
	static int hist_h3[256] = { 0 };
	static int hist_h4[256] = { 0 };
	static int hist[256] = { 0 };
	static int new_hist[256] = { 0 };


	// Declaring array for reading a row of image
	// static char row_img[COLS];

	// Total no of pixel
	int total_pixel = ROWS * COLS;

	// Temporary variables
	int i, row, col;

	// Variable to calculate CDF
	int cdf = 0;

	// To plot the histogram we find the frequency of each pixel
	// Read a row of image
	for(row=0; row<ROWS; row++)
	{
		// Find and put the value in each pixel to hist array
		for(col=0; col<COLS; col = col + 4)
		{
#pragma HLS PIPELINE
			hist_h1[(int)input_img[row][col]]++;
			hist_h2[(int)input_img[row][col+1]]++;
			hist_h3[(int)input_img[row][col+2]]++;
			hist_h4[(int)input_img[row][col+3]]++;
		}
	}

	// Calculate CDF and form the new_hist
	float const multiplier = 255.0 / total_pixel;
	for(i=0; i<256; i++)
	{
		hist[i] = hist_h1[i] + hist_h2[i] + hist_h3[i] + hist_h4[i];

		// CDF calculation
		cdf = cdf + hist[i];

		// Calculation of new hist array
		new_hist[i] = (int)(cdf * multiplier);
	}

	// Performing Histogram Equalization by mapping new hist levels
	for(row=0; row<ROWS; row++)
	{
		for(col=0; col<COLS; col++)
		{
			// Mapping function
			output_img[row][col] = (unsigned char)new_hist[input_img[row][col]];
		}
	}

}
