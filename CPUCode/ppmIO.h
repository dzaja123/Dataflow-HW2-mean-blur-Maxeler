/**
 * Document: MaxCompiler Training (maxcompiler-training.pdf)
 * Chapter: 2
 * Exercise Solution: 1
 * Summary:
 * 	 Header file for loading and saving binary images as Portable
 *   Pixel Map files (.ppm). These functions will only reliably
 *   work with the images as provided for the exercises.
 */

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
	int grayscale);

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
		int grayscale);
