#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

class VectorInt {
public:
    vector<int> data;
    VectorInt() = default;
    VectorInt(unsigned int n) : data(n, 0) {}
    VectorInt(const VectorInt& other) = default;

    int& operator[](unsigned int i) {
        assert(i < data.size());
        return data[i];
    }

    unsigned int size() const { return data.size(); }
};

class MatrixInt {
protected:
    VectorInt* IntArray;
    unsigned int n, size;
    unsigned char codeError;
    static int num_matrix;

public:
    unsigned int getN() const { return n; }
    unsigned int getSize() const { return size; }
    unsigned char getCodeError() const { return codeError; }

    MatrixInt() : IntArray(nullptr), n(0), size(0), codeError(0) {
        ++num_matrix;
    }

    MatrixInt(unsigned int isize) : n(isize), size(isize), codeError(0) {
        IntArray = new VectorInt[n];
        for (unsigned int i = 0; i < n; ++i) {
            IntArray[i] = VectorInt(size);
            IntArray[i][i] = 1;
        }
        ++num_matrix;
    }

    MatrixInt(unsigned int in, unsigned int isize2) : n(in), size(isize2), codeError(0) {
        IntArray = new VectorInt[n];
        for (unsigned int i = 0; i < n; ++i) {
            IntArray[i] = VectorInt(size);
        }
        ++num_matrix;
    }

    MatrixInt(unsigned int in, unsigned int isize2, int value) : n(in), size(isize2), codeError(0) {
        IntArray = new VectorInt[n];
        for (unsigned int i = 0; i < n; ++i) {
            IntArray[i] = VectorInt(size);
            for (unsigned int j = 0; j < size; ++j) {
                IntArray[i][j] = value;
            }
        }
        ++num_matrix;
    }

    MatrixInt(const MatrixInt& other) : n(other.n), size(other.size), codeError(other.codeError) {
        IntArray = new VectorInt[n];
        for (unsigned int i = 0; i < n; ++i) {
            IntArray[i] = other.IntArray[i];
        }
        ++num_matrix;
    }

    ~MatrixInt() {
        delete[] IntArray;
        --num_matrix;
    }

    MatrixInt& operator++() {
        for (unsigned int i = 0; i < n; ++i)
            for (unsigned int j = 0; j < size; ++j)
                ++IntArray[i][j];
        return *this;
    }

    MatrixInt operator++(int) {
        MatrixInt temp = *this;
        ++(*this);
        return temp;
    }

    MatrixInt operator-() const {
        MatrixInt result(n, size);
        for (unsigned int i = 0; i < n; ++i)
            for (unsigned int j = 0; j < size; ++j)
                result.IntArray[i][j] = -IntArray[i][j];
        return result;
    }

    bool operator!() const {
        return !(n == 0 || size == 0);
    }

    MatrixInt operator~() const {
        MatrixInt result(n, size);
        for (unsigned int i = 0; i < n; ++i)
            for (unsigned int j = 0; j < size; ++j)
                result.IntArray[i][j] = ~IntArray[i][j];
        return result;
    }

    VectorInt& operator[](unsigned int i) {
        if (i >= n) {
            codeError = 1;
            return IntArray[n-1];
        }
        return IntArray[i];
    }

    MatrixInt& operator=(const MatrixInt& other) {
        if (this == &other) return *this;
        delete[] IntArray;
        n = other.n; size = other.size; codeError = other.codeError;
        IntArray = new VectorInt[n];
        for (unsigned int i = 0; i < n; ++i) {
            IntArray[i] = other.IntArray[i];
        }
        return *this;
    }

    MatrixInt operator+(const MatrixInt& other) const {
        assert(n == other.n && size == other.size);
        MatrixInt result(n, size);
        for (unsigned int i = 0; i < n; ++i)
            for (unsigned int j = 0; j < size; ++j)
                result.IntArray[i][j] = IntArray[i][j] + other.IntArray[i][j];
        return result;
    }

    MatrixInt operator+(int scalar) const {
        MatrixInt result(n, size);
        for (unsigned int i = 0; i < n; ++i)
            for (unsigned int j = 0; j < size; ++j)
                result.IntArray[i][j] = IntArray[i][j] + scalar;
        return result;
    }

    MatrixInt operator-(const MatrixInt& other) const {
        assert(n == other.n && size == other.size);
        MatrixInt result(n, size);
        for (unsigned int i = 0; i < n; ++i)
            for (unsigned int j = 0; j < size; ++j)
                result.IntArray[i][j] = IntArray[i][j] - other.IntArray[i][j];
        return result;
    }

    MatrixInt operator*(int scalar) const {
        MatrixInt result(n, size);
        for (unsigned int i = 0; i < n; ++i)
            for (unsigned int j = 0; j < size; ++j)
                result.IntArray[i][j] = IntArray[i][j] * scalar;
        return result;
    }

    friend ostream& operator<<(ostream& os, const MatrixInt& m) {
        for (unsigned int i = 0; i < m.n; ++i) {
            for (unsigned int j = 0; j < m.size; ++j) {
                os << m.IntArray[i][j] << ' ';
            }
            os << '\n';
        }
        return os;
    }

    static int howMany() { return num_matrix; }
};

int MatrixInt::num_matrix = 0;

int main3() {
    MatrixInt A(2, 2, 3);
    MatrixInt B(2, 2, 1);

    MatrixInt C = ++A + (B * 2) - (-B) + ~A;

    cout << "A:\n" << A;
    cout << "B:\n" << B;
    cout << "C:\n" << C;
    cout << "Number of matrices: " << MatrixInt::howMany() << "\n";

    return 0;
}
