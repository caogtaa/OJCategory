//
//  by caogtaa
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

#define TORLERANCE  0.0000000001

// namespace geometry {

template <class V>
inline V square(V v)
{
    return v * v;
}

template <typename V>
bool in_range(V v, V r1, V r2)
{
    return v >= min(r1, r2) && v <= max(r1, r2);
}

template <typename P>
typename P::value_type x_mul(const P &pp, const P &p1, const P &p2)
{
    // XMUL of vector (pp-p1) and (p2-p1)
    if (p1.cy > p2.cy ){
        // swap(p1, p2);
        // return x_mul(pp, p2, p1);
        return (pp.cx-p2.cx) * (p1.cy-p2.cy) - (pp.cy-p2.cy) * (p1.cx-p2.cx);
    }
    
    return (pp.cx-p1.cx) * (p2.cy-p1.cy) - (pp.cy-p1.cy) * (p2.cx-p1.cx);
}

template <typename P>
bool ray_intersect(const P &pp, const P &p1, const P &p2)
{
    // if right ray from pp intersects with segment (p1, p2)
    return in_range(pp.cy, p1.cy, p2.cy) &&
        abs(pp.cy - min(p1.cy, p2.cy)) >= TORLERANCE &&
        x_mul(pp, p1, p2) < 0; // todo: loose precision for double?
}

template <typename P>
bool on_edge(const P &pp, const P &p1, const P &p2){
    return in_range(pp.cx, p1.cx, p2.cx) &&
        in_range(pp.cy, p1.cy, p2.cy) &&
        abs(x_mul(pp, p1, p2)) <= TORLERANCE;
}

template <typename P>
bool line_intersects(const P &s1, const P &e1, const P &s2, const P &e2)
{
    if (on_edge(s1, s2, e2) || on_edge(e1, s2, e2) || on_edge(s2, s1, e1) || on_edge(e2, s1, e1))
        return true;
    
    auto x1 = x_mul(s1, s2, e2);
    auto x2 = x_mul(e1, s2, e2);
    auto y1 = x_mul(s2, s1, e1);
    auto y2 = x_mul(e2, s1, e1);
    // todo: carefully check x1*x2 == 0
    // when segments are parallel
    return ((x1 * x2 < 0) && (y1 * y2) < 0);
}

template <typename P>
typename P::value_type euclid_distance(const P &p1, const P &p2) {
    return std::hypot(p1.cx-p2.cx, p1.cy-p2.cy);
}

struct PointD
{
    typedef double value_type;
    
    PointD() {}
    PointD(double x, double y): cx(x), cy(y) {}
    bool operator == (const PointD &p2) const {
        return abs(cx - p2.cx) <= TORLERANCE && abs(cy - p2.cy) <= TORLERANCE;
    }
    
    double cx, cy;
};

template <class P>
struct Vector2D
{
    typedef typename P::value_type value_type;

    Vector2D() {}
    Vector2D(value_type x, value_type y) : cx(x), cy(y) {}
    Vector2D(const P &p) : cx(p.cx), cy(p.cy) {}
    Vector2D(const P &sp, const P &ep) : cx(ep.cx-sp.cx), cy(ep.cy-sp.cy) {}
    
    // rotate clockwise 90 degree
    // (x, y) -> (y, -x)
    void rotate() {
        value_type tmp = cx;
        cx = cy;
        cy = -tmp;
        // return Vector2D(cy, -cx);
    }
    
    void unitize() {
        double tmp = hypot(cx, cy);
        cx /= tmp;
        cy /= tmp;
    }
    
    value_type dot_mul(const Vector2D<P> &v) const {
        return cx * v.cx + cy * v.cy;
    }
    
    value_type cx;
    value_type cy;
};

template <class P>
struct Rect
{
    typedef typename P::value_type value_type;

    P top_left;
    P bottom_right;
    
    inline P top_right() const {
        P result;
        result.cx = bottom_right.cx;
        result.cy = top_left.cy;
        return result;
    }
    
    inline P bottom_left() const {
        P result;
        result.cx = top_left.cx;
        result.cy = bottom_right.cy;
        return result;
    }
    
    inline value_type width() const {
        return bottom_right.cx - top_left.cx;
    }
    
    inline value_type height() const {
        return top_left.cy - bottom_right.cy;
    }
    
    inline value_type area() const {
        return width() * height();
    }
    
    inline value_type top() const {
        return top_left.cy;
    }
    
    inline value_type bottom() const {
        return bottom_right.cy;
    }
    
    inline value_type left() const {
        return top_left.cx;
    }
    
    inline value_type right() const {
        return bottom_right.cx;
    }
    
    inline value_type center_y() const {
        return (top_left.cy + bottom_right.cy) / 2;
    }
    
    inline value_type center_x() const {
        return (top_left.cx + bottom_right.cx) / 2;
    }
    
    inline P center() const {
        P result;
        result.cx = center_x();
        result.cy = center_y();
        return result;
    }
    
    bool intersects(const P &pnt) const {
        return left() <= pnt.cx && pnt.cx <= right() && bottom() <= pnt.cy && pnt.cy <= top();
    }
};

