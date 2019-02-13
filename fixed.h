#include <cmath>

// TODO: MOINS UNAIRE DU CMI SUCEUR DE CHIBRE
// TODO: MOINS UNAIRE DU CMI SUCEUR DE CHIBRE
// TODO: MOINS UNAIRE DU CMI SUCEUR DE CHIBRE
// TODO: MOINS UNAIRE DU CMI SUCEUR DE CHIBRE
// TODO: MOINS UNAIRE DU CMI SUCEUR DE CHIBRE
// TODO: MOINS UNAIRE DU CMI SUCEUR DE CHIBRE
// TODO: MOINS UNAIRE DU CMI SUCEUR DE CHIBRE
// TODO: MOINS UNAIRE DU CMI SUCEUR DE CHIBRE


#ifndef FIXED_FIXED_H
#define FIXED_FIXED_H

#include <iostream>
#include <memory>

//TODO: perte de précision.

namespace fp {
/*
* fixed  point  type
*/
    template<std::size_t Int, std::size_t Frac>
    class fixed {
    public:

        using underlying_type = long long;
        underlying_type value;
        static constexpr std::size_t integer_part = Int;
        static constexpr std::size_t fractional_part = Frac;

/*
* constructors
*/
        fixed() = default;

        constexpr explicit fixed(float x);

        constexpr explicit fixed(double x);

/*
* copy  constructors
*/
        fixed(const fixed &other);

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed(const fixed<OtherInt, OtherFrac> &other);

/*
* copy  assignment
*/
        fixed &operator=(const fixed &other);

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator=(const fixed<OtherInt, OtherFrac> &other);

/*
* conversions
*/
        operator float() const;

        operator double() const;

/*
* compound  assignment  operators
*/
        fixed &operator+=(const fixed &other);

        fixed &operator+=(float other);

        fixed &operator+=(double other);

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator+=(const fixed<OtherInt, OtherFrac> &other);

        fixed &operator-=(const fixed &other);

        fixed &operator-=(float other);

        fixed &operator-=(double other);

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator-=(const fixed<OtherInt, OtherFrac> &other);

        fixed &operator*=(const fixed &other);

        fixed &operator*=(float other);

        fixed &operator*=(double other);

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator*=(const fixed<OtherInt, OtherFrac> &other);

        fixed &operator/=(const fixed &other);

        fixed &operator/=(float other);

        fixed &operator/=(double other);

        template<std::size_t OtherInt, std::size_t OtherFrac>
        fixed &operator/=(const fixed<OtherInt, OtherFrac> &other);
    };


    template<size_t Int, size_t Frac>
    constexpr fixed<Int, Frac>::fixed(float x) {//TODO: marche pas si Int + Frac = 0
        this->value = static_cast<long long>(std::round(x * std::pow(2, this->fractional_part)));
    }

