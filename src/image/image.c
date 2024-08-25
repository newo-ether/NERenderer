// image.c

#include "../config/config.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../stb/stb_image_write.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

#include "image.h"

Image ImageInit(int width, int height, ImageChannel channel, ImageType type) {
    Image image;
    int channel_size;
    channel_size = (type == LDR ? 1 : 4);
    image.image = (void *)calloc(width * height * channel, channel_size);
    image.width = width;
    image.height = height;
    image.channel = channel;
    image.type = type;
    image.channel_size = channel_size;
    image.size = width * height * channel * channel_size;
    return image;
}

Image * ImageNew(int width, int height, ImageChannel channel, ImageType type) {
    Image *image;
    int channel_size;
    channel_size = (type == LDR ? 1 : 4);
    image = (Image *)malloc(sizeof(Image));
    image->image = (void *)calloc(width * height * channel, channel_size);
    image->width = width;
    image->height = height;
    image->channel = channel;
    image->type = type;
    image->channel_size = channel_size;
    image->size = width * height * channel * channel_size;
    return image;
}

Image ImageInitFromArray(void *array, int width, int height, ImageChannel channel, ImageType type) {
    Image image;
    image.image = array;
    image.width = width;
    image.height = height;
    image.channel = channel;
    image.type = type;
    image.channel_size = (type == LDR ? 1 : 4);
    image.size = width * height * channel * image.channel_size;
    return image;
}

Image * ImageNewFromArray(void *array, int width, int height, ImageChannel channel, ImageType type) {
    Image *image;
    image = (Image *)malloc(sizeof(Image));
    image->image = array;
    image->width = width;
    image->height = height;
    image->channel = channel;
    image->type = type;
    image->channel_size = (type == LDR ? 1 : 4);
    image->size = width * height * channel * image->channel_size;
    return image;
}

Image ImageInitFromFile(const char *filename, ImageChannel channel) {
    Image image;
    void *array;
    int width, height, original_channel;
    ImageType type;
    type = (stbi_is_hdr(filename) ? HDR : LDR);
    array = stbi_load(filename, &width, &height, &original_channel, channel);
    image = ImageInitFromArray(array, width, height, channel, type);
    return image;
}

Image * ImageNewFromFile(const char *filename, ImageChannel channel) {
    Image *image;
    void *array;
    int width, height, original_channel;
    ImageType type;
    type = (stbi_is_hdr(filename) ? HDR : LDR);
    array = stbi_load(filename, &width, &height, &original_channel, channel);
    image = ImageNewFromArray(array, width, height, channel, type);
    return image;
}

Image ImageCopy(Image image) {
    Image image_new;
    image_new = ImageInit(image.width, image.height, image.channel, image.type);
    memcpy(image_new.image, image.image, image.size);
    return image_new;
}

Image * ImageNewCopy(Image *image) {
    Image *image_new;
    image_new = ImageNew(image->width, image->height, image->channel, image->type);
    memcpy(image_new->image, image->image, image->size);
    return image_new;
}

void ImageFree(Image *this, bool freeThis) {
    if (this == NULL) {
        return;
    }
    if (this->image != NULL) {
        free(this->image);
    }
    if (freeThis) {
        free(this);
    }
}

inline void * ImageGetArray(Image *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return NULL;
    }
#endif
    return this->image;
}

inline int ImageGetWidth(Image *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return 0;
    }
#endif
    return this->width;
}

inline int ImageGetHeight(Image *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return 0;
    }
#endif
    return this->height;
}

inline ImageChannel ImageGetChannel(Image *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return 0;
    }
#endif
    return this->channel;
}

inline ImageType ImageGetImageType(Image *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return 0;
    }
#endif
    return this->type;
}

inline int ImageGetChannelSize(Image *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return 0;
    }
#endif
    return this->channel_size;
}

inline int ImageGetImageSize(Image *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return 0;
    }
#endif
    return this->size;
}

void ImageSave(Image *this, const char *filename, ImageFormat format) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    if (format == PNG) {
        if (this->type != LDR) {
            assert(false);
            return;
        }
        stbi_write_png(filename, this->width, this->height, this->channel, this->image, this->width * this->channel);
    }
    else if (format == JPG) {
        if (this->type != LDR) {
            assert(false);
            return;
        }
        stbi_write_jpg(filename, this->width, this->height, this->channel, this->image, 100);
    }
    else if (format == BMP) {
        if (this->type != LDR) {
            assert(false);
            return;
        }
        stbi_write_bmp(filename, this->width, this->height, this->channel, this->image);
    }
    else if (format == EXR) {
        if (this->type != HDR) {
            assert(false);
            return;
        }
        stbi_write_hdr(filename, this->width, this->height, this->channel, (float *)this->image);
    }
}
