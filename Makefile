# Makefile

CC = gcc
CFLAGS = -Wall -fgnu89-inline
LINK = -lm
BINDIR = build

all: main

test: test_image \
	  test_camera \
	  test_matrix \
	  test_transform \
	  test_array3 \
	  test_list

main: src/base/camera.o \
	  src/base/intersectinfo.o \
	  src/base/list.o \
	  src/base/object.o \
	  src/base/scene.o \
	  src/base/spectrum.o \
	  src/base/transform.o \
	  src/base/matrix.o \
	  src/base/vector3.o \
	  src/base/point3.o \
	  src/base/utils.o \
	  src/base/ray.o \
	  src/base/sampler.o \
	  src/camera/perspectivecamera.o \
	  src/image/image.o \
	  src/light/pointlight.o \
	  src/light/arealight.o \
	  src/light/infinitearealight.o \
	  src/material/lambertian.o \
	  src/renderer/pathtracer.o \
	  src/shape/sphere.o \
	  src/main/main.o
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LINK) $^ -o $(BINDIR)/$@

test_image: src/image/image.o \
			src/test/test_image.o
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LINK) $^ -o $(BINDIR)/$@

test_camera: src/base/camera.o \
	         src/base/transform.o \
			 src/base/matrix.o \
	    	 src/base/vector3.o \
			 src/base/point3.o \
			 src/base/utils.o \
			 src/base/ray.o \
			 src/base/sampler.o \
			 src/camera/perspectivecamera.o \
			 src/test/test_camera.o
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LINK) $^ -o $(BINDIR)/$@

test_matrix: src/base/matrix.o \
	  		 src/test/test_matrix.o
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LINK) $^ -o $(BINDIR)/$@

test_transform: src/base/transform.o \
                src/base/matrix.o \
                src/base/vector3.o \
                src/base/point3.o \
                src/base/utils.o \
                src/base/ray.o \
                src/test/test_transform.o
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LINK) $^ -o $(BINDIR)/$@

test_array3: src/base/vector3.o \
             src/base/point3.o \
             src/base/utils.o \
             src/test/test_array3.o
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LINK) $^ -o $(BINDIR)/$@

test_list: src/base/list.o \
		   src/test/test_list.o
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LINK) $^ -o $(BINDIR)/$@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -rf src/**/*.o
