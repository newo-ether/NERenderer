// test_image.c

#include <stdio.h>

#include "../image/image.h"

int main() {
    Image img;
    int i, j;
    uint8 *pixel;
    img = ImageInit(1920, 1080, RGB, LDR);
    ImageForeachPixel(&img, &i, &j, pixel, uint8) {
        pixel[0] = (uint8)((float)i / img.width * 256);
        pixel[1] = (uint8)((float)j / img.height * 256);
        pixel[2] = (uint8)(256 - ((float)i / img.width) * ((float)j / img.height) * 256);
    }
    ImageSave(&img, "test.png", PNG);
    ImageFree(&img, false);
    return 0;
}
