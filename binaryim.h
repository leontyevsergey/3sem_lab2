#include<iostream>
#include<cstdio>
#include<stdexcept>
using namespace std;

template <typename T>
class binaryimage {
private:
	T** image;
	size_t width, height;
public:
	
	binaryimage();
	binaryimage(const size_t a_width, const size_t a_height);
	binaryimage(const binaryimage& image_copy);
	~binaryimage();
	T operator()(const size_t a_width, const size_t a_height) const;
	T& operator()(const size_t a_width, const size_t a_height);
	binaryimage operator =(const binaryimage& a_image);
	binaryimage operator *(const binaryimage& a_image) const;
	binaryimage operator +(const binaryimage& a_image) const;
	binaryimage operator *(const T a_b) const;
	binaryimage operator +(const T a_b) const;
	//binaryimage operator !() const;
	bool operator ==(const binaryimage& a_image) const;
	double ratio() const;
	//friend ostream& operator <<(std::ostream& os, const binaryimage& a_image);
	size_t get_width() const;
	size_t get_height() const;
};



template <typename T>
binaryimage<T>::binaryimage() : image(nullptr), width(0), height(0) {}

template <typename T>
binaryimage<T>::binaryimage(const size_t a_width, const size_t a_height) {
	if (a_width == 0 || a_height == 0) {
		throw std::out_of_range( "The number of rows and columns should be >0" );
	}
	width = a_width;
	height = a_height;
	image = new T * [width];
	for (size_t i = 0; i < width; ++i) {
		image[i] = new T[height];
		for (size_t j = 0; j < height; ++j) {
			image[i][j] = NULL;
		}
	}
}

template <typename T>
binaryimage<T>::binaryimage(const binaryimage& image_copy) {
	width = image_copy.width;
	height = image_copy.height;
	image = new T * [width];
	for (size_t i = 0; i < width; i++)
	{
		image[i] = new T[height];
		for (size_t j = 0; j < height; j++)
		{
			image[i][j] = image_copy.image[i][j];
		}
	}
}

template <typename T>
T binaryimage<T>::operator()(const size_t a_width, const size_t a_height) const {
	if (a_width > width || a_height > height)
		throw std::out_of_range( "Incorrect coordinates" );
	return image[a_width][a_height];
}

template <typename T>
T& binaryimage<T>::operator()(const size_t a_width, const size_t a_height) {
	if (a_width > width || a_height > height)
		throw std::out_of_range( "Incorrect coordinates" );
	return image[a_width][a_height];
}

template <typename T>
binaryimage<T> binaryimage<T>::operator =(const binaryimage& a_image) {
	width = a_image.width;
	height = a_image.height;
	if (width != a_image.width || height != a_image.height) {
		if (image) {
			for (size_t i = 0; i < width; ++i) {
				delete[] image[i];
			}
		}
		delete[] image;
		image = new T * [width];
		for (size_t i = 0; i < width; ++i) {
			image[i] = new T[height];
		}
	}
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			image[i][j] = a_image.image[i][j];
			a_image.image[i][j] = image[i][j];
		}
	}
	return a_image;
}

template <typename T>
binaryimage<T> binaryimage<T>::operator*(const binaryimage& a_image) const {
	size_t x_min = 0, y_min = 0, result_width, result_height;
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
	binaryimage<T> result_image(result_width, result_height);
	for (size_t i = 0; i < x_min; ++i) {
		for (size_t j = 0; j < y_min; ++j) {
			result_image.image[i][j] = image[i][j] * a_image.image[i][j];
		}
	}
	if (width > a_image.width || width < a_image.width) {
		for (size_t i = x_min; i < result_width; ++i) {
			for (size_t j = 0; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	if (height > a_image.height || height < a_image.height) {
		for (size_t i = 0; i < x_min; ++i) {
			for (size_t j = y_min; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	return result_image;
}

template <typename T>
binaryimage<T> binaryimage<T>::operator +(const binaryimage& a_image) const {
	size_t x_min = 0, y_min = 0, result_width, result_height;
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
	binaryimage<T> result_image(result_width, result_height);
	for (size_t i = 0; i < x_min; ++i) {
		for (size_t j = 0; j < y_min; ++j) {
			result_image.image[i][j] = image[i][j] + a_image.image[i][j];
		}
	}
	if (width > a_image.width || width < a_image.width) {
		for (size_t i = x_min; i < result_width; ++i) {
			for (size_t j = 0; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	if (height > a_image.height || height < a_image.height) {
		for (size_t i = 0; i < x_min; ++i) {
			for (size_t j = y_min; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}

	return result_image;
}

template <typename T>
binaryimage<T> binaryimage<T>::operator *(const T a_b) const {
	binaryimage<T> result_image(width, height);
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			result_image.image[i][j] = image[i][j] * a_b;
		}
	}
	return result_image;
}

template <typename T>
binaryimage<T> binaryimage<T>::operator +(const T a_b) const {
	binaryimage<T> result_image(width, height);
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			result_image.image[i][j] = image[i][j] + a_b;
		}
	}
	return result_image;
}

/*template <typename T>
binaryimage<T> binaryimage<T>::operator!() const {
	binaryimage<T> result_image(width, height);
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			if (image[i][j] == True)
				result_image.image[i][j] = False;
			else
				result_image.image[i][j] = True;
		}
	}
	return result_image;
}*/

template <typename T>
bool binaryimage<T>::operator ==(const binaryimage& a_image) const {
	if (width == a_image.width && height == a_image.height) {
		for (size_t i = 0; i < width; ++i) {
			for (size_t j = 0; j < height; ++j) {
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

template <typename T>
ostream& operator <<(ostream& os, const binaryimage<T>& a_image) {
	for (size_t i = 0; i < a_image.get_width(); ++i) {
		for (size_t j = 0; j < a_image.get_height(); ++j) {
			//if (a_image(i, j))
			//	os << "\t" << a_image(i, j);
			//else
				os << "\t" << a_image(i, j);
		}
		os << endl;
	}
	return os;
}

template <typename T>
double binaryimage<T>::ratio() const {
	double temp = 0, d_width = width, d_height = height;
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			if (image[i][j])
				temp++;
		}
	}
	return(temp / (d_width * d_height));
}

template <typename T>
size_t binaryimage<T>::get_width() const {
	return width;
}

template <typename T>
size_t binaryimage<T>::get_height() const {
	return height;
}

template <typename T>
binaryimage<T>::~binaryimage<T>() {
	if (image) {
		for (size_t i = 0; i < width; ++i) {
			delete[] image[i];
		}
	}
	delete[] image;
}