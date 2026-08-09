#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <math.h>
#include <string>
#include <sstream>

template <class T = double>
class Vector2
{
private:
public:
    Vector2(const T &X = 0, const T &Y = 0) : x{X}, y{Y}
    {
    }

    T x;
    T y;

    Vector2<T> Norm(bool return_only = true)
    {
        T abs = sqrt((x * x) + (y * y));
        Vector2<T> out = {x / abs, y / abs};
        if (!return_only)
        {
            x = out.x;
            y = out.y;
        }
        return out;
    }
    Vector2<T> Rotate(double angle, bool return_only = false)
    {
        T _x = (cos((0.017453293) * (-angle)) * x) + (sin((0.017453293) * (-angle)) * y);
        T _y = (-sin((0.017453293) * (-angle)) * x) + (cos((0.017453293) * (-angle)) * y);
        if (!return_only)
        {
            x = _x;
            y = _y;
        }
        return Vector2<T>(_x, _y);
    }
    Vector2<T> Scale(T factor, bool return_only = false)
    {
        T _x = x * factor;
        T _y = x * factor;
        if (!return_only)
        {
            x = _x;
            y = _y;
        }
        return Vector2<T>(_x,_y);
    }

    template <class U>
    Vector2<T> operator+(const Vector2<U> &r)
    {
        return Vector2<T>(x + r.x, y + r.y);
    }
    template <class U>
    Vector2<T> operator+=(const Vector2<U> &r)
    {
        x += r.x;
        y += r.y;
        return *this;
    }
    template <class U>
    Vector2<T> operator-(const Vector2<U> &r)
    {
        return Vector2<T>(x - r.x, y - r.y);
    }
    template <class U>
    Vector2<T> operator-=(const Vector2<U> &r)
    {
        x -= r.x;
        y -= r.y;
        return *this;
    }
    template <class U>
    Vector2<T> operator*(const Vector2<U> &r)
    {
        return Vector2<T>(x * r.x, y * r.y);
    }
    template <class U>
    Vector2<T> operator*=(const Vector2<U> &r)
    {
        x *= r.x;
        y *= r.y;
        return *this;
    }
    template <class U>
    Vector2<T> operator/(const Vector2<U> &r)
    {
        return Vector2(x / r.x, y / r.y);
    }
    template <class U>
    Vector2<T> operator/=(const Vector2<U> &r)
    {
        x /= r.x;
        y /= r.y;
        return *this;
    }

    template <class U>
    Vector2<T> operator+(const U &r)
    {
        return Vector2<T>(x + r, y + r);
    }
    template <class U>
    Vector2<T> operator+=(const U &r)
    {
        x += r;
        y += r;
        return *this;
    }
    template <class U>
    Vector2<T> operator-(const U &r)
    {
        return Vector2<T>(x - r, y - r);
    }
    template <class U>
    Vector2<T> operator-=(const U &r)
    {
        x -= r;
        y -= r;
        return *this;
    }
    template <class U>
    Vector2<T> operator*(const U &r)
    {
        Vector2<T> out = {x * (T)r, y * (T)r};
        return out;
    }
    template <class U>
    Vector2<T> operator*=(const U &r)
    {
        x *= (T)r;
        y *= (T)r;
        return *this;
    }
    template <class U>
    Vector2<T> operator/(const U &r)
    {
        return Vector2<T>(x / (T)r, y / (T)r);
    }
    template <class U>
    Vector2<T> operator/=(const U &r)
    {
        x /= (T)r;
        y /= (T)r;
        return *this;
    }
    template <class U>
    bool operator==(const Vector2<U> &r)
    {
        if (x == r.x || y == r.y)
        {
            return true;
        }
        return false;
    }
    template <class U>
    bool operator!=(const Vector2<U> &r)
    {
        if (x != r.x || y != r.y)
        {
            return true;
        }
        return false;
    }

    operator Vector2<double>()
    {
        Vector2<double> r = Vector2<double>((double)x, (double)y);
        return r;
    }
    operator std::string()
    {
        std::stringstream Xout;
        Xout << x;
        std::stringstream Yout;
        Yout << y;

        return "(" + Xout.str() + "," + Yout.str() + ")";
    }
    operator const char *()
    {
        std::stringstream Xout;
        Xout << x;
        std::stringstream Yout;
        Yout << y;

        std::string out = "(" + Xout.str() + "," + Yout.str() + ")";

        return out.data();
    }
};

#endif