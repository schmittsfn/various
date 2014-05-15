//
//  PRPGeometryHelper.h
//  primaryp
//
//  Created by stefan on 5/15/14.
//
//

#ifndef primaryp_PRPGeometryHelper_h
#define primaryp_PRPGeometryHelper_h

/** Returns the angle of the line between two points */
float getAngleOfLineBetweenTwoPoints(const cocos2d::Point& p1, const cocos2d::Point& p2)
{
    float xDiff = p2.x - p1.x;
    float yDiff = p2.y - p1.y;
    return atan2(yDiff, xDiff) * (180. / M_PI);
}

/** Computes the length of a vector */
float getVectorLength(const cocos2d::Point& a)
{
	return sqrt(a.dot(a));
}

/** Returns the sign of the crossproduct as an integer with the value 1 */
int getCrossProductSign(const cocos2d::Point& a, const cocos2d::Point& b)
{
	return (a.cross(b) < 0.) ? -1 : 1;
}

/** Returns the angle between two vectors */
float getAngleBetweenVectors(const cocos2d::Point& a, const cocos2d::Point& b)
{
	const float lengthProd = getVectorLength(a) * getVectorLength(b);
    const float cosA = MIN(a.dot(b) / lengthProd, 1.0);
    const float rad = acos(cosA);
    float deg = CC_RADIANS_TO_DEGREES(rad);
    return deg * getCrossProductSign(a, b);
}

#endif
