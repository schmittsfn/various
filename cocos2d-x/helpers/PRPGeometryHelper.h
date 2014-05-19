//
//  PRPGeometryHelper.h
//  primaryp
//
//  Created by stefan on 5/15/14.
//
//

#ifndef primaryp_PRPGeometryHelper_h
#define primaryp_PRPGeometryHelper_h


/** Returns the sign of the crossproduct as an integer with the value 1 */
inline int getCrossProductSign(const cocos2d::Point& a, const cocos2d::Point& b)
{
	return (a.cross(b) < 0.) ? -1 : 1;
}

/** Converts radians to 0 - 360 degrees */
inline float radiansToDegrees(const float rad)
{
    float deg = CC_RADIANS_TO_DEGREES(rad);
    return deg < 0. ? deg + 360 : deg;
}

#pragma mark - Cartesian - Polar conversions
struct PolarCoord {
    float r; // radius
    float a; // angle
};

/** Converts a cartesian coordinate to a polar coordinate */
inline PolarCoord convertCartesianToPolar(const cocos2d::Point& p)
{
    float r = hypotf(p.x, p.y);
    float rad = atan2f(p.y, p.x);
    float a = radiansToDegrees(rad);
    return {r,a};
}

/** Converts a polar coordinate to a cartesian coordinate */
inline cocos2d::Point convertPolarToCartesian(const PolarCoord p)
{
    float rad = CC_DEGREES_TO_RADIANS(p.a);
    float x = p.r * cosf(rad);
    float y = p.r * sinf(rad);
    return cocos2d::Point(x,y);
}

#pragma mark - Vector
/** Returns a new vector rotated by a given angle (clockwise) */
inline cocos2d::Point rotateVector(const cocos2d::Point& vec, const float angle)
{
    PolarCoord p = convertCartesianToPolar(vec);
    p.a += angle;
    return convertPolarToCartesian(p);
}

/** Returns the angle of the line between two points */
inline float getAngleOfLineBetweenTwoPoints(const cocos2d::Point& p1, const cocos2d::Point& p2)
{
    float xDiff = p2.x - p1.x;
    float yDiff = p2.y - p1.y;
    return atan2(yDiff, xDiff) * (180. / M_PI);
}

/** Computes the length of a vector */
inline float getVectorMagnitude(const cocos2d::Point& a)
{
	return hypotf(a.x, a.y);
}

/** Returns the angle between two vectors */
inline float getAngleBetweenVectors(const cocos2d::Point& a, const cocos2d::Point& b)
{
	const float lengthProd = getVectorMagnitude(a) * getVectorMagnitude(b);
    const float cosA = MIN(a.dot(b) / lengthProd, 1.0);
    const float rad = acos(cosA);
    float deg = CC_RADIANS_TO_DEGREES(rad);
    return deg * getCrossProductSign(a, b);
}

#pragma mark - Triangle
/** Calculates the area of a triangle */
inline double getTriangleArea(float sideA, float sideB, float angle)
{
    return sideA * sideB * (sin(angle) / 2.);
}

#pragma mark - Circle
/* circle_circle_intersection() *
 * Determine the points where 2 circles in a common plane intersect.
 *
 * int circle_circle_intersection(
 *                                // center and radius of 1st circle
 *                                double x0, double y0, double r0,
 *                                // center and radius of 2nd circle
 *                                double x1, double y1, double r1,
 *                                // 1st intersection point
 *                                double *xi, double *yi,
 *                                // 2nd intersection point
 *                                double *xi_prime, double *yi_prime)
 *
 * This is a public domain work. 3/26/2005 Tim Voght
 * http://paulbourke.net/geometry/circlesphere/tvoght.c
 */
inline int circle_circle_intersection(double x0, double y0, double r0,
                                      double x1, double y1, double r1,
                                      double *xi, double *yi,
                                      double *xi_prime, double *yi_prime)
{
    double a, dx, dy, d, h, rx, ry;
    double x2, y2;
    
    /* dx and dy are the vertical and horizontal distances between
     * the circle centers.
     */
    dx = x1 - x0;
    dy = y1 - y0;
    
    /* Determine the straight-line distance between the centers. */
    //d = sqrt((dy*dy) + (dx*dx));
    d = hypot(dx,dy); // Suggested by Keith Briggs
    
    /* Check for solvability. */
    if (d > (r0 + r1))
    {
        /* no solution. circles do not intersect. */
        return 0;
    }
    if (d < fabs(r0 - r1))
    {
        /* no solution. one circle is contained in the other */
        return 0;
    }
    
    /* 'point 2' is the point where the line through the circle
     * intersection points crosses the line between the circle
     * centers.
     */
    
    /* Determine the distance from point 0 to point 2. */
    a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;
    
    /* Determine the coordinates of point 2. */
    x2 = x0 + (dx * a/d);
    y2 = y0 + (dy * a/d);
    
    /* Determine the distance from point 2 to either of the
     * intersection points.
     */
    h = sqrt((r0*r0) - (a*a));
    
    /* Now determine the offsets of the intersection points from
     * point 2.
     */
    rx = -dy * (h/d);
    ry = dx * (h/d);
    
    /* Determine the absolute intersection points. */
    *xi = x2 + rx;
    *xi_prime = x2 - rx;
    *yi = y2 + ry;
    *yi_prime = y2 - ry;
    
    return 1;
}






#endif
