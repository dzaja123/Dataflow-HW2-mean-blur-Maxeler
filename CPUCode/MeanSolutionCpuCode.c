/**
 * Document: MaxCompiler Training (maxcompiler-training.pdf)
 * Chapter: 2
 * Exercise Solution: 1
 * Summary:
 * 	 Performs a mean blur on an image.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include <MaxSLiCInterface.h>

#include "ppmIO.h"

int main(void)
{
	printf("Loading image.\n");
	int32_t *inImage;
	int width = 0, height = 0;
	loadImage("lena.ppm", &inImage, &width, &height, 1);

	int dataSize = width * height * sizeof(int32_t);
	// Allocate a buffer for the output image
	int32_t *outImage = malloc(dataSize);

	printf("Running Kernel.\n");
	MeanSolution(width * height, inImage, outImage);

	printf("Saving image.\n");
	writeImage("lena_mean.ppm", outImage, width, height, 1);

	printf("Exiting\n");
	return 0;
}
