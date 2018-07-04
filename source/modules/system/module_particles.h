#pragma once

#include "modules/module.h"

namespace Particles
{
  struct TCoreSystem;
  class CSystem;
  using TParticleHandle = int;
}

class CModuleParticles : public IModule
{
public:
  CModuleParticles(const std::string& name);
  bool start() override;
  bool stop() override;
  void update(float delta) override;
  void render() override;

  Particles::TParticleHandle launchSystem(const std::string& name, CHandle entity = CHandle());
  Particles::TParticleHandle launchSystem(const Particles::TCoreSystem* cps, CHandle entity = CHandle());
  void kill(Particles::TParticleHandle ph, float fade_out = 0.f);

  const VEC3& getWindVelocity() const;

private:
  std::vector<Particles::CSystem*> _activeSystems;
  VEC3                             _windVelocity = VEC3::Zero;
  Particles::TParticleHandle       _lastHandle;
};