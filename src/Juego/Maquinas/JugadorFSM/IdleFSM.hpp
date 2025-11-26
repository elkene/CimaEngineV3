#pragma once
#include "../FSM.hpp"
namespace IVJ {
class IdleFSM : public FSM {
public:
  explicit IdleFSM();
  FSM* onInputs(const CE::IControl &control) override;
  void onEntrar(const Entidad &obj) override;
  void onSalir(const Entidad &obj) override;
  void onUpdate(Entidad &obj, float dt) override;

private:
  CE::Vector2D ani_frames[4]{};
  float tiempo{};
  int id_actual{};
  float max_tiempo{};
  // sprite ref
  sf::Sprite *sprite{nullptr};
  int s_w{};
  int s_h{};
};
} // namespace IVJ
