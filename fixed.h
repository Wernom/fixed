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

        using underlying_type = long long; //long long étant la plus grande valeurs entiere pouvant etre stocké dans la machine
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

    bool isOverflow (long long value, size_t integer_part, size_t fractional_part){
        return value >= std::pow(-2, integer_part - 1) || value <= std::floor(std::pow(2, integer_part - 1) - 1/std::pow(2, fractional_part));
    }

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
        fixed<Int, Frac> f(other);
        this->value = f.value;
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

        if (isOverflow(tmpV, this->integer_part, this->fractional_part)) {
            throw std::overflow_error("Overflow !");
        }

        this->value = tmpV;
        return *this;
    }


    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator+=(float other) {
        this->value += fixed<Int, Frac>(other).value;
        if (isOverflow(this->value, this->integer_part, this->fractional_part)) {
            throw std::overflow_error("Overflow !");
        }
        return *this;
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator+=(double other) {
        this->value += fixed<Int, Frac>(other).value;
        if (isOverflow(this->value, this->integer_part, this->fractional_part)) {
            throw std::overflow_error("Overflow !");
        }
        return *this;
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator+=(const fixed &other) {
        long long tmp=this->value+other.value;

        if (isOverflow(tmp, this->integer_part, this->fractional_part)) {
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
        if (isOverflow(tmpV, this->integer_part, this->fractional_part)) {
            throw std::overflow_error("Overflow !");
        }

        this->value = tmpV;
        return *this;
    }


    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator-=(float other) {//TODO:overflow
        this->value += fixed<Int, Frac>(other).value;
        if (isOverflow(this->value, this->integer_part, this->fractional_part)) {
            throw std::overflow_error("Overflow !");
        }
        return *this;
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator-=(double other) {
        this->value -= fixed<Int, Frac>(other).value;
        return *this;
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator*=(const fixed &other) {
        this->value *= other.value; // TODO: OVERFLOW !
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator*=(float other) {
        this->value *= fixed<Int, Frac>(other).value;
        return *this;
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator*=(double other) {
        this->value *= fixed<Int, Frac>(other).value;
        return *this;
    }


    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator/=(const fixed &other) {
        this->value /= other.value; // TODO: OVERFLOW !
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator/=(float other) {
        this->value /= fixed<Int, Frac>(other).value;
        return *this;
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator/=(double other) {
        this->value /= fixed<Int, Frac>(other).value;
        return *this;
    }

    template<size_t Int, size_t Frac>
    fixed<Int, Frac> &fixed<Int, Frac>::operator-=(const fixed &other) {
        long long tmp=this->value+other.value;

        if (isOverflow(tmp, this->integer_part, this->fractional_part)) {
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


/*
* arithmetic  operators
*/

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    fixed<std::max(I1, I2), std::max(F1, F2)> operator+(fixed<I1, F1> lhs, fixed<I2, F2> rhs);
    template <std:: size_t I1, std:: size_t F1, std:: size_t I2, std:: size_t F2>
    fixed<std::max(I1, I2), std::max(F1, F2)> operator-(fixed <I1, F1> lhs , fixed <I2, F2> rhs);
    template<std:: size_t I1, std:: size_t F1, std:: size_t I2, std:: size_t F2>
    fixed<std::max(I1, I2), std::max(F1, F2)> operator*(fixed <I1, F1> lhs , fixed <I2, F2> rhs);
    template<std:: size_t I1, std:: size_t F1, std:: size_t I2, std:: size_t F2>
    fixed<std::max(I1, I2), std::max(F1, F2)> operator/(fixed <I1, F1> lhs , fixed <I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    fixed<std::max(I1, I2), std::max(F1, F2)> operator+(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        fixed<std::max(I1, I2), std::max(F1, F2)> res (double(lhs) + double(rhs));

        if (isOverflow(res.value, res.integer_part, res.fractional_part)) {
            throw std::overflow_error("Overflow !");
        }

        return res;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    fixed<std::max(I1, I2), std::max(F1, F2)> operator-(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        fixed<std::max(I1, I2), std::max(F1, F2)> res (double(lhs) + double(rhs));
        if (isOverflow(res.value, res.integer_part, res.fractional_part)) {
            throw std::overflow_error("Overflow !");
        }
        return res;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    fixed<std::max(I1, I2), std::max(F1, F2)> operator*(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        fixed<std::max(I1, I2), std::max(F1, F2)> res (double(lhs) * double(rhs));
        if (isOverflow(res.value, res.integer_part, res.fractional_part)) {
            throw std::overflow_error("Overflow !");
        }
        return res;
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    fixed<std::max(I1, I2), std::max(F1, F2)> operator/(fixed<I1, F1> lhs, fixed<I2, F2> rhs) {
        fixed<std::max(I1, I2), std::max(F1, F2)> res (double(lhs) / double(rhs));
        if (isOverflow(res.value, res.integer_part, res.fractional_part)) {
            throw std::overflow_error("Overflow !");
        }
        return res;
    }


/*
* comparison  operators
*/
    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator==(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator==(fixed<I1, F1> lhs, fixed<I2, F2> rhs){
        return double(lhs) == double(rhs);
    }

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator<(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator<(fixed<I1, F1> lhs, fixed<I2, F2> rhs){
        return double(lhs) < double(rhs);
    }


    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator>(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator>(fixed<I1, F1> lhs, fixed<I2, F2> rhs){
        return double(lhs) > double(rhs);
    }


    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator<=(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator<=(fixed<I1, F1> lhs, fixed<I2, F2> rhs){
        return double(lhs) <= double(rhs);
    }


    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator>=(fixed<I1, F1> lhs, fixed<I2, F2> rhs);

    template<std::size_t I1, std::size_t F1, std::size_t I2, std::size_t F2>
    bool operator>=(fixed<I1, F1> lhs, fixed<I2, F2> rhs){
        return double(lhs) >= double(rhs);
    }

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

    template<typename Fixed>
    constexpr Fixed fixed_traits<Fixed>::lowest() {
        //On retourn un fixed qui vaut moins deux puissance le nombre de bit de la partie fractionnaire moins un.
        Fixed res(std::pow(-2, Fixed::integer_part - 1));
        return res;
    }

    template<typename Fixed>
    constexpr Fixed fixed_traits<Fixed>::min() {
        //La valeur la plus petite positive correspond à la résolution du nombre fixé soit deux puissance moins le nombre de bit de la partie fractionnaire.
        Fixed res(1/std::pow(2, Fixed::fractional_part));
        return res;
    }

    template<typename Fixed>
    constexpr Fixed fixed_traits<Fixed>::max() {
        //On retourn un fixed qui vaut deux puissance le nombre de bit de la partie entiere moins un le tout moins deux puissance moins la partie fractionnaire.
        Fixed res(std::pow(2, Fixed::integer_part - 1) - 1/std::pow(2, Fixed::fractional_part));
        return res;
    }

    template<typename Fixed>
    constexpr Fixed fixed_traits<Fixed>::zero() {
        Fixed res(0);
        return res;
    }

    template<typename Fixed>
    constexpr Fixed fixed_traits<Fixed>::one() {
        Fixed res(1);
        return res;
    }

    template<typename Fixed>
    constexpr Fixed fixed_traits<Fixed>::pi() {
        Fixed res(M_PI);
        return res;
    }

/*
* functions
*/
    template<typename Fixed>
    Fixed sqrt(Fixed f);

    template<typename Fixed>
    std::string to_string(Fixed f);

    template<typename Fixed>
    std::string to_string(Fixed f) {
        return std::to_string(double(f));
    }

    template<typename Fixed>
    std::ostream &operator<<(std::ostream &os, Fixed f);
}
#endif //FIXED_FIXED_H
