/* -------------------------------------------------------------------------- *\
| --------------- PPM -----------------------
| @description
|
| @author: vodka
|
| @version: 1.0
|
| @datetime: 2017.07.20
|
|
\* ---------------------------------------------------------------------------*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <memory>

using namespace std;

typedef unsigned char uchar;

struct Image {
	int width;
	int height;
	int channel;
	vector<uchar> data;

	Image(int height, int width, int channel = 3, const vector<uchar>& data = vector<uchar>()) 
		: height(height)
		, width(width)
		, channel(channel)
		, data(data) {
		if (this->data.size() != height * width * channel) 
			this->data.resize(height * width * channel);
	}

	uchar& operator () (int i, int j, int k) {
		return data[k + j * channel + i * width * channel];
	}

	const uchar& operator () (int i, int j, int k) const {
		return data[k + j * channel + i * width * channel];
	}
};

void save(const Image& image, const string& filename) {
	int w = image.width;
	int h = image.height;

	FILE* file = fopen(filename.c_str(), "wb");
	fprintf(file, "P6\n%d %d\n255\n", w, h);

	fwrite(&image.data[0], sizeof(uchar), image.data.size(), file);
	fclose(file);
}

Image open(const string& filename) {
	FILE* file = fopen(filename.c_str(), "rb");

	int w, h, l;
	fscanf(file, "P6\n%d %d\n%d\n", &w, &h, &l);

	vector<uchar> data(w * h * 3);

	fread(&data[0], sizeof(uchar), data.size(), file);
	fclose(file);

	return Image(h, w, 3, data);
}

void boxBlur(const Image& input, Image& output, int radius) {
	const int width = input.width;
	const int height = input.height;
	int rr = (2 * radius + 1) * (2 * radius + 1);
	
	auto clamp = [](int num, int low, int high) { return num < low ? low : (num > high ? high : num); };

	for (int i = 0; i < input.height; ++i) {
		for (int j = 0; j < input.width; ++j) {
			double rgb[3] = { 0, 0, 0 };

			for (int di = -radius; di <= radius; ++di) {
				for (int dj = -radius; dj <= radius; ++dj) {
					int ii = clamp(i + di, 0, height - 1);
					int jj = clamp(j + dj, 0, width - 1);

					rgb[0] += input(ii, jj, 0);
					rgb[1] += input(ii, jj, 1);
					rgb[2] += input(ii, jj, 2);
				}
			}

			output(i, j, 0) = uchar(rgb[0] / rr);
			output(i, j, 1) = uchar(rgb[1] / rr);
			output(i, j, 2) = uchar(rgb[2] / rr);
		}
	}
}

int main() {
	auto img = open("E:/zju.ppm");
	Image blurImage(img.height, img.width);

	int r = 17;
	boxBlur(img, blurImage, r);
	save(blurImage, "E:/out.ppm");

	return 0;
}