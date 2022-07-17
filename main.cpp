/*
 Builds a particle collison simulation.
 Collision are detected using a brute force approach
 where in each time step, every particle checks its
 distance to everyother particle, when a particle collison
 has occured, the particles color will change to a random color.
 
 main takes up to two integer arguments, first is the number of
 particles to simulate and second is the number of frames
 ex to simulate 70 particles for 600 frames
 ./p 70 600
 */
 
#include "PPM.hpp"
#include "particle.hpp"

#include <thread>
#include <chrono>
#include <sys/wait.h>
#include <unistd.h>

const Vec2 BOUNDS(1080,1080);//screen resolution
const float BALL_R = 10;// ball/particle raduis
int num_P = 50;//defualt number of particles

// shape representation of a particle
struct Ball{
    float x;
    float y;
    float r;
    Ball(float x, float y, float r):x(x),y(y),r(r){}
};
// holds color and pos data for each particle in a frame
struct Frame{
    int frame;
    vector<Color> colors;
    vector<Particle> set;
};
//init set and initial colors
void initSet(vector<Particle> &v,vector<Color>  &c);
// color in pixel data into PPM file
void colorBall(PPM *ppm,Ball ball,Color color);
// draw Frames from a Frame set(sim) within a range [start,end]
void drawFrames(vector<Frame> sim, int start, int end);
// updatae pos, check and correct for collision.
void updateParticles(vector<Particle> &set, vector<Color> &colors, float step, int &numC);
// update screen.js to play correct nunber of frames, calling edit.awk
void initJS(int num){
    char *arg[5];
    arg[0] = (char*)"./edit.awk";
    arg[1] = (char*)"-v";
    string N = "NUM=" + to_string(num);
    arg[2] = (char*)N.c_str();
    arg[3] = (char*)"script.js";
    arg[4] = NULL;
    
    pid_t c_pid = fork();
    if(c_pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(c_pid > 0){
        wait(0);
        return;
    }else{
        if(execvp(arg[0],arg) == -1)
            perror("execvp");
        exit(EXIT_SUCCESS);
    }
}
//
int main(int argc, char* argv[]){
    srand(40);
    
    int totalFrames = 300;//default number of frames to produce
    if(argc > 1)
        num_P = atoi(argv[1]);
    if(argc > 2)
        totalFrames = atoi(argv[2]);
    
    if(num_P <= 0 || totalFrames <=0 ){
        cerr<<"Needs two arguments > 0. first, the number of particles and second, the number of frames\nEx: ./p 50 300\n";
        exit(1);
    }
    
    thread _b(initJS,totalFrames);
    _b.detach();
    
    vector<Particle> set;
    vector<Color> ballColor;
    initSet(set,ballColor);
    
   
    const float step = 1.0 / 120.0;
    float time = 0.0;
    int numCollisions = 0;
    
    vector<Frame> sim;
    int frame = 0;
    
    while(frame < totalFrames){
        
        updateParticles(set,ballColor,step,numCollisions);
        time += step;
        
        //write data
        if( (int) (time / step) % 60 == 0 ){
            Frame t;
            t.frame = frame;
            t.colors = ballColor;
            t.set = set;
            sim.push_back(t);
            frame++;
            cout << "recording frame # " << frame << endl;
        }
        
    }
    
    int range = totalFrames / 4;
    Vec2 r1(0,range);
    Vec2 r2(range+1,2*range);
    Vec2 r3((2*range)+1,3*range);
    Vec2 r4((3*range)+1,totalFrames-1);
    
    thread a(drawFrames,sim,r1.x,r1.y);
    thread b(drawFrames,sim,r2.x,r2.y);
    thread c(drawFrames,sim,r3.x,r3.y);
    thread d(drawFrames,sim,r4.x,r4.y);


    a.join();
    b.join();
    c.join();
    d.join();
    
    
    return 0;
}
void initSet(vector<Particle> &v,vector<Color> &c){
    Color blue(0,0,255);
    for(int i = 0; i < num_P; i++){
        float mass = 10;
        Particle p(BOUNDS,mass);
        
        float dx = (rand() % 100)/ 100.0;
        float dy = (rand() % 100)/ 100.0;

        Vec2 pos;
        pos.x = (rand()  % ( (int)BOUNDS.x - 50 + 1 ) + 50) * 1.0 + dx;
        pos.y = (rand()  % ( (int)BOUNDS.y - 50 + 1 ) + 50) * 1.0 + dy;
        
        p.setPos(pos);
        
        int s = rand() % 2;
        if( s == 0) s = -1;
        
        Vec2 vel;
        vel.x = (rand() % 10 -3 + 1)*s+dx;
        vel.y = (rand() % 10-3 + 1 )*s+dy ;
        
        p.setVel(vel);
        
        v.push_back(p);
        c.push_back(blue);
    }
}
void updateParticles(vector<Particle> &set, vector<Color> &colors, float step, int &numC){
    //update positions
    for(int i = 0; i < set.size(); i++){
        set[i].updatePos(step,BALL_R);
        //set[i].updateVel(step);
    }
    //brute force particle collisions
    for(int i = 0; i < set.size(); i++){
        for(int j = 0; j < set.size();j++){
            if( j != i ) {
                if( dist(set[i],set[j]) < (2*BALL_R) ) {
                    numC++;
                    collision(&set[i],&set[j]);
                    while(dist(set[i],set[j]) < (2*BALL_R) ){
                        set[i].updatePos(step,BALL_R);
                        set[j].updatePos(step,BALL_R);
                    }
                    colors[i] = getRandomColor();
                    colors[j] = getRandomColor();
                }
            }
        }
    }
}
void colorBall(PPM *ppm,Ball ball,Color color){
    for(int y = ball.y - ball.r; y < ball.y + ball.r; y++)
        for(int x = ball.x - ball.r; x < ball.x + ball.r; x++){
            float d = dist(x,y, ball.x,ball.y);
            if( d < ball.r )
                ppm->setPixelColor(x,y,color);
        }
}
void drawFrames(vector<Frame> sim, int start, int end){
    if(start >= sim.size()) return;
    string folderPath = "img/";
    PPM ppm(BOUNDS.x,BOUNDS.y,folderPath);
    for(int i = start; i <= end; i++){
        for(int j = 0; j < sim[i].set.size();j++){
            Vec2 pos = sim[i].set[j].getPos();
            Ball b(pos.x,pos.y,BALL_R);
            colorBall(&ppm,b,sim[i].colors[j]);
        }
        ppm.drawImage(sim[i].frame);
        convertImage(sim[i].frame);
    }
}
