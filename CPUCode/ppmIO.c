/**
 * Document: MaxCompiler Training (maxcompiler-training.pdf)
 * Chapter: 2
 * Exercise Solution: 1
 * Summary:
 * 	 Library for loading and saving binary images as Portable Pixel
 *   Map files (.ppm). These functions will only reliably work with
 *   the images as provided for the exercises.
 */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "ppmIO.h"

/**
 * \brief Loads a .ppm image as 24-bit RGB pixels stored in 32-bit integers
 *
 * \param [in] filename Name of the .ppm file to load
 * \param [out] dest Buffer into which to write the image
 * \param [out] width Width of the image in pixels as read from the .ppm file
 * \param [out] height Height of the image in pixels as read from the .ppm file
 * \param [in] grayscale Whether to load the image in grayscale (1) or color (!=1)
 */
void loadImage(
	char *filename,
	int **dest,
	int *width,
	int *height,
	int grayscale)
{
	// hack to make the buffer big enough
	char buffer[200];
	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		printf("Error opening file %s.", filename);
		exit(1);
	}
	fgets(buffer, 200, file); // Type
	// assume no comment for now
	fscanf(file, "%d %d\n", width, height);
	fgets(buffer, 200, file); // Max intensity

	*dest = malloc((*width) * (*height) * sizeof(int));

	int pixelsRead = 0;
	int pixel = 0;
	int currComponent = 0;

	for (int i = 0; i < ((*width) * (*height) * 3); i++) {
		int v;
		int got = fscanf(file, "%d", &v);
		if (got == 0) {
			printf("Unexpected end of file after reading %d color values", i);
			exit(1);
		}
		switch (currComponent)
		{
			case 0:
				pixel = v;
				currComponent++;
				break;
			case 1:
				pixel = (pixel << 8) | (v & 0xFF);
				currComponent++;
				break;
			case 2:
				pixel = (pixel << 8) | (v & 0xFF);
				currComponent = 0;
				if (grayscale)
					pixel = ((pixel >> 16) & 0xff) * 3 / 10 + ((pixel >> 8)
						& 0xff) * 59 / 100 + ((pixel) & 0xff) * 11 / 100;
				(*dest)[pixelsRead] = pixel;
				pixelsRead++;
				break;
		}
	}
	fclose(file);
}

/**
 * \brief Writes an image as a color .ppm file
 *
 * \param [in] filename Name of the .ppm file to save
 * \param [in] data Buffer containing the image data
 * \param [in] width Width of the image in pixels in the buffer
 * \param [in] height Height of the image in pixels in the buffer
 * \param [in] grayscale Whether the image in the buffer is grayscale (1) or
 *             color (!=1)
 */
void writeImage(
		char *filename,
		int *data,
		int width,
		int height,
		int grayscale)
{
	FILE *file = fopen(filename, "w");

	fprintf(file, "P3\n");
	fprintf(file, "%d %d\n", width, height);
	fprintf(file, "255\n");

	for (int i = 0; i < width * height; i++) {
		if (grayscale) {
			//	if (data[i] > 255)
			//		printf("Warning: Out of range data. %d at pixel %d\n.", data[i], i);
			data[i] = data[i] > 255 ? 255 : data[i];
			//	if (data[i] < 0)
			//		printf("Warning: Data < 0. %d at pixel %d\n.", data[i], i);
			data[i] = data[i] < 0 ? 0 : data[i];

			for (int j = 0; j < 3; j++)
				fprintf(file, "%d\n", (int) data[i]);
		} else {
			fprintf(file, "%d\n", ((int) data[i]) >> 16);
			fprintf(file, "%d\n", (((int) data[i]) >> 8) & 0xff);
			fprintf(file, "%d\n", (((int) data[i])) & 0xff);
		}
	}
	fclose(file);
}
