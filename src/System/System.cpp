#include "../../inc/System/System.hpp"
#include "../../inc/Functions/EulerDiscretizer.hpp"
#include "../../inc/Functions/VerletDiscretizer.hpp"

namespace NBodyEnv {

  //TODO FIX TEMPLATE

template<>
void System<EulerDiscretizer>::addParticle(Particle particle) {
  _systemParticles.push_back(particle);
  _prevState.push_back(particle);
}

template<>
const Particle &System<EulerDiscretizer>::getParticle(int index) const {
  return _systemParticles[index];
}

template<>
void System<EulerDiscretizer>::printParticles() const{
  for(auto iter=_systemParticles.begin(); iter != _systemParticles.end(); iter++){
    std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
  }  
}

template<>
void System<EulerDiscretizer>::compute() {
  // Save current state in a temp vector
  std::vector<NBodyEnv::Particle> tempState(_systemParticles);

  // Reset forces
  for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
       iter++) {
    iter->setForce({0.0, 0.0, 0.0});
  }

  // Compute system forces
  for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
        iter++)
  {
    bool isP2Visible = true;
    if (!iter->getVisible())
    {
      // particle is not visible, it has previously been absorbed by another particle
      // ==> skip it
      continue;
    }
    for (auto secIter = iter + 1; secIter != _systemParticles.end();
          secIter++)
    {
      // here we still need to call computeForce() on the particle p2, even if it is not visible
      // otherwise we won't update p1
      iter->computeForce(*secIter, _func);
      if (secIter->getVisible() == false)
        isP2Visible = false;
    }
  _discretizer.discretize(*iter, _deltaTime);
  }
}

template<>
void System<VerletDiscretizer>::addParticle(Particle particle) {
  _systemParticles.push_back(particle);
  _prevState.push_back(particle);
}

template<>
const Particle &System<VerletDiscretizer>::getParticle(int index) const {
  return _systemParticles[index];
}

template<>
void System<VerletDiscretizer>::printParticles() const{
  for(auto iter=_systemParticles.begin(); iter != _systemParticles.end(); iter++){
    std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
  }  
}

//TODO the same as above for the collisions

template<>
void System<VerletDiscretizer>::compute() {
  // Save current state in a temp vector
  std::vector<NBodyEnv::Particle> tempState(_systemParticles);

  // Reset forces
  for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
       iter++) {
    iter->setForce({0.0, 0.0, 0.0});
  }

  // Compute system forces
  for (auto iter = _systemParticles.begin(), prevIter = _prevState.begin(); iter != _systemParticles.end();
       iter++, prevIter++) {

    for (auto secIter = iter + 1; secIter != _systemParticles.end();
         secIter++) {
      // Compute new force
      iter->computeForce(*secIter, _func);
    }
    
    if(prevIter->getPos().xPos == 0 && prevIter->getPos().yPos == 0 && prevIter->getPos().zPos == 0){
        _discretizer.updateFirsePos(*iter, _deltaTime);
    } else {
        _discretizer.updatePos(*iter, *prevIter, _deltaTime);
    }

  }

  // Update prev state
  _prevState.clear();
  std::copy(tempState.begin(), tempState.end(), _prevState.begin());
}
} // namespace NBodyEnv
