#ifndef DEF_MATRIX
#define DEF_MATRIX
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

template <class T>
class Matrix{
    private:
        std::vector<std::vector<T> > array;
        int height;
        int width;

    public:
        Matrix<T>(int height, int width);
        Matrix<T>(std::vector<std::vector<T> > const &array);
        Matrix<T>();

        int getHeight() const;
        int getWidth() const;

        Matrix<T> multiply(const Matrix<T>& m) const;
        Matrix<T> multiply(const T& value) const;

        void fill(const T& value);
        void putFromInput();
        void putFromFile(int h, int w, string filename);
        void put(int h, int w, const T& value);
        T get(int h, int w) const;

        void print(std::ostream &flux) const;

        bool operator==(const Matrix<T>& m);
        bool operator!=(const Matrix<T>& m);
        Matrix<T> operator*=(const Matrix<T>& m);
        Matrix<T> operator*=(const T &m);
        T& operator()(int y, int x);
};

template <class T> Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b);
template <class T> Matrix<T> operator*(const T &b, const Matrix<T>& a);

#endif

template <class T>
Matrix<T>::Matrix(int height, int width){
    this->height = height;
    this->width = width;
    this->array = std::vector<std::vector<T> >(height, std::vector<T>(width));
}

template <class T>
Matrix<T>::Matrix(std::vector<std::vector<T> > const &array){
    if(array.size()==0)
        throw std::invalid_argument("Size of array must be greater than 0.");

    this->height = array.size();
    this->width = array[0].size();
    this->array = array;
}

template <class T>
Matrix<T>::Matrix(){
    height = 0;
    width = 0;
}

template <class T>
int Matrix<T>::getHeight() const{
    return height;
}

template <class T>
int Matrix<T>::getWidth() const{
    return width;
}

template <class T>
void Matrix<T>::fill(const T& value){
    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            array[i][j] = value;
        }
    }
}

template <class T>
Matrix<T> Matrix<T>::multiply(const T& value) const{
    int a;
    // Matrix result(this->getHeight(), this->getHeight());
    // for (int i=0 ; i<height ; i++){
    //     for (int j=0 ; j<width ; j++){
    //         result.array[i][j] *= value;
    //     }
    // }
    // int s;
    // for (int i = 0; i < this->getHeight(); i++) {
    // for (int m = 0; m < value->getHeight(); m++) {
    // for (int j = 0; j < this->getHeight(); j++) {
    // s = s + this->array[i][j] * value[j][m];
    // }
    // result[i][m] = s;
    // s = 0;
    // }
    // }

    // return result;
}

template <class T>
void Matrix<T>::put(int h, int w, const T& value){
    if(!(h>=0 && h<height && w>=0 && w<width))
        throw std::invalid_argument("Index out of bounds.");

    array[h][w] = value;
}

template <class T>
void Matrix<T>::putFromFile(int h, int w, string filename){
    ifstream fin(filename);
    if (fin.is_open()) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                fin >> array[i][j];
            }
        }
    }
}

template <class T>
T Matrix<T>::get(int h, int w) const{
    if(!(h>=0 && h<height && w>=0 && w<width))
        throw std::invalid_argument("Index out of bounds.");

    return array[h][w];
}


template <class T>
void Matrix<T>::print(std::ostream &flux) const{
    int maxLength[width];
    std::stringstream ss;

    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            ss << array[i][j];
            if(maxLength[j] < ss.str().size()){
                maxLength[j] = ss.str().size();
            }
            ss.str(std::string());
        }
    }

    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            flux << array[i][j];
            ss << array[i][j];
            for (int k=0 ; k<maxLength[j]-ss.str().size()+1 ; k++){
                flux << " ";
            }
            ss.str(std::string());
        }
        flux << std::endl;
    }
}

template <class T>
bool Matrix<T>::operator==(const Matrix& m){
    if(height==m.height && width==m.width){
        for (int i=0 ; i<height ; i++){
            for (int j=0 ; j<width ; j++){
                if(array[i][j]!=m.array[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

template <class T>
T& Matrix<T>::operator()(int y, int x){
    if(!(y>=0 && y<height && x>=0 && x<width))
        throw std::invalid_argument("Index out of bounds.");
    return array[y][x];
}

template <class T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b){
    return a.multiply(b);
}

template <class T>
Matrix<T> operator*(const T &b, const Matrix<T>& a){
    return a.multiply(b);
}