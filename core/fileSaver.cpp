
#include "fileSaver.h"
#include <stdio.h>
#include <string.h>
#include <csetjmp>

int fileSaver::write_JPEG(char * filename, JSAMPLE * image_buffer, int image_width, int image_height,int quality)
{
    std::cout << image_height << " " << image_width << "\n";
    // standard boilerplate code for jpg saving

    // structure contains the JPEG compression parameters and pointers to
    // working space
    jpeg_compress_struct cinfo;

    // jpeg error description
    jpeg_error_mgr jerr;

    FILE *outfile;              // target file
    JSAMPROW row_pointer[1];    // pointer to JSAMPLE row[s]
    int row_stride;             // physical row width in image buffer

    // setup error handler first
    cinfo.err = jpeg_std_error(&jerr);

    // initialize the JPEG compression object
    jpeg_create_compress(&cinfo);

    if ((outfile = fopen(filename, "wb")) == NULL)
    {
        std::cout << "can't open " << filename << "\n";
        return 1;
    }
    jpeg_stdio_dest(&cinfo, outfile);

    // setting up parameters for compression
    cinfo.image_width  = image_width;
    cinfo.image_height = image_height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, quality, TRUE);

    // start compressor

    jpeg_start_compress(&cinfo, TRUE);
    row_stride = image_width * 3;

    // write all lines
    while(cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    // finishing compression
    jpeg_finish_compress(&cinfo);
    fclose(outfile);

    // cleanup
    jpeg_destroy_compress(&cinfo);

    return 0;
}

struct my_error_mgr {
    struct jpeg_error_mgr pub;	/* "public" fields */

    jmp_buf setjmp_buffer;	/* for return to caller */
};

METHODDEF(void) my_error_exit(j_common_ptr cinfo)
{
    /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
    my_error_mgr * myerr = (my_error_mgr *) cinfo->err;

    // Always display the message
    (*cinfo->err->output_message)(cinfo);

    // return control to the setjmp point
    longjmp(myerr->setjmp_buffer, 1);
}


JSAMPLE* fileSaver::read_JPEG(char *filename, int &width, int &height) {
    jpeg_decompress_struct cinfo;
    my_error_mgr jerr;

    FILE *infile;       // source file
    JSAMPARRAY buffer;  // Output row buffer
    int row_stride;     // physical row width in output buffer
    JSAMPLE *buff;

    if ((infile = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "can't open %s\n",filename);
        return 0;
    }

    // Step 1. allocate and initialize JPEG decompression object
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    // Establish the setjmp return context for my_error_exit to use
    if (setjmp(jerr.setjmp_buffer))
    {
        // If we get here, the JPEG code has signaled an error
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        return 0;
    }

    // Now we can initialize the JPEG decompression object
    jpeg_create_decompress(&cinfo);

    // Step 2. specify data source
    jpeg_stdio_src(&cinfo, infile);

    // Step 3. read file parameters with jpeg_read_header()
    (void) jpeg_read_header(&cinfo, TRUE);
    /* We can ignore the return value from jpeg_read_header since
     *   (a) suspension is not possible with the stdio data source, and
     *   (b) we passed TRUE to reject a tables-only JPEG file as an error.
     * See libjpeg.txt for more info.
     */
     /* Step 4: set parameters for decompression */

    /* In this example, we don't need to change any of the defaults set by
     * jpeg_read_header(), so we do nothing here.
     */
    /* Step 5: Start decompressor */

    (void) jpeg_start_decompress(&cinfo);
    /* We can ignore the return value since suspension is not possible
     * with the stdio data source.
     */

    /* We may need to do some setup of our own at this point before reading
     * the data.  After jpeg_start_decompress() we have the correct scaled
     * output image dimensions available, as well as the output colormap
     * if we asked for color quantization.
     * In this example, we need to make an output work buffer of the right size.
     */
     /* JSAMPLEs per row in output buffer */
     row_stride = cinfo.output_width * cinfo.output_components;

     /* Make a one-row-high sample array that will go away when done with image */
     buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

     buff = new JSAMPLE[cinfo.image_width * cinfo.image_height * 3];
     width  = cinfo.image_width;
     height = cinfo.image_height;
     int i = 0;

     while (cinfo.output_scanline < cinfo.output_height)
     {
        /* jpeg_read_scanlines expects an array of pointers to scanlines.
         * Here the array is only one element long, but you could ask for
         * more than one scanline at a time if that's more convenient.
         */
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        /* Assume put_scanline_someplace wants a pointer and sample count. */
        memcpy(buff + i * row_stride, buffer[0], row_stride);
        i += 1;
     }

     (void) jpeg_finish_decompress(&cinfo);
     jpeg_destroy_decompress(&cinfo);
     fclose(infile);
     return buff;
}
