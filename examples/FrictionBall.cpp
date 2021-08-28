#include <CppPhysics/Particle.hpp>
#include <SFML/Graphics.hpp>
#include <VectorAlgebra.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
  Particle::Point ball{{3, 3, 0}, {10, 10, 0}, 10, 0};
  sf::RenderWindow window(sf::VideoMode(600, 600), "FrictionBall");
  sf::CircleShape ballRender{30, 20};
  ballRender.setFillColor(sf::Color::Green);
  ballRender.setPosition({ball.getPosition().x*100, ball.getPosition().y*100});
  window.draw(ballRender);
  window.display();
  sf::Event event;
  while (window.isOpen()) {
    double mu;
    std::cin >> mu >> ball.accVelocity().x >> ball.accVelocity().y;
    while (ball.compute(Particle::Info::Speed)> 0.1 && window.isOpen()) {
      window.clear();
      ballRender.setPosition({ball.getPosition().x*100, ball.getPosition().y*100});
      window.draw(ballRender);
      window.display();
      VA::Vector3d force =
          -1 * VA::hat(ball.getVelocity()) * ball.getMass() * 9.81 * mu;

      ball.evolveDynamics(force);
      if (ball.getPosition().x <= 0 ||
          ball.getPosition().x*100 >= window.getSize().x-60) {
        ball.accVelocity().x *= -1;
      }
      if (ball.getPosition().y <= 0 ||
          ball.getPosition().y*100 >= window.getSize().y-60) {
        ball.accVelocity().y *= -1;
      }
      std::cout<<"V="<<ball.getVelocity()<<"    |V|="<<ball.compute(Particle::Info::Speed)<<'\n';
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }
    }
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }
  }
  return 0;
}