template <typename P>
struct Polygon
{
    vector<P> _v;
    
    Rect<P> bounding_rect() const {
        Rect<P> result;
        result.top_left.cx = std::numeric_limits<typename P::value_type>::max();
        result.top_left.cy = std::numeric_limits<typename P::value_type>::min();
        result.bottom_right.cx = std::numeric_limits<typename P::value_type>::min();
        result.bottom_right.cy = std::numeric_limits<typename P::value_type>::max();
        
        for (int i = 0; i < (int)_v.size(); ++i) {
            result.top_left.cx = min(result.top_left.cx, _v[i].cx);
            result.top_left.cy = max(result.top_left.cy, _v[i].cy);
            result.bottom_right.cx = max(result.bottom_right.cx, _v[i].cx);
            result.bottom_right.cy = min(result.bottom_right.cy, _v[i].cy);
        }
        
        return result;
    }
    
    bool intersects(const P &pnt) const {
        bool done = false;
        int pre_index;
        for (int i = 0; i < (int)_v.size(); ++i) {
            pre_index = (i+(int)_v.size()-1) % _v.size();
            if (on_edge(pnt, _v[i], _v[pre_index]))
                return true;

            if (ray_intersect(pnt, _v[i], _v[pre_index])) {
                if (done)
                    // more than 2 intersection
                    return false;
                
                done = true;
            }
        }
        
        return done;
    }
    
    template <typename R>
    bool intersects_rect(const R &rc) const {
        if (intersects(rc.center()))
            return true;
        
        if (rc.intersects(_v[0]))
            return true;

        // line cross test
        int pre_index;
        for (int i = 0; i < (int)_v.size(); ++i) {
            pre_index = (i+(int)_v.size()-1) % _v.size();
            if (line_intersects(_v[i], _v[pre_index], rc.top_left, rc.top_right()))
                return true;
            
            if (line_intersects(_v[i], _v[pre_index], rc.top_right(), rc.bottom_right))
                return true;
            
            if (line_intersects(_v[i], _v[pre_index], rc.bottom_left(), rc.bottom_right))
                return true;
            
            if (line_intersects(_v[i], _v[pre_index], rc.bottom_left(), rc.top_left))
                return true;
        }
        
        return false;
    }
};

struct Ellipse
{
    typedef PointD P;
    typedef typename P::value_type value_type;

    P p1;
    P p2;
    double a;
    P center;
    double c;
    double b;
    double sin_theta;
    double cos_theta;
    bool is_circle;
    
    void init() {
        if (p2.cx < p1.cx) {
            P tmp = p2;
            p2 = p1;
            p1 = tmp;
        }

        center.cx = (p1.cx + p2.cx) / 2;
        center.cy = (p1.cy + p2.cy) / 2;
        c = euclid_distance(p1, center);
        b = sqrt(square(a) - square(c));
        
        if (p1 == p2) {
            is_circle = true;
            sin_theta = 0.0;
            cos_theta = 0.0;
        } else {
            is_circle = false;
            auto dist = euclid_distance(p1, p2);
            sin_theta = (p1.cy - p2.cy) / dist;
            cos_theta = (p1.cx - p2.cx) / dist;
        }
    }
    
    inline double focal_distance(const P &pnt) const {
        return euclid_distance(pnt, p1) + euclid_distance(pnt, p2);
    }
    
    bool intersects(const P &pnt) const {
        // f(x,y) = x^2/a^2 + y^2/b^2=1,
        // f(x1,y1) < 1 then inside
        return focal_distance(pnt) <= 2 * a;
    }
    
    // intersects with horizontal line
    bool intersects_h_line(value_type y, value_type& x1, value_type& x2) const {
        y -= center.cy;
        if (is_circle) {
            if (square(a) - square(y) >= 0.0) {
                x1 = x2 = std::sqrt(square(a) - square(y)) + center.cx;
                return true;
            }
            
            return false;
        }

        double v = b;
        double h = a;
        double __a = square(v) * square(cos_theta) + square(h) * square(sin_theta);
        double __b = 2 * y * cos_theta * sin_theta * (square(v) - square(h));
        double __c = square(y) * (square(v) * square(sin_theta) + square(h) * square(cos_theta)) - square(h) * square(v);
        if (square(__b) >= __a * __c * 4) {
            double tmp = sqrt(square(__b) - __a * __c * 4);
            x1 = (-__b + tmp) / 2 / __a + center.cx;
            x2 = (-__b - tmp) / 2 / __a + center.cx;
            return true;
        }
        
        return false;
    }
    
    bool intersects_v_line(value_type x, value_type& y1, value_type& y2) const {
        x -= center.cx;
        if (is_circle) {
            if (square(a) - square(x) >= 0.0) {
                y1 = y2 = sqrt(square(a) - square(x)) + center.cy;
                return true;
            }
            
            return false;
        }

        double v = b;
        double h = a;
        double __a = square(v) * square(sin_theta) + square(h) * square(cos_theta);
        double __b = 2 * x * cos_theta * sin_theta * (square(v) - square(h));
        double __c = square(x) * (square(v) * square(cos_theta) + square(h) * square(sin_theta)) - square(h) * square(v);
        if (square(__b) >= __a * __c * 4) {
            double tmp = sqrt(square(__b) - __a * __c * 4);
            y1 = (-__b + tmp) / 2 / __a + center.cy;
            y2 = (-__b - tmp) / 2 / __a + center.cy;
            return true;
        }
        
        return false;
    }
    
    template <typename R>
    bool intersects_rect(const R &rc) const {
        if (rc.intersects(p1))
            return true;
        
        // consider the case rectangle contain it
        bool test1 = intersects(rc.top_left) || intersects(rc.bottom_right) ||
            intersects(rc.top_right()) || intersects(rc.bottom_left());

        if (test1)
            return true;
        
        // check intersection of horizontal lines
        double v1, v2;
        if (intersects_h_line(rc.top(), v1, v2)) {
            if (rc.left() <= v1 && v1 <= rc.right())
                return true;
            
            if (rc.left() <= v2 && v2 <= rc.right())
                return true;
        }
        
        if (intersects_h_line(rc.bottom(), v1, v2)) {
            if (rc.left() <= v1 && v1 <= rc.right())
                return true;
            
            if (rc.left() <= v2 && v2 <= rc.right())
                return true;
        }
        
        if (intersects_v_line(rc.left(), v1, v2)) {
            if (rc.bottom() <= v1 && v1 <= rc.top())
                return true;
            
            if (rc.bottom() <= v2 && v2 <= rc.top())
                return true;
        }
        
        if (intersects_v_line(rc.right(), v1, v2)) {
            if (rc.bottom() <= v1 && v1 <= rc.top())
                return true;
            
            if (rc.bottom() <= v2 && v2 <= rc.top())
                return true;
        }
        
        return false;
    }
};

inline double _ratio(double x1, double x2, double r) {
    // return x1 + (x2-x1) * r
    return x2 * r + x1 * (1-r);
}

#define MAXC    3000

double C[MAXC]; // length of perpendicular
Vector2D<PointD> V[MAXC]; // unitized perpendicular vector

int NC = 0;
vector<Polygon<PointD>> polys;
vector<Ellipse> ellis;
int N, M;
double resy;
    
// }

double solveWithXY(double x, double y)
{
    Vector2D<PointD> P(x, y);
    double cur;
    double result = std::numeric_limits<double>::lowest();
    for (int i = 0; i < NC; ++i) {
        cur = P.dot_mul(V[i]) - C[i];
        result = max(result, cur);
    }
    
    for (int i = 0; i < (int)ellis.size(); ++i) {
        cur = ellis[i].focal_distance(PointD(x, y)) - ellis[i].a * 2;
        result = max(result, cur);
    }
    
    return result;
}

double solveWithX(double x)
{
    double ly = -10000.0;
    double ry = 10000.0;
    const double C1 = 4.0/11.0;
    const double C2 = 7.0/11.0;
    
    for (int i = 0; i < 60; ++i) {
        double y1 = _ratio(ly, ry, C1);
        double y2 = _ratio(ly, ry, C2);
        double v1 = solveWithXY(x, y1);
        double v2 = solveWithXY(x, y2);
        if (v1 <= v2) {
            ry = y2;
        } else {
            ly = y1;
        }
    }
    
    resy = (ly + ry) / 2;
    return solveWithXY(x, resy);
}

int main()
{
    scanf("%d", &N);
    polys.resize(N);
    PointD pnt;
    for (int i = 0; i < N; ++i) {
        int nv;
        scanf("%d", &nv);
        for (int k = 0; k < nv; ++k) {
            scanf("%lf %lf", &pnt.cx, &pnt.cy);
            polys[i]._v.push_back(pnt);
        }
        
        polys[i]._v.push_back(polys[i]._v[0]);
        for (int k = 0; k < nv; ++k) {
            Vector2D<PointD> v(polys[i]._v[k], polys[i]._v[k+1]);
            v.rotate();
            v.unitize();
            V[NC] = v;
            C[NC++] = Vector2D<PointD>(polys[i]._v[k]).dot_mul(v);
        }
    }
    
    scanf("%d", &M);
    ellis.resize(M);
    for (int i = 0; i < M; ++i) {
        scanf("%lf %lf %lf %lf %lf", &ellis[i].p1.cx, &ellis[i].p1.cy, &ellis[i].p2.cx, &ellis[i].p2.cy, &ellis[i].a);
        ellis[i].init();
    }
    
    double lx = -10000.0;
    double rx = 10000.0;
    const double C1 = 4.0/11.0;
    const double C2 = 7.0/11.0;
    
    for (int i = 0; i < 60; ++i) {
        double x1 = _ratio(lx, rx, C1);
        double x2 = _ratio(lx, rx, C2);
        double v1 = solveWithX(x1);
        double v2 = solveWithX(x2);
        if (v1 <= v2) {
            rx = x2;
        } else {
            lx = x1;
        }
    }
    
    double resx = (lx + rx) / 2;
    printf("%lf\n%lf\n", resx, resy);
    return 0;
}
