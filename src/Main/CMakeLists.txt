project(CimaEngine3v)

add_executable(CimaEngine3v main.cpp
        ../Motor/App/App.hpp
        ../Motor/Primitivos/Objetos.cpp
        ../Motor/Primitivos/Objetos.hpp
        ../Juego/Figuras/Figura.cpp
        ../Juego/Figuras/Figura.hpp
        ../Juego/Figuras/FIleLoader.cpp
        ../Juego/Figuras/FIleLoader.hpp
        ../Motor/Utils/Vector2D.cpp
        ../Motor/Utils/Vector2D.hpp
        ../Juego/Componentes/JComponentes.cpp
        ../Juego/Componentes/JComponentes.hpp
        ../Motor/Componentes/IComponentes.cpp
        ../Motor/Componentes/IComponentes.hpp
        ../Juego/Sistema/Sistema.cpp
        ../Juego/Sistema/Sistema.hpp
        ../Juego/Transformada/Transformada.cpp
        ../Juego/Transformada/Transformada.h
        ../Motor/Camaras/Camaras.hpp
        ../Motor/Camaras/CamarasGestor.hpp
        ../Motor/GUI/GListObjetos.hpp
)