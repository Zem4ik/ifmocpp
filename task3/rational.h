#pragma once

class rational {
    private:
        int num;
        int denom;
        int gcd(int a, int b) const;

    public:
        rational(int a);
        rational(int a, int b);
        int getNum() const;
        int getDenom() const;
        rational operator +(rational const &secondRational) const;
        rational operator -(rational const &secondRational) const;
        rational operator *(rational const &secondRational) const;
        rational operator /(rational const &secondRational) const;
};
