#include "VectorShort.h"
#include <iostream>
#include <cassert>
using namespace std;

class VectorShort {
private:
    short* data_;
    size_t size_;
    int codeError_;

    static size_t object_count_;

    void allocate_and_init(size_t n, short value) {
        data_ = nullptr;
        try {
            data_ = new short[n];
        } catch (bad_alloc&) {
            data_ = nullptr;
            size_ = 0;
            codeError_ = 1;
            return;
        }
        size_ = n;
        for (size_t i = 0; i < n; ++i) {
            data_[i] = value;
        }
        codeError_ = 0;
    }

public:
    static size_t getObjectCount() {
        return object_count_;
    }

    VectorShort() {
        allocate_and_init(1, 0);
        ++object_count_;
    }

    VectorShort(size_t n) {
        allocate_and_init(n, 0);
        ++object_count_;
    }

    VectorShort(size_t n, short init_value) {
        allocate_and_init(n, init_value);
        ++object_count_;
    }

    VectorShort(const VectorShort& other) {
        size_ = 0;
        data_ = nullptr;
        codeError_ = other.codeError_;
        allocate_and_init(other.size_, 0);
        if (data_) {
            for (size_t i = 0; i < other.size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        ++object_count_;
    }

    ~VectorShort() {
        delete[] data_;
        --object_count_;
    }

    void* operator new(size_t sz) {
        return ::operator new(sz);
    }
    void operator delete(void* ptr) {
        ::operator delete(ptr);
    }

    VectorShort& operator++() {
        for (size_t i = 0; i < size_; ++i)
            ++data_[i];
        return *this;
    }

    VectorShort operator++(int) {
        VectorShort temp = *this;
        ++(*this);
        return temp;
    }

    VectorShort& operator--() {
        for (size_t i = 0; i < size_; ++i)
            --data_[i];
        return *this;
    }
    VectorShort operator--(int) {
        VectorShort temp = *this;
        --(*this);
        return temp;
    }

    bool operator!() const {
        return (size_ != 0);
    }

    VectorShort operator~() const {
        VectorShort res(*this);
        for (size_t i = 0; i < res.size_; ++i)
            res.data_[i] = ~res.data_[i];
        return res;
    }

    VectorShort operator-() const {
        VectorShort res(*this);
        for (size_t i = 0; i < res.size_; ++i)
            res.data_[i] = -res.data_[i];
        return res;
    }

    VectorShort& operator=(const VectorShort& other) {
        if (this == &other) return *this;
        delete[] data_;
        allocate_and_init(other.size_, 0);
        if (data_) {
            for (size_t i = 0; i < other.size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        codeError_ = other.codeError_;
        return *this;
    }

    VectorShort& operator+=(const VectorShort& other) {
        if (size_ != other.size_) {
            codeError_ = 2;
            return *this;
        }
        for (size_t i = 0; i < size_; ++i)
            data_[i] += other.data_[i];
        return *this;
    }

    VectorShort& operator-=(const VectorShort& other) {
        if (size_ != other.size_) {
            codeError_ = 2;
            return *this;
        }
        for (size_t i = 0; i < size_; ++i)
            data_[i] -= other.data_[i];
        return *this;
    }

    VectorShort& operator*=(short scalar) {
        for (size_t i = 0; i < size_; ++i)
            data_[i] *= scalar;
        return *this;
    }

    VectorShort& operator/=(short scalar) {
        if (scalar == 0) {
            codeError_ = 3;
            return *this;
        }
        for (size_t i = 0; i < size_; ++i)
            data_[i] /= scalar;
        return *this;
    }

    VectorShort& operator%=(short scalar) {
        if (scalar == 0) {
            codeError_ = 3;
            return *this;
        }
        for (size_t i = 0; i < size_; ++i)
            data_[i] %= scalar;
        return *this;
    }

    VectorShort& operator|=(const VectorShort& other) {
        if (size_ != other.size_) {
            codeError_ = 2;
            return *this;
        }
        for (size_t i = 0; i < size_; ++i)
            data_[i] |= other.data_[i];
        return *this;
    }

    VectorShort& operator^=(const VectorShort& other) {
        if (size_ != other.size_) {
            codeError_ = 2;
            return *this;
        }
        for (size_t i = 0; i < size_; ++i)
            data_[i] ^= other.data_[i];
        return *this;
    }

    VectorShort& operator&=(const VectorShort& other) {
        if (size_ != other.size_) {
            codeError_ = 2;
            return *this;
        }
        for (size_t i = 0; i < size_; ++i)
            data_[i] &= other.data_[i];
        return *this;
    }

    VectorShort operator+(const VectorShort& other) const {
        VectorShort res(*this);
        res += other;
        return res;
    }

    VectorShort operator-(const VectorShort& other) const {
        VectorShort res(*this);
        res -= other;
        return res;
    }

    VectorShort operator*(short scalar) const {
        VectorShort res(*this);
        res *= scalar;
        return res;
    }

    VectorShort operator/(short scalar) const {
        VectorShort res(*this);
        res /= scalar;
        return res;
    }

    VectorShort operator%(short scalar) const {
        VectorShort res(*this);
        res %= scalar;
        return res;
    }

    VectorShort operator|(const VectorShort& other) const {
        VectorShort res(*this);
        res |= other;
        return res;
    }

    VectorShort operator^(const VectorShort& other) const {
        VectorShort res(*this);
        res ^= other;
        return res;
    }

    VectorShort operator&(const VectorShort& other) const {
        VectorShort res(*this);
        res &= other;
        return res;
    }

    friend VectorShort operator>>(const VectorShort& v, int shift) {
        VectorShort res(v);
        for (size_t i = 0; i < res.size_; ++i) {
            res.data_[i] >>= shift;
        }
        return res;
    }

    friend VectorShort operator<<(const VectorShort& v, int shift) {
        VectorShort res(v);
        for (size_t i = 0; i < res.size_; ++i) {
            res.data_[i] <<= shift;
        }
        return res;
    }

    bool operator==(const VectorShort& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) return false;
        }
        return true;
    }

    bool operator!=(const VectorShort& other) const {
        return !(*this == other);
    }

    short& operator[](size_t idx) {
        if (idx >= size_) {
            codeError_ = 4;
            return data_[size_ - 1];
        }
        return data_[idx];
    }

    const short& operator[](size_t idx) const {
        if (idx >= size_) {
            return data_[size_ - 1];
        }
        return data_[idx];
    }

    short operator()() const {
        short sum = 0;
        for (size_t i = 0; i < size_; ++i)
            sum += data_[i];
        return sum;
    }

    bool operator>(const VectorShort& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] <= other.data_[i]) return false;
        }
        return true;
    }

    bool operator>=(const VectorShort& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] < other.data_[i]) return false;
        }
        return true;
    }

    bool operator<(const VectorShort& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] >= other.data_[i]) return false;
        }
        return true;
    }

    bool operator<=(const VectorShort& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] > other.data_[i]) return false;
        }
        return true;
    }

    size_t size() const { return size_; }
    int codeError() const { return codeError_; }

    void print(ostream& os = cout) const {
        os << "[";
        for (size_t i = 0; i < size_; ++i) {
            os << data_[i];
            if (i + 1 < size_) os << ", ";
        }
        os << "]";
    }

};

size_t VectorShort::object_count_ = 0;

int main1() {
    VectorShort v1;
    VectorShort v2(5);
    VectorShort v3(4, 7);

    ++v3;
    v3.print(); cout << "\n";

    v3 -= v2;
    v3.print(); cout << "\n";

    VectorShort v4 = v3 * 2;
    v4.print(); cout << "\n";

    VectorShort v5 = ~v4;
    v5.print(); cout << "\n";

    VectorShort v6 = -v5;
    v6.print(); cout << "\n";

    cout << "Sum v6 = " << v6() << "\n";

    cout << "v6 > v4 ? " << (v6 > v4) << "\n";

    cout << "Object count: " << VectorShort::getObjectCount() << "\n";

    return 0;
}