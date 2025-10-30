#include <iostream>
#include <Motor/Motor.hpp>
#include <Juego/Juego.hpp>
#include <Motor/Utils/Utils.hpp>
#include <memory>



int main(int argc, char *argv[]) {

    //crear objeto del motor
    CE::MotorConfig config;
    config.vW=1080;
    config.vH=720;
    config.titulo="CimaEngine";
    std::cout<<"Iniciando "<<config.titulo<<"\n";
    CE::Motor motor{config,std::make_unique<IVJ::Juego>()};

    //CE::Motor motor{config,std::make_unique<IVJ::Infeccion>()};
    return motor.OnRun();
}
