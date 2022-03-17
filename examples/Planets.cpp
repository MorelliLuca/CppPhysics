#define USING_SFML

#include <CppPhysics/Particle.hpp>
#include <SFML/Graphics.hpp>
#include <CppPhysics/VectorAlgebra.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

double static constexpr R{1.5E11}; 
Particle::Point sun{1.989E30};
std::vector<VA::Vector3d> orbitTrack,sunTrack;

void printOrbit(Particle::Point const& planet, sf::RenderWindow& window)
{
  orbitTrack.push_back(planet.getPosition());
  sunTrack.push_back(sun.getPosition());
  sf::CircleShape trackerPoint(1, 4);
  trackerPoint.setFillColor(sf::Color::White);
  for(auto point : orbitTrack)
  {
  trackerPoint.setPosition(point*2E-9+VA::Vector3d{350,350,0});
  window.draw(trackerPoint);
  }
  for(auto point : sunTrack)
  {
  trackerPoint.setPosition(point*2E-9+VA::Vector3d{350,350,0});
  window.draw(trackerPoint);
  }
  sf::CircleShape ballRender{10, 20};
  ballRender.setFillColor(sf::Color::Yellow);
  ballRender.setPosition(sun.getPosition()*2E-9+VA::Vector3d{340,340,0});
  window.draw(ballRender);
  ballRender.setFillColor(sf::Color::Blue);
  ballRender.setPosition(planet.getPosition()*2E-9+VA::Vector3d{340,340,0});
  window.draw(ballRender);
}

int main() {
  VA::Const::epsilon=5000;
  Particle::Point earth({1.470568E11,0,0},{0,30.28361E3,0},5.726E24);
  std::cout<<"Do you want to change the initial position? [y/n]:";
  char choice;
  std::cin>>choice;
  if(choice=='y')
  {
    std::cout<<"Please insert the initial coordinates (x,y):";
    std::cin>>earth.accPosition().x>>earth.accPosition().y; 
  }
  std::cout<<"Do you want to change the initial velocity? [y/n]:";
  std::cin>>choice;
  if(choice=='y')
  {
    std::cout<<"Please insert the initial veloctity components (x,y):";
    std::cin>>earth.accVelocity().x>>earth.accVelocity().y; 
  }
  std::cout<<"Do you want to change the mass of the Earth? [y/n]:";
  std::cin>>choice;
  if(choice=='y')
  {
    std::cout<<"Please insert the mass:";
    double mass;
    std::cin>>mass;
    earth.setMass(mass); 
    std::cout<< earth.getMass();
  }
  
  sf::RenderWindow window(sf::VideoMode(700, 700), "Orbit");
  printOrbit(earth,window);
  sf::Event event;
  sf::Font font;
      if (!font.loadFromFile("font.ttf"))
       {
         std::cerr<<"Font not loaded!!!";
         return 1;
       }
  while (window.isOpen()) {
      window.clear();
      printOrbit(earth,window);
      double dis=Particle::distance(earth,sun);
        VA::Vector3d force=-1*VA::Const::G*sun.getMass()*earth.getMass()/pow(dis,2)*VA::hat(earth.getPosition()-sun.getPosition());
      earth.evolveDynamics(force);
      sun.evolveDynamics(-force);
      sf::Text text;
      text.setFont(font); 
      text.setCharacterSize(20); 
      text.setFillColor(sf::Color::White);
      text.setString("R:");
      window.draw(text);
      text.move(50,0);
      text.setString(std::to_string(VA::mod(earth.getPosition())));
      window.draw(text);
      text.setPosition(0,20);
      text.setString("V:");
      window.draw(text);
      text.move(50,0);
      text.setString(std::to_string(VA::mod(earth.getVelocity())));
      window.draw(text);
      window.display();
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
      }  
    }
  return 0;
}
