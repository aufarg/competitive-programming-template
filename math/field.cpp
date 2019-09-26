#ifdef DEBUG
#include <bits/stdc++.h>
#endif
namespace fields
{
    using namespace std;
    template<typename T, const T P>
    class field {
        class element {
            private:
            T value;

            public:
            element(T _value):
                value(_value) {}

            element(const element &other):
                value(other.value) {}

            element& operator+(const element &other) {
                value = (value + other.value) % P;
                return *this;
            }

            element& operator-(const element &other) {
                value = ((value - other.value) % P + P) % P;
                return *this;
            }

            element& operator*(const element &other) {
                value = (value * other.value) % P;
                return *this;
            }

            void operator+=(const element &other) {
                *this = *this + other;
            }

            void operator-=(const element &other) {
                *this = *this - other;
            }

            void operator*=(const element &other) {
                *this = *this * other;
            }

            bool operator==(const element &other) {
                return value == other.value;
            }

            bool operator==(const T &other) {
                return value == other;
            }

            element exp(T exponent) const {
                if (exponent == 0) return element(value);
                element ret = pow(exponent/2);
                ret *= ret;
                return (exponent%2) ? ret * value : ret;
            }

            element inverse() const {
                return pow(P-2);
            }

            element& operator/(const element &other) {
                *this *= other.inverse();
                return *this;
            }

            friend istream& operator>>(istream &stream, const element &element) {
                stream >> element.value;
                return stream;
            }

            friend ostream& operator<<(ostream &stream, const element &element) {
                stream << element.value;
                return stream;
            }
        };
        public:
        prime_field() {}
        prime_field(const prime_field<T, P> &other) {}

        element operator()(T value)
        {
            return element(value);
        }
    };
}
