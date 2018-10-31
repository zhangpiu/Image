# Overview
This is a PPM encoder and decoder written by C++. The formats of PPM(Portable PixMap), PGM(Portable GreyMap), PBM(Portable BitMap) are a convenient(simple) method of saving image data. Please refer http://paulbourke.net/dataformats/ppm/ for more information.

# Example
A `boxBlur` function has been implenmented based on the simple PPM reader and `Image` struct.
``` bash
$ g++ --std=c++11 main.cpp -o main
$ ./main zju.ppm out.ppm 17
```

| original   | blurred       |
| ---------- | :-----------: |
| ![](https://github.com/zhangpiu/PPM-Image/blob/master/images/zju.jpg?raw=true)      | ![](https://github.com/zhangpiu/PPM-Image/blob/master/images/out.jpg?raw=true)         |
