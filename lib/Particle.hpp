//Particle.hpp - Library for simulation of classical particles
//Written by Luca Morelli 2021 

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <CppPhysics/VectorAlgebra.hpp>
#include <math.h>
#include <stdexcept>
#include <vector>

namespace Particle {

class Point  {

VA::Vector3d position;
VA::Vector3d velocity;
double mass{0};
double charge{0};

public:
Point(VA::Vector3d pos, VA::Vector3d vel, double M, double ch) 
: position{pos},velocity{vel},mass{M},charge{ch} {}

Point(VA::Vector3d pos, VA::Vector3d vel, double M) 
: position{pos},velocity{vel},mass{M} {}

Point(VA::Vector3d pos, VA::Vector3d vel) 
: position{pos},velocity{vel} {}
Point(VA::Vector3d pos) 
: position{pos} {}

Point(double M) 
: mass{M}{}

Point(double M, double ch) 
: mass{M},charge{ch} {}

auto const& getPosition() const{
    return position;
}

auto const& getVelocity() const{
    return velocity;
}

double getMass() const{
    return mass;
}

double getCharge() const{
    return charge;
}

double getSpeed() const{
    return mod(velocity);
}

double getKE() const{
    return mass*pow(this->getSpeed(),2)/2;
}

auto& accPosition() {
    return position;
}

auto& accVelocity() {
    return velocity;
}

void setMass(double newMass) {
    mass=newMass;
}

void setCharge(double newCharge) {
    charge=newCharge;
}

void evolveDynamics(VA::Vector3d const& force)
{
    position+=velocity*VA::Const::epsilon+force/(2*mass)*pow(VA::Const::epsilon,2);
    velocity+=force/mass*VA::Const::epsilon;
    
}  
};

inline double distance(Point p1,Point p2)
{
    return mod(p1.getPosition()-p2.getPosition());
}


class Gas{
    std::vector<Point> population;
    long unsigned int N;
    VA::Vector3d containerSize;

    public:
    Gas(Point const& p, long unsigned int n, VA::Vector3d borders) : population(n,p) , N{n}, containerSize{borders} {}
    Gas(std::vector<Point> pop, VA::Vector3d borders) : population{pop}, N{population.size()}, containerSize{borders} {}
    
    void add(Point const& newParticle)
    {
        population.push_back(newParticle);
        N++;
    }

    //Remove

    auto getPointer(int n=0)
    {
        return &population[n];
    }

    Point const& getParticle(int n) const
    {
        return population[n];
    }

    Point& accParticle(int n)
    {
        return population[n];
    }

    double totalMass() const{
        double partialMass{0};
        for(auto p:population)
        {
            partialMass+=p.getMass();
        }
        return partialMass;
    }



    void evolveDynamics(VA::Vector3d externalForces)
    {
        
        for(auto p1:population)
        {
           VA::Vector3d internalForces{0};
           for(auto p2:population)
           {
               internalForces+=VA::hat(p2.getPosition()-p1.getPosition())/pow(distance(p1,p2),2)*(-1*VA::Const::G*p1.getMass()*p2.getMass()+VA::Const::K_e*p1.getCharge()*p2.getCharge());
           }
           p1.evolveDynamics(externalForces+internalForces);
           if(p1.getPosition().x<0||p1.getPosition().x>containerSize.x)
           {
               p1.accVelocity().x*=-1;
           }
           if(p1.getPosition().y<0||p1.getPosition().y>containerSize.y)
           {
               p1.accVelocity().y*=-1;
           }
           if(p1.getPosition().z<0||p1.getPosition().z>containerSize.z)
           {
               p1.accVelocity().z*=-1;
           }
        }
    }
};

};





#endif