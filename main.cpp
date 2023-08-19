#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <cstring>

using namespace std;

template <typename T>
class Image {
    private:
        T *pixels = nullptr;
        int m_width = -1;
        int m_height = -1;
    public:
        Image() {}
        
        Image(int width, int height) : m_width(width), m_height(height) {
            assert(m_width > 0 && m_height > 0);
            pixels = new T[m_width * m_height];
            memset(pixels, 0, m_width * m_height * sizeof(T));
        }
        
        virtual ~Image() {
            delete[] pixels;
        }
        
        //copy constructor
        Image(const Image& other) : m_width(other.m_width), m_height(other.m_height) {
            assert(m_width > 0 && m_height > 0);
            pixels = new T[m_width * m_height];
            memcpy(pixels, other.pixels, m_width * m_height * sizeof(T));
        }
        
        //copy assignment constructor
        Image& operator= (const Image& other) {
            if (this == &other) return *this;
            
            delete[] pixels;
            
            m_width = other.m_width;
            m_height = other.m_height;
            pixels = new T[m_width * m_height];
            memcpy(pixels, other.pixels, m_width * m_height * sizeof(T));
            
            return *this;
        }
        
        //move constructor
        Image(Image&& other) : pixels(nullptr), m_width(other.m_width), m_height(other.m_height) {
            assert(m_width > 0 && m_height > 0);
            delete[] pixels;
            
            m_width = other.m_width;
            m_height = other.m_height;
            pixels = other.pixels;
            
            other.pixels = nullptr;
            other.m_width = -1;
            other.m_height = -1;
        }
        
        //move assignment constructor
        Image& operator= (const Image&& other) {
            if (this == &other) return *this;
            
            delete[] pixels;
            
            m_width = other.m_width;
            m_height = other.m_height;
            pixels = other.pixels;
            
            other.pixels = nullptr;
            other.m_width = -1;
            other.m_height = -1;
            
            return *this;
        }
        
        virtual T getPixel(int x, int y) {
            assert(m_width > 0 && m_height > 0);
            return pixels[y * m_width + x];
        }
        
        virtual void setPixel(int x, int y, T value) {
            assert(m_width > 0 && m_height > 0);
            pixels[y * m_width + x] = value;
        }

        virtual void fillPixels(T value) {
            for (int i = 0; i < m_width; i++) {
                for (int j = 0; j < m_height; j++) {
                    pixels[i * m_width + j] = value;
                }
            }
        }

        virtual void fillPixels(int x1, int y1, int x2, int y2, T value) {
            assert(x1 < x2 && y1 < y2);
            for (int i = x1; i < x2; i++) {
                for (int j = y1; j < y2; j++) {
                    pixels[i * m_width + j] = value;
                }
            }
        }
        
        virtual void show() {
            for (int i = 0; i < m_width; i++) {
                for (int j = 0; j < m_height; j++) {
                    cout << pixels[i * m_width + j] << " ";
                }
                cout << endl;
            }
        }
        
        int getWidth() {
            return m_width;
        }
        
        int getHeight() {
            return m_height;
        }
};

int main()
{
    Image<int> img(10, 10);
    img.fillPixels(0, 0, 5, 5, 23);
    img.show();
    return 0;
}
