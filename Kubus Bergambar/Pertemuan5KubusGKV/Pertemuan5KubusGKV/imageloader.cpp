//
//  main.cpp
//
//
//  
//

#include <assert.h>
#include <fstream>
#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) {}

Image::~Image() {
    delete[] pixels;
}

namespace {
    // Konversi 4 buah karakter ke integer, menggunakan bentuk little-endian
    int toInt(const char* bytes) {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8)  |
                     (unsigned char)bytes[0]);
    }

    // Konversi 2 buah karakter ke integer, menggunakan bentuk little-endian
    short toShort(const char* bytes) {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }

    // Membaca 4 byte selanjutnya sebagai integer, menggunakan bentuk little-endian
    int readInt(ifstream &input) {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

    short readShort(ifstream &input) {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

    template<class T>
    class auto_array {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) : array(array_), isReleased(false) {}

        auto_array(const auto_array<T> &aarray) {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        ~auto_array() {
            if (!isReleased && array != NULL) {
                delete[] array;
            }
        }

        T* get() const {
            return array;
        }

        T &operator*() const {
            return *array;
        }

        void operator=(const auto_array<T> &aarray) {
            if (!isReleased && array != NULL) {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        T* operator->() const {
            return array;
        }

        T* release() {
            isReleased = true;
            return array;
        }

        void reset(T* array_ = NULL) {
            if (!isReleased && array != NULL) {
                delete[] array;
            }
            array = array_;
        }

        T* operator+(int i) {
            return array + i;
        }

        T &operator[](int i) {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename) {
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"File tidak ditemukan!!!");

    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Bukan file bitmap!!!");

    input.ignore(8);
    int dataOffset = readInt(input);
    int headerSize = readInt(input);
    int width, height;

    switch(headerSize) {
        case 40:
            width = readInt(input);
            height = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Gambar tidak 24 bits per pixel!");
            assert(readShort(input) == 0 || !"Gambar dikompres!");
            break;
        case 12:
            width = readShort(input);
            height = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Gambar tidak 24 bits per pixel!");
            break;
        case 64:
            assert(!"Tidak dapat mengambil OS/2 V2 bitmaps");
            break;
        case 108:
            assert(!"Tidak dapat mengambil Windows V4 bitmaps");
            break;
        case 124:
            assert(!"Tidak dapat mengambil Windows V5 bitmaps");
            break;
        default:
            assert(!"Format bitmap ini tidak diketahui!");
    }

    // Membaca data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);

    // Mengambil data yang mempunyai format benar
    auto_array<char> pixels2(new char[width * height * 3]);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            for(int c = 0; c < 3; c++) {
                pixels2[3 * (width * y + x) + c] = pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}
