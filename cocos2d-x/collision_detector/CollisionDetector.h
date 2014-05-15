#ifndef __primaryp__PRPCollisionDetector__
#define __primaryp__PRPCollisionDetector__

#include "cocos2d.h"

class CollisionDetector : public cocos2d::Ref
{
public:
    typedef cocos2d::Ref super;
    
    CREATE_FUNC(CollisionDetector);
    
    virtual bool init();
    
    virtual ~CollisionDetector();
    
    //Function signature for checking for collision detection spr1, spr2 are the concerned sprites
    //pp is bool, set to true if Pixel Perfection Collision is required. Else set to false
    //_rt is the secondary buffer used in our system
    bool areTheSpritesColliding(cocos2d::Sprite* spr1,
                                cocos2d::Sprite* spr2,
                                const bool pp,
                                cocos2d::RenderTexture* rt);
private:
    CollisionDetector();
    
    // Values below are all required for openGL shading
    cocos2d::GLProgram* _glProgram;
    cocos2d::Color4B* _buffer;
    int _uniformColorRed;
    int _uniformColorBlue;
    
};

#endif /* defined(__primaryp__PRPCollisionDetector__) */
