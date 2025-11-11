#pragma once

#include <string>
#include <memory>
#include <vector>
#include <Juego/Figuras/Figura.hpp>

namespace ARCHIVOS
{
    class FIleLoader
    {
        ;
    public:
        FIleLoader(const std::string& pathfile);
        ~FIleLoader();
        std::vector<std::shared_ptr<CE::Objeto>> LoadFile();
    private:
        std::vector<std::shared_ptr<CE::Objeto>> lista;
        std::string archivo;
    };
};