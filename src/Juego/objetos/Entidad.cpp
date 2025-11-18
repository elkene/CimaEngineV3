#include "Entidad.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"

  namespace IVJ {
  void Entidad::onUpdate(float dt) {
    // Revisar si tiene ciertos componentes
    // para actualizarlo debidamente
    // o hacer una clase hija y ahi revisarla
    if (tieneComponente<CE::ISprite>()) {
      auto sprite = getComponente<CE::ISprite>();
      auto pos = getTransformada()->posicion;
      sprite->m_sprite.setPosition({pos.x, pos.y});
    }
    if (tieneComponente<IVJ::IMaquinaEstado>()) {
      auto mq = getComponente<IVJ::IMaquinaEstado>();
      if (mq->fsm)
        mq->fsm->onUpdate(*this, dt);
    }
  }
  void Entidad::inputFSM() {
    if (!getComponente<IMaquinaEstado>() || !getComponente<CE::IControl>() ||
        !getComponente<IMaquinaEstado>()->fsm)
      return;
    auto mq = getComponente<IMaquinaEstado>();
    // Crear el nuevo estado, si es nulo no hay nuevo estado aun.
    auto control = *getComponente<CE::IControl>();
    auto n_estado = mq->fsm->onInputs(control);
    std::shared_ptr<FSM> estado(n_estado);
    if (estado)
        setFSM(estado);
  }
    void Entidad::setFSM(const std::shared_ptr<FSM> &mq)
    {
      auto &estado_actual=getComponente<IMaquinaEstado>()->fsm;
      //transicion de salida
      estado_actual->onSalir(*this);
      //transicion de entrada a otro estado
      estado_actual=mq;
    estado_actual->onEntrar(*this);
    }

  void Entidad::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    // Revisar si tiene ciertos componentes
    // para actualizarlo debidamente
    // o hacer una clase hija y ahi revisarla
    if (tieneComponente<CE::ISprite>()) {
      auto sprite = getComponente<CE::ISprite>();
      target.draw(sprite->m_sprite);
    }
  }

} // namespace IVJ
