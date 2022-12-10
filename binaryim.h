#include<iostream>
#include<cstdio>
#include<stdexcept>
using namespace std;

template <typename T, T True, T False>
class binaryimage {
private:
	T** image;
	int width, height;
public:
	
	binaryimage();
	binaryimage(const int a_width, const int a_height);
	binaryimage(const binaryimage& image_copy);
	~binaryimage();
	T operator()(const int a_width, const int a_height) const;
	T& operator()(const int a_width, const int a_height);
	binaryimage operator =(const binaryimage& a_image);
	binaryimage operator *(const binaryimage& a_image) const;
	binaryimage operator +(const binaryimage& a_image) const;
	binaryimage operator *(const T a_b) const;
	binaryimage operator +(const T a_b) const;
	binaryimage operator !() const;
	bool operator ==(const binaryimage& a_image) const;
	double ratio() const;
	//friend ostream& operator <<(std::ostream& os, const binaryimage& a_image);
	int get_width() const;
	int get_height() const;
};



template <typename T, T True, T False>
binaryimage<T, True, False>::binaryimage() : image(nullptr), width(0), height(0) {}

template <typename T, T True, T False>
binaryimage<T, True, False>::binaryimage(const int a_width, const int a_height) {
	if (a_width <= 0 || a_height <= 0) {
		throw std::out_of_range( "The number of rows and columns should be >0" );
	}
	width = a_width;
	height = a_height;
	image = new T * [width];
	for (int i = 0; i < width; ++i) {
		image[i] = new T[height];
		for (int j = 0; j < height; ++j) {
			image[i][j] = False;
		}
	}
}

template <typename T, T True, T False>
binaryimage<T, True, False>::binaryimage(const binaryimage& image_copy) {
	width = image_copy.width;
	height = image_copy.height;
	image = new T * [width];
	for (int i = 0; i < width; i++)
	{
		image[i] = new T[height];
		for (int j = 0; j < height; j++)
		{
			image[i][j] = image_copy.image[i][j];
		}
	}
}

template <typename T, T True, T False>
T binaryimage<T, True, False>::operator()(const int a_width, const int a_height) const {
	if (a_width > width || a_height > height || a_height < 0 || a_width < 0)
		throw std::out_of_range( "Incorrect coordinates" );
	return image[a_width][a_height];
}

template <typename T, T True, T False>
T& binaryimage<T, True, False>::operator()(const int a_width, const int a_height) {
	if (a_width > width || a_height > height || a_height < 0 || a_width < 0)
		throw std::out_of_range( "Incorrect coordinates" );
	return image[a_width][a_height];
}

template <typename T, T True, T False>
binaryimage<T, True, False> binaryimage<T, True, False>::operator =(const binaryimage& a_image) {
	width = a_image.width;
	height = a_image.height;
	if (width != a_image.width || height != a_image.height) {
		if (image) {
			for (int i = 0; i < width; ++i) {
				delete[] image[i];
			}
		}
		delete[] image;
		image = new T * [width];
		for (int i = 0; i < width; ++i) {
			image[i] = new T[height];
		}
	}
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			image[i][j] = a_image.image[i][j];
			a_image.image[i][j] = image[i][j];
		}
	}
	return a_image;
}

template <typename T, T True, T False>
binaryimage<T, True, False> binaryimage<T, True, False>::operator*(const binaryimage& a_image) const {
	int x_min = 0, y_min = 0, result_width, result_height;
	if (width > a_image.width) {
		result_width = width;
		x_min = a_image.width;
	}
	else
	{
		result_width = a_image.width;
		x_min = width;
	}
	if (height > a_image.height) {
		result_height = height;
		y_min = a_image.height;
	}
	else
	{
		result_height = a_image.height;
		y_min = height;
	}
	binaryimage<T, True, False> result_image(result_width, result_height);
	for (int i = 0; i < x_min; ++i) {
		for (int j = 0; j < y_min; ++j) {
			result_image.image[i][j] = image[i][j] * a_image.image[i][j];
		}
	}
	if (width > a_image.width || width < a_image.width) {
		for (int i = x_min; i < result_width; ++i) {
			for (int j = 0; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	if (height > a_image.height || height < a_image.height) {
		for (int i = 0; i < x_min; ++i) {
			for (int j = y_min; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	return result_image;
}

template <typename T, T True, T False>
binaryimage<T, True, False> binaryimage<T, True, False>::operator +(const binaryimage& a_image) const {
	int x_min = 0, y_min = 0, result_width, result_height;
	if (width > a_image.width) {
		result_width = width;
		x_min = a_image.width;
	}
	else
	{
		result_width = a_image.width;
		x_min = width;
	}
	if (height > a_image.height) {
		result_height = height;
		y_min = a_image.height;
	}
	else
	{
		result_height = a_image.height;
		y_min = height;
	}
	binaryimage<T, True, False> result_image(result_width, result_height);
	for (int i = 0; i < x_min; ++i) {
		for (int j = 0; j < y_min; ++j) {
			result_image.image[i][j] = image[i][j] + a_image.image[i][j];
		}
	}
	if (width > a_image.width || width < a_image.width) {
		for (int i = x_min; i < result_width; ++i) {
			for (int j = 0; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	if (height > a_image.height || height < a_image.height) {
		for (int i = 0; i < x_min; ++i) {
			for (int j = y_min; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}

	return result_image;
}

template <typename T, T True, T False>
binaryimage<T, True, False> binaryimage<T, True, False>::operator *(const T a_b) const {
	binaryimage<T, True, False> result_image(width, height);
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			result_image.image[i][j] = image[i][j] * a_b;
		}
	}
	return result_image;
}

template <typename T, T True, T False>
binaryimage<T, True, False> binaryimage<T, True, False>::operator +(const T a_b) const {
	binaryimage<T, True, False> result_image(width, height);
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			result_image.image[i][j] = image[i][j] + a_b;
		}
	}
	return result_image;
}

template <typename T, T True, T False>
binaryimage<T, True, False> binaryimage<T, True, False>::operator!() const {
	binaryimage<T, True, False> result_image(width, height);
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (image[i][j] == True)
				result_image.image[i][j] = False;
			else
				result_image.image[i][j] = True;
		}
	}
	return result_image;
}

template <typename T, T True, T False>
bool binaryimage<T, True, False>::operator ==(const binaryimage& a_image) const {
	if (width == a_image.width && height == a_image.height) {
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				if (image[i][j] == a_image.image[i][j])
					continue;
				else
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T, T True, T False>
ostream& operator <<(ostream& os, const binaryimage<T, True, False>& a_image) {
	for (int i = 0; i < a_image.get_width(); ++i) {
		for (int j = 0; j < a_image.get_height(); ++j) {
			if (a_image(i, j) == True)
				os << "\t1";
			else
				os << "\t.";
		}
		os << endl;
	}
	return os;
}

template <typename T, T True, T False>
double binaryimage<T, True, False>::ratio() const {
	double temp = 0, d_width = width, d_height = height;
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (image[i][j])
				temp++;
		}
	}
	return(temp / (d_width * d_height));
}

template <typename T, T True, T False>
int binaryimage<T, True, False>::get_width() const {
	return width;
}

template <typename T, T True, T False>
int binaryimage<T, True, False>::get_height() const {
	return height;
}

template <typename T, T True, T False>
binaryimage<T, True, False>::~binaryimage<T, True, False>() {
	if (image) {
		for (int i = 0; i < width; ++i) {
			delete[] image[i];
		}
	}
	delete[] image;
}