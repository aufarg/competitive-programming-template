#include <bits/stdc++.h>

template<typename T>
class matrix {
    private:
    size_t N, M;
    T *values;

    void allocate_memory(size_t _N, size_t _M) {
        values = new T[_N*_M];
    }

    public:
    matrix(size_t _N, size_t _M):
        N(_N), M(_M) {
            allocate_memory(_N, _M);
        }

    matrix(initializer_list<vector<T>> list) {
        N = list.size(); M = list.begin()->size();
        allocate_memory(N, M);
        size_t index = 0;
        for (const vector<T> &v: list) {
            for (const T &x: v) {
                this->values[index] = x;
                index++;
            }
        }
    }

    matrix(vector<vector<T>> list) {
        N = list.size(); M = list.begin()->size();
        allocate_memory(N, M);
        size_t index = 0;
        for (const vector<T> &v: list) {
            for (const T &x: v) {
                this->values[index] = x;
                index++;
            }
        }
    }

    matrix(const matrix& other):
        N(other.N), M(other.M) {
            allocate_memory(N, M);
            memcpy(values, other.values, N*M*sizeof(*values));
    }

    void set_identity() {
        assert(N == M);
        memset(values, 0, N*M*sizeof(*values));
        for (int i = 0; i < N; i++) {
            values[i*M+i] = 1;
        }
    }

    T* operator[](const size_t index) const {
        return values + index * M;
    }

    matrix& operator=(const matrix& other) {
        delete[] values;

        allocate_memory(N, M);
        memcpy(values, other.values, N*M*sizeof(*values));

        return *this;
    }

    matrix operator*(const matrix& other) const {
        assert(M == other.N);
        matrix ret(N, other.M);
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < other.M; j++) {
                ret[i][j] = 0;
                for (size_t k = 0; k < M; k++) {
                    ret[i][j] += (*this)[i][k] * other[k][j];
                    ret[i][j] %= MOD;
                }
            }
        }
        return ret;
    }

    matrix& operator*=(const matrix &other) {
        return *this = *this * other;
    }

    matrix operator^(long long power) const {
        assert(N == M);
        matrix ret(N, M), base = *this;
        ret.set_identity();
        while (power > 0) {
            if (power % 2) ret *= base;
            power /= 2;
            base *= base;
        }
        return ret;
    }
};
