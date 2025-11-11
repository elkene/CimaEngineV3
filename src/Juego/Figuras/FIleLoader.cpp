#include "FIleLoader.hpp"
#include <Juego/Figuras/Figura.hpp>
#include <iostream>
#include <fstream>

namespace ARCHIVOS
{
    FIleLoader::FIleLoader(const std::string& pathfile)
        :archivo{pathfile}{}
    FIleLoader::~FIleLoader()
    {
        lista.clear();
    }

    std::vector<std::shared_ptr<CE::Objeto>> FIleLoader::LoadFile()
    {
        std::ifstream elarchivo(archivo);
        if (!elarchivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo: " << this->archivo << "\n";
            return {};
        }

        std::vector<std::shared_ptr<CE::Objeto>> listaFiguras;
        std::string tipo;
        bool primerTipo = true;

        while (elarchivo >> tipo) {

            if (primerTipo) {
                if (tipo.size() >= 3 &&
                    (unsigned char)tipo[0] == 0xEF &&
                    (unsigned char)tipo[1] == 0xBB &&
                    (unsigned char)tipo[2] == 0xBF) {
                    tipo = tipo.substr(3);
                    }
                primerTipo = false;
            }

            std::shared_ptr<IVJ::Figuras> figura;

            if (tipo == "Rectangulo") {
                figura = std::make_shared<IVJ::Rectangulo>();
              } else if (tipo == "Circulo") {
                    figura = std::make_shared<IVJ::Circulo>();
                } else if (tipo == "Triangulo") {
                    figura = std::make_shared<IVJ::Triangulo>();
                } else {
                    std::cerr << "Tipo desconocido: '" << tipo << "'\n";
                    continue;
                }

                figura->loadFromFile(elarchivo); // cargar parámetros restantes
                listaFiguras.push_back(figura);
            }

            return listaFiguras;
        }
    }