    template<size_t Int, size_t Frac>
    constexpr fixed<Int, Frac>::fixed(double x) {//TODO: marche pas si Int + Frac = 0
        this->value = static_cast<long long>(std::round(x * std::pow(2, this->fractional_part)));
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac>::operator float() const {
        return ((float) ((this->value / std::pow(2, this->fractional_part))));
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac>::operator double() const {
        return (((double) (this->value)) / std::pow(2, this->fractional_part));
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac>::fixed(const fixed &other) {
        double val = double(other);
        this->value = static_cast<long long>(std::round(val * std::pow(2, this->fractional_part)));
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator=(const fixed &other) {//TODO: overflow.
        this->value = other.value;
        return *this;
    }

    template<size_t Int, size_t Frac>
    template<size_t OtherInt, size_t OtherFrac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator=(const fixed<OtherInt, OtherFrac> &other) {
        this->value = other.value;
        return *this;
    }


    template<size_t Int, size_t Frac>
    template<size_t OtherInt, size_t OtherFrac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator+=(const fixed<OtherInt, OtherFrac> &other) {
        long tmpV;
        if (OtherInt > Int) {
            if (OtherFrac > Frac) {
                fixed<OtherInt, OtherFrac> tmp(other);
                tmpV = this->value + tmp.value;
            } else {
                fixed<OtherInt, Frac> tmp(other);
                tmpV = this->value + tmp.value;
            }
        } else {
            if (OtherFrac > Frac) {
                fixed<Int, OtherFrac> tmp(other);
                tmpV = this->value + tmp.value;
            } else {
                fixed<Int, Frac> tmp(other);
                tmpV = this->value + tmp.value;
            }
        }
        if (tmpV > (pow(2,this->integer_part-1)-pow(2,-fractional_part))){
            throw std::overflow_error("Overflow !");
        }
        if (tmpV < -pow(2,integer_part-1)) {
            throw std::overflow_error("Overflow !");
        }
        this->value = tmpV;
        return *this;
    }


    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator+=(float other) {
        this->value += fixed<Int, Frac>(other).value;
        return *this;
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator+=(double other) {
        this->value += fixed<Int, Frac>(other).value;
        return *this;
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator+=(const fixed &other) {
        long long tmp=this->value+other.value;
        if (tmp > (pow(2,this->integer_part-1)-pow(2,-fractional_part))){
            throw std::overflow_error("Overflow !");
        }
        if (tmp < -pow(2,integer_part-1)) {
            throw std::overflow_error("Overflow !");
        }
        this->value = tmp;
        return *this;
    }



    template<size_t Int, size_t Frac>
    template<size_t OtherInt, size_t OtherFrac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator-=(const fixed<OtherInt, OtherFrac> &other) {
        long tmpV;
        if (OtherInt > Int) {
            if (OtherFrac > Frac) {
                fixed<OtherInt, OtherFrac> tmp(other);
                tmpV = this->value + tmp.value;
            } else {
                fixed<OtherInt, Frac> tmp(other);
                tmpV = this->value + tmp.value;
            }
        } else {
            if (OtherFrac > Frac) {
                fixed<Int, OtherFrac> tmp(other);
                tmpV = this->value + tmp.value;
            } else {
                fixed<Int, Frac> tmp(other);
                tmpV = this->value + tmp.value;
            }
        }
        if (tmpV > (pow(2,this->integer_part-1)-pow(2,-fractional_part))){
            throw std::overflow_error("Overflow !");
        }
        if (tmpV < -pow(2,integer_part-1)) {
            throw std::overflow_error("Overflow !");
        }
        this->value = tmpV;
        return *this;
    }


    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator-=(float other) {//TODO:overflow
        this->value += fixed<Int, Frac>(other).value;
        return *this;
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator-=(double other) {//TODO:overflow
        this->value += fixed<Int, Frac>(other).value;
        return *this;
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator-=(const fixed &other) {
        long long tmp=this->value+other.value;
        if (tmp > (pow(2,this->integer_part-1)-pow(2,-fractional_part))){
            throw std::overflow_error("Overflow !");
        }
        if (tmp < -pow(2,integer_part-1)) {
            throw std::overflow_error("Overflow !");
        }
        this->value = tmp;
        return *this;
    }


    template<size_t Int, size_t Frac>
    template<size_t OtherInt, size_t OtherFrac>
    fixed<Int, Frac>::fixed(const fixed<OtherInt, OtherFrac> &other) {
        double val = double(other);
        this->value = static_cast<long long>(std::round(val * std::pow(2, this->fractional_part)));
    }

    bool isOverflow (long long value, size_t integer_part, size_t fractional_part){
        return value > std::pow(-2, integer_part - 1) || std::floor(std::pow(2, integer_part - 1) - 1/std::pow(2, fractional_part));
    }


/*
* arithmetic  operators
*/

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    fixed<std::max(I1, I2), std::max(F1, F2)> operator+(fixed<I1, F1> lhs, fixed<I2, F2> rhs);
//    template <std:: size_t I1, std:: size_t F1, std:: size_t I2, std:: size_t F2>
//    implementation-defined operator-(fixed <I1, F1> lhs , fixed <I2, F2> rhs);
//    template<std:: size_t I1, std:: size_t F1, std:: size_t I2, std:: size_t F2>
//    implementation-defined operator*(fixed <I1, F1> lhs , fixed <I2, F2> rhs);
//    template<std:: size_t I1, std:: size_t F1, std:: size_t I2, std:: size_t F2>
//    implementation-defined operator/(fixed <I1, F1> lhs , fixed <I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    fixed<std::max(I1, I2), std::max(F1, F2)> operator+(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        return fixed<std::max(I1, I2), std::max(F1, F2)>(double(lhs) + double(rhs));
    }


/*
* comparison  operators
*/
    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator==(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator<(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator>(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator<=(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator>=(fixed<I1, F1> lhs, fixed<I2, F2> rhs);
/*
* types
*/
    using Q_8_8 = fixed<8, 8>;
    using Q_16_16 = fixed<16, 16>;
    using Q_0_32 = fixed<0, 32>;

/*
* traits
*/
    template<typename Fixed>
    struct fixed_traits {
        static constexpr Fixed lowest();

        static constexpr Fixed min();

        static constexpr Fixed max();

        static constexpr Fixed zero();

        static constexpr Fixed one();

        static constexpr Fixed pi();
    };

/*
* functions
*/
    template<typename Fixed>
    Fixed sqrt(Fixed f);

    template<typename Fixed>
    std::string to_string(Fixed f);

    template<typename Fixed>
    std::string to_string(Fixed f) {
        return std::to_string(f);
    }

    template<typename Fixed>
    std::ostream &operator<<(std::ostream &os, Fixed f);
}
#endif //FIXED_FIXED_H
