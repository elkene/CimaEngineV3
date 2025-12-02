#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <string>
#include "../Utils/Vector2D.hpp"

namespace CE
{
    class GestorAssets
    {
    public:
        static GestorAssets& Get();

        void agregarFont(const std::string& key, const std::string& filepath);

        void agregarTextura(const std::string& key, const std::string& filepath,
                            const CE::Vector2D& pos_init, const CE::Vector2D& dim);

        void agregarSonido(const std::string& key, const std::string& filepath);

        void agregarMusica(const std::string& key, const std::string& filepath);

        sf::Font& getFont(const std::string& key)
        {
            return *hashFonts[key];
        }

        sf::Texture& getTextura(const std::string& key)
        {
            return *hashTexturas[key];
        }

        sf::Sound& getSonido(const std::string& key)
        {
            return *hashSonidos[key];
        }

        sf::Music& getMusica(const std::string& key)
        {
            return *hashMusica[key];
        }

    private:

        // ---- MAPAS DE RECURSOS ----
        std::map<std::string, std::shared_ptr<sf::Font>>        hashFonts;
        std::map<std::string, std::shared_ptr<sf::Texture>>     hashTexturas;

        // ¡NUEVO! Necesario para NO compartir un mismo buffer
        std::map<std::string, std::shared_ptr<sf::SoundBuffer>> hashBuffers;

        // Sonido (sf::Sound necesita su *propio* buffer)
        std::map<std::string, std::shared_ptr<sf::Sound>>       hashSonidos;

        // Música (streaming)
        std::map<std::string, std::shared_ptr<sf::Music>>       hashMusica;

        // Singleton
        static inline GestorAssets* instancia = nullptr;
    };
}
