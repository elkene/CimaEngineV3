#pragma once
#include <string>
#include <Motor/App/ALayer.hpp>
#include <Motor/Utils/Utils.hpp>
#include <Motor/GUI/GLayer.hpp>
#include <memory>
#include <vector>
namespace CE {
    class Motor {
        public:
            Motor(const MotorConfig& config,std::unique_ptr<GameLayer> ref);
            int OnRun(void);
    private:
        void OnInit(void);
        void OnEventFrame(float dt);
        void OnUpdateFrame(float dt);
        void OnRenderFrame(float dt);
    private:
        MotorConfig motor_info;
        //apuntador al juego
        std::unique_ptr<GameLayer> mi_app;
        //lista de objetos de GUI
        std::vector<std::shared_ptr<GLayer>> gui_layers;

    };
}