#include "helpers.h"

#include <cs50.h>
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			BYTE b = image[i][j].rgbtBlue;
			BYTE g = image[i][j].rgbtGreen;
			BYTE r = image[i][j].rgbtRed;
			BYTE mean = round((b + g + r) / 3.0);
			image[i][j].rgbtBlue = mean;
			image[i][j].rgbtGreen = mean;
			image[i][j].rgbtRed = mean;
		}
	}

	return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0, half = width / 2; j < half; j++)
		{
			int op_index = width - 1 - j;
			RGBTRIPLE temp = image[i][j];
			image[i][j] = image[i][op_index];
			image[i][op_index] = temp;
		}
	}
	return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE temp[height][width];
	//printf("Height: %i, Width: %i \n", height, width);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			BYTE b = image[i][j].rgbtBlue;
			BYTE g = image[i][j].rgbtGreen;
			BYTE r = image[i][j].rgbtRed;

			temp[i][j].rgbtBlue = b;
			temp[i][j].rgbtGreen = g;
			temp[i][j].rgbtRed = r;
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int b_sum = 0;
			int g_sum = 0;
			int r_sum = 0;
			int count = 0;

			for (int k = i - 1; k <= i + 1; k++)
			{
				for (int l = j - 1; l <= j + 1; l++)
				{
					int shift_k = k - (i - 1);
					int shift_l = l - (j - 1);
					//printf("Abs: %i, %i, Semirel: %i, %i Rel: %i %i", i, j, k,
//						   l, shift_k, shift_l);

					bool ib_top = k >= 0;
					bool ib_bottom = k < height;
					bool ib_left = l >= 0;
					bool ib_right = l < width;
					bool ib = ib_top && ib_bottom && ib_left && ib_right;

					if (ib)
					{
						b_sum += image[k][l].rgbtBlue;
						g_sum += image[k][l].rgbtGreen;
						r_sum += image[k][l].rgbtRed;
						count++;
						//printf("    ~~~~IB~~~\n");
					}
					else
					{
						//printf("\n");
					}
				}
			}

			//printf("\n");
			BYTE b_mean = round(b_sum / (count * 1.0));
			BYTE g_mean = round(g_sum / (count * 1.0));
			BYTE r_mean = round(r_sum / (count * 1.0));

			temp[i][j].rgbtBlue = b_mean;
			temp[i][j].rgbtGreen = g_mean;
			temp[i][j].rgbtRed = r_mean;
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
			image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
			image[i][j].rgbtRed = temp[i][j].rgbtRed;
		}
	}
	return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

	RGBTRIPLE temp[height][width];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			BYTE b = image[i][j].rgbtBlue;
			BYTE g = image[i][j].rgbtGreen;
			BYTE r = image[i][j].rgbtRed;

			temp[i][j].rgbtBlue = b;
			temp[i][j].rgbtGreen = g;
			temp[i][j].rgbtRed = r;
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int bx_sum = 0;
			int gx_sum = 0;
			int rx_sum = 0;

			int by_sum = 0;
			int gy_sum = 0;
			int ry_sum = 0;
			int count = 0;

			for (int k = i - 1; k <= i + 1; k++)
			{
				for (int l = j - 1; l <= j + 1; l++)
				{
					int shift_k = k - (i - 1);
					int shift_l = l - (j - 1);
					//printf("Abs: %i, %i, Semirel: %i, %i Rel: %i %i", i, j, k,
			//			   l, shift_k, shift_l);

					bool ib_top = k >= 0;
					bool ib_bottom = k < height;
					bool ib_left = l >= 0;
					bool ib_right = l < width;
					bool ib = ib_top && ib_bottom && ib_left && ib_right;

					if (ib)
					{
						bx_sum += image[k][l].rgbtBlue * gx[shift_k][shift_l];
						gx_sum += image[k][l].rgbtGreen * gx[shift_k][shift_l];
						rx_sum += image[k][l].rgbtRed * gx[shift_k][shift_l];

						by_sum += image[k][l].rgbtBlue * gy[shift_k][shift_l];
						gy_sum += image[k][l].rgbtGreen * gy[shift_k][shift_l];
						ry_sum += image[k][l].rgbtRed * gy[shift_k][shift_l];
						//printf("    ~~~~IB~~~\n");
					}
					else
					{
						//printf("\n");
					}
				}
			}

			int R = round(sqrt(pow(rx_sum, 2.0) + pow(ry_sum, 2.0)));
			int G = round(sqrt(pow(gx_sum, 2.0) + pow(gy_sum, 2.0)));
			int B = round(sqrt(pow(bx_sum, 2.0) + pow(by_sum, 2.0)));

			R = (R > 255) ? 255 : R;
			G = (G > 255) ? 255 : G;
			B = (B > 255) ? 255 : B;

			//printf("R_in %i, G_in %i, B_in %i\n", image[i][j].rgbtRed,
		//	   image[i][j].rgbtGreen, image[i][j].rgbtBlue);
			//printf("Rout %i, Gout %i, Bout %i\n\n", R, G, B);

			temp[i][j].rgbtBlue = B;
			temp[i][j].rgbtGreen = G;
			temp[i][j].rgbtRed = R;
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			image[i][j].rgbtBlue = (BYTE) temp[i][j].rgbtBlue;
			image[i][j].rgbtGreen = (BYTE) temp[i][j].rgbtGreen;
			image[i][j].rgbtRed = (BYTE) temp[i][j].rgbtRed;
		}
	}
	return;
}
