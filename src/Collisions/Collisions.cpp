#include "../../inc/Collisions/Collisions.hpp"
#include <iostream>
#include <math.h>

namespace NBodyEnv {
void Collisions::elasticCollision(Particle &p1, Particle &p2) {
  // print collision position
  std::cout << "Elastic collision at: " << p1.getPos().xPos << ", "
            << p1.getPos().yPos << ", " << p1.getPos().zPos << std::endl;
  // print particles velocities
  // std::cout << "P1 velocity: " << p1.getVel().xVel << ", " <<
  // p1.getVel().yVel << ", " << p1.getVel().zVel << std::endl; std::cout << "P2
  // velocity: " << p2.getVel().xVel << ", " << p2.getVel().yVel << ", " <<
  // p2.getVel().zVel << std::endl;

  // need to compute the new velocities of the particles
  double totMass = p1.getSpecInfo() + p2.getSpecInfo();
  double massDiffP1P2 = p1.getSpecInfo() - p2.getSpecInfo();
  double massDiffP2P1 = p2.getSpecInfo() - p1.getSpecInfo();
  double xVelP1 = massDiffP1P2 / totMass * p1.getVel().xVel +
                  2 * p2.getSpecInfo() / totMass * p2.getVel().xVel;

  double yVelP1 = massDiffP1P2 / totMass * p1.getVel().yVel +
                  2 * p2.getSpecInfo() / totMass * p2.getVel().yVel;

  double zVelP1 = massDiffP1P2 / totMass * p1.getVel().zVel +
                  2 * p2.getSpecInfo() / totMass * p2.getVel().zVel;

  // same for P2
  double xVelP2 = massDiffP2P1 / totMass * p2.getVel().xVel +
                  2 * p1.getSpecInfo() / totMass * p1.getVel().xVel;

  double yVelP2 = massDiffP2P1 / totMass * p2.getVel().yVel +
                  2 * p1.getSpecInfo() / totMass * p1.getVel().yVel;

  double zVelP2 = massDiffP2P1 / totMass * p2.getVel().zVel +
                  2 * p1.getSpecInfo() / totMass * p1.getVel().zVel;

  // set new velocities
  p1.setVel({xVelP1, yVelP1, zVelP1});
  p2.setVel({xVelP2, yVelP2, zVelP2});

  // print new velocities
  // std::cout << "P1 velocity: " << p1.getVel().xVel << ", " <<
  // p1.getVel().yVel << ", " << p1.getVel().zVel << std::endl; std::cout << "P2
  // velocity: " << p2.getVel().xVel << ", " << p2.getVel().yVel << ", " <<
  // p2.getVel().zVel << std::endl;
}

void Collisions::inelasticCollision(Particle &p1, Particle &p2) {
  // NOTE: here we consider a PERFECTLY INELASTIC COLLISION, so the two
  // particles will merge into one with the sum of their masses and the velocity
  // of the new particle will be the average of the two print collision position
  std::cout << "Inelastic collision at: " << p1.getPos().xPos << ", "
            << p1.getPos().yPos << ", " << p1.getPos().zPos << std::endl;

  // compute total mass
  double totMass = p1.getSpecInfo() + p2.getSpecInfo();
  double xVel = (p1.getSpecInfo() * p1.getVel().xVel +
                 p2.getSpecInfo() * p2.getVel().xVel) /
                totMass;
  double yVel = (p1.getSpecInfo() * p1.getVel().yVel +
                 p2.getSpecInfo() * p2.getVel().yVel) /
                totMass;
  double zVel = (p1.getSpecInfo() * p1.getVel().zVel +
                 p2.getSpecInfo() * p2.getVel().zVel) /
                totMass;

  // set new velocity and mass for the first particle, which will be the merged
  // one
  p1.setSpecInfo(totMass);
  p1.setVel({xVel, yVel, zVel});

  // compute mass density of both particles ==> d = m/V = m / (4/3 * pi * r^3)
  double massDensityP1 = p1.getSpecInfo() / (4.0 / 3.0 * M_PI * p1.getRadius() *
                                             p1.getRadius() * p1.getRadius());
  double massDensityP2 = p2.getSpecInfo() / (4.0 / 3.0 * M_PI * p2.getRadius() *
                                             p2.getRadius() * p2.getRadius());

  // compute mass density of the merged particle as average of the two
  double massDensityMerged = massDensityP1 + massDensityP2 / 2.0;

  // compute new radius and set it by reverting the previous formula ==> r =
  // (3/4 * pi * m / d)^(1/3)
  double newRadius =
      pow(3.0 / (4.0 * M_PI) * totMass / massDensityMerged, 1.0 / 3.0);
  p1.setRadius(newRadius);

  // TODO: before being able to use this, we need to modify the System class to
  // be able to remove particles
}

} // namespace NBodyEnv
