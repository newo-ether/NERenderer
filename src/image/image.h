// image.h

#ifndef _IMAGE_H_ // _IMAGE_H_
#define _IMAGE_H_

#include <stdbool.h>

// Iterators for Image
#define ImageForeachPixel(_image, _x, _y, _ptr, _type) \
    for (*(_x) = 0, *(_y) = 0, _ptr = (_type *) ((_image)->image); \
         \
         _ptr < (_type *) ((char *)(_image)->image + (_image)->size); \
         \
         _ptr = (_type *) ((char *)_ptr + (_image)->channel * (_image)->channel_size), \
         *(_x) = ((int)((char *)_ptr - (char *)((_image)->image)) / ((_image)->channel * (_image)->channel_size)) % (_image)->width, \
         *(_y) = (int)((int)((char *)_ptr - (char *)((_image)->image)) / ((_image)->channel * (_image)->channel_size) / (_image)->width))

#ifndef _UINT8_ // _UINT8_
#define _UINT8_

typedef unsigned char uint8;

#endif // _UINT8_

typedef enum ImageFormat {
    PNG, JPG, BMP, EXR
} ImageFormat;


typedef enum ImageChannel {
    GREY=1, GREYALPHA=2, RGB=3, RGBA=4
} ImageChannel;


typedef enum ImageType {
    LDR, HDR
} ImageType;


typedef struct Image {
    void *image;
    int width;
    int height;
    enum ImageChannel channel;
    enum ImageType type;
    int channel_size;
    int size;
} Image;


// Image Constructor
Image ImageInit(int width, int height, ImageChannel channel, ImageType type);

// Image New Constructor
Image * ImageNew(int width, int height, ImageChannel channel, ImageType type);

// Image Constructor using array
Image ImageInitFromArray(void *array, int width, int height, ImageChannel channel, ImageType type);

// Image New Constructor using array
Image * ImageNewFromArray(void *array, int width, int height, ImageChannel channel, ImageType type);

// Image Constructor using filename
Image ImageInitFromFile(const char *filename, ImageChannel channel);

// Image New Constructor using filename
Image * ImageNewFromFile(const char *filename, ImageChannel channel);

// Image Copy Constructor
Image ImageCopy(Image image);

// Image New Copy Constructor
Image * ImageNewCopy(Image *image);

// Image Deconstructor
void ImageFree(Image *this, bool freeThis);


inline void * ImageGetArray(Image *this);

inline int ImageGetWidth(Image *this);

inline int ImageGetHeight(Image *this);

inline ImageChannel ImageGetChannel(Image *this);

inline ImageType ImageGetImageType(Image *this);

inline int ImageGetChannelSize(Image *this);

inline int ImageGetImageSize(Image *this);

void ImageSave(Image *this, const char *filename, ImageFormat format);

#endif // _IMAGE_H_
