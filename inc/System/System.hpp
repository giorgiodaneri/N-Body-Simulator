#ifndef SYSTEM
#define SYSTEM

#include "../Particle/Particle.hpp"
#include <functional>
#include <iostream>
#include <vector>

namespace NBodyEnv {
class System {
public:
  System(std::function<void(Particle &, Particle &)> func, double deltaTime)
      : _func(func), _deltaTime(deltaTime){};
  ~System() = default;
  void compute();
  void addParticle(Particle particle);
  const Particle &getParticle(int index) const;
  const std::vector<Particle> &getParticles() const { return _systemParticles; }
  const std::vector<Particle> &getPrevState() const { return _prevState; }

private:
  std::vector<NBodyEnv::Particle> _prevState;
  std::vector<NBodyEnv::Particle> _systemParticles;
  std::function<void(Particle &, Particle &)> _func;
  double _deltaTime;
};
} // namespace NBodyEnv

#endif