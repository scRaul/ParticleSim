/*
 2D particle model for represneting
 conservation of momentum. Acceleartion is 0
 and velocity is a constant.
 */

#ifndef PART_HPP
#define PART_HPP

#include <cmath>


struct Vec2{
    float x;
    float y;
    Vec2(float x=0, float y=0):x(x),y(y){}
};

class Particle{
    
private:
    Vec2 bounds;
    Vec2 vel;
    Vec2 pos;
 //   Vec2 acc;
    float mass;
    void boundsCheck(float r){
        if(pos.x <= 0+r || pos.x >= bounds.x-r)
            vel.x *= -1;
        if(pos.y <= 0+r || pos.y >= bounds.y-r)
            vel.y *= -1;
    }
public:
    
    Particle(Vec2 bounds, float mass):bounds(bounds),mass(mass){};
    
    void setVel(Vec2 vel){this->vel = vel;}
    void setPos(Vec2 pos){this->pos = pos;}
    
    Vec2 getVel(){return vel;}
    Vec2 getPos(){return pos;}
    float getMass(){return mass;}
    
    void updatePos(float t,float r){
        boundsCheck(r);
        pos.x = pos.x + ( vel.x*t ); //+ (.5 * acc.x * t * t);
        pos.y = pos.y + ( vel.y*t ); //+ (.5 * acc.y * t * t);
    }
//    void updateVel(float t){
//        p->vel.x = p->vel.x ;+  ( p->acc.x * t );
//        p->vel.y = p->vel.y ;+  ( p->acc.y * t );
//    }
    
    
};


double dist(Particle p1, Particle p2){
    Vec2 pos1 = p1.getPos();
    Vec2 pos2 = p2.getPos();
    
    return sqrt( pow( (pos2.x- pos1.x),2) + pow( (pos2.y-pos1.y),2 ) );
}
double dist (int x1, int y1, int x2, int y2 ){
    return sqrt( pow( (x2 - x1),2) + pow( (y2-y1),2 ) );
}

// Conservation of momentum calculation
void collision(Particle *p1, Particle *p2){
    Vec2 pos1 = p1->getPos();
    Vec2 pos2 = p2->getPos();
    
    Vec2 vel1 = p1->getVel();
    Vec2 vel2 = p2->getVel();
    
    float m1 = p1->getMass();
    float m2 = p2->getMass();
    
    
    Vec2 tv;
    tv.x = vel2.x;
    tv.y = vel2.y;
    
    
    vel2.x = vel2.y = 0;
    vel1.x -= tv.x;
    vel1.y -= tv.y;
    
    float mm = m1 + m2;
    float q1 = m1 - m2;
    float q2 = 2 * m1;
    
    vel2.x = ( (q2 / mm ) * vel1.x ) + tv.x;
    vel2.y = ( (q2 / mm ) * vel1.y ) + tv.y;
    
    vel1.x = ( (q1 / mm ) * vel1.x ) + tv.x;
    vel1.y = ( (q1 / mm ) * vel1.y ) + tv.y;
    
    
    p1->setVel(vel1);
    p2->setVel(vel2);
    
}


#endif
