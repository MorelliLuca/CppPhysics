#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <CppPhysics/Particle.hpp>
#include <CppPhysics/VectorAlgebra.hpp>
#include "math.h"
#include <iostream>

TEST_CASE("Creating a Particle")
{
    SUBCASE("First constructor")
    {
    Particle::Point p{{1,2,3},{4,5,6},100,123};
    CHECK(p.getPosition()==VA::Vector3d{1,2,3});
    CHECK(p.getVelocity()==VA::Vector3d{4,5,6});
    CHECK(p.getMass()==100);
    CHECK(p.getCharge()==123);
    CHECK(doctest::Approx(p.getKE())==3850.0);
    CHECK(doctest::Approx(p.getSpeed())==8.7749);
    }
    SUBCASE("Second constructor")
    {
    Particle::Point p{100,123};
    CHECK(p.getPosition()==VA::Vector3d{0,0,0});
    CHECK(p.getVelocity()==VA::Vector3d{0,0,0});
    CHECK(p.getMass()==100);
    CHECK(p.getCharge()==123);
    CHECK(p.getKE()==0);
    CHECK(p.getSpeed()==0);
    }
    
}

TEST_CASE("Falling object on the surface of the Earth")
{
    Particle::Point p{{0,0,10},{0,0,0},100,0};
    for(int i{0};i!=(1.426E5);++i)
    {
        p.evolveDynamics({0,0,-9.81*100});
    }
    CHECK(static_cast<int>(p.getPosition().z)==0);
}

TEST_CASE("Solar System")
{
    using  namespace VA;
    Particle::Point earth({1.470568E11,0,0},{0,30.28361E3,0},5.726E24);
    Particle::Point sun(1.989E30);
    Const::epsilon=60*60;
    for(int i{0};i!=365.25*24;++i)
    {
        double dis=Particle::distance(earth,sun);
        Vector3d f=-1*Const::G*sun.getMass()*earth.getMass()/pow(dis,2)*hat(earth.getPosition()-sun.getPosition());
        earth.evolveDynamics(f);
        sun.evolveDynamics(-f);
    }
    CHECK(VA::mod(earth.getPosition())/1.470568E11<1.05);
}

TEST_CASE("Dot and cross Product")
{
    using namespace VA;
    Vector3d v1{1,0,0},v2{0,1,0};
    Vector3d v3{crossP(v1,v2)};
    CHECK(v1*v2==0);
    CHECK(v1*v1==1);
    CHECK(v3==Vector3d{0,0,1});
}

TEST_CASE("betweenAngle Function")
{
    using namespace VA;
    Vector3d v1{1,0,0},v2{0,1,0};
    Vector3d v3{crossP(v1,v2)};
    CHECK(doctest::Approx(betweenAngle(v1,v2))==(Const::Pi/2));
    CHECK(doctest::Approx(betweenAngle(v2,v1))==(Const::Pi/2));
    CHECK(doctest::Approx(betweenAngle(v1,v1))==0);
    CHECK(doctest::Approx(betweenAngle(v1,v3))==(Const::Pi/2));
    v1+=v2;
    CHECK(doctest::Approx(betweenAngle(v1,v2))==(Const::Pi/4));
    v1+=v3;
    CHECK(doctest::Approx(betweenAngle(v1,v2))==0.95531);
}

TEST_CASE("cout overload")
{
    using namespace VA;
    Vector3d v1{1,0,0},v2{0,1,0};
    v1+=v2;
    v1/=3;
    v1+=v2;
    std::cout<<"Print test of a vector: if the followng message is correctly printed the overload is working\nV="<<v1<<'\n';
}

TEST_CASE("Vector3 Type conversion")
{
    using namespace VA;    
    Vector3d v1{1,0,0};
    Vector3f v3=v1;
    CHECK(v3==v1);
}
