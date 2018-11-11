Image Preprocessing Processing

Python 3 program intended for converting color images of different file types to a comma delimited text file containing the pixel values converted to grayscale and normalized from 0-255 to 0-1 with a decimal precision of three.  The program depends on the Pillow image processing library.  

The program expects command line arguments for the input file name, the image, and the output file name, the text file to which the normalized pixel values are to be written.  If the input file name is not provide the program terminates, and if the output file name is not provide a default name of "output" is given.  Additionally, the flags "-s" and "-r", in that order, can optionally be supplied to the program as command line arguments to use the Pillow library to show the converted image and to print the raw normalized values to the screen.

To execute (using the same image provided "image.jpg" and using both flags):

    python imageProcessor.py image.jpg normalizedValues.txt -s -r

