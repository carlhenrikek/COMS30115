# COMS30115

This is the repository for the Computer Graphics unit COMS30115 at the University of Bristol.

## Dependencies

* [GLM 0.9.7](https://glm.g-truc.net/0.9.7/index.html)
* [SDL 2.0.7](https://www.libsdl.org/download-2.0.php)

## Using CMake

If you don't want to use the provided Makefile, or you're running on Windows you
can use CMake files provided. Make a build folder `build` and cd into it then
run `cmake ..`, finally run `make` to build the project, you should find the
executables in `build/starfield/starfield`.

```bash
$ cd Labs
$ mkdir build
$ cmake ..
$ make
$ ./build/starfield/starfield
```
