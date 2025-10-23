#include "GLogger.hpp"

#include <imgui-SFML.h>
#include <string>

namespace CE {
    GLogger::GLogger()
        : GLayer()
    { }

    GLogger& GLogger::Get()
    {
        if (!instancia)
            instancia = new GLogger();
        return *instancia;
    }

    void GLogger::OnInit(const MotorConfig& des)
    {
        // Inicialización si se requiere
    }

    void GLogger::OnUpdate(float dt)
    {
        msfps = std::to_string(1.f / dt) + " fps";
    }

    void GLogger::OnRender()
    {
        ImGui::Begin("Log", nullptr, 0);

        // Mostrar FPS
        ImGui::LabelText("", "[%s]", msfps.c_str());

        // Dequeue y mostrar la cola de logs
        while (queue.getSize() > 0)
        {
            auto log = queue.popFrontDato();
            ImVec4 color = nivelColores(log.second);
            ImGui::TextColored(
                color,
                "%10s %s",
                nivelToString(log.second).c_str(),
                log.first.c_str()
            );
        }

        ImGui::End();
    }

    void GLogger::agregarLog(const std::string& log, GLogger::Niveles n)
    {
        queue.agregarDato(std::make_pair(log, n));
    }

    ImVec4 GLogger::nivelColores(Niveles n)
    {
        switch (n)
        {
            case GLogger::Niveles::LOG:         // gris
                return ImVec4(169.f/255.f, 169.f/255.f, 169.f/255.f, 1.f);
            case GLogger::Niveles::LOG_DEBUG:   // amarillo
                return ImVec4(1.f, 1.f, 0.f, 1.f);
            case GLogger::Niveles::LOG_ERROR:   // rojo
                return ImVec4(1.f, 0.f, 0.f, 1.f);
            case GLogger::Niveles::LOG_SEVERO:  // morado
                return ImVec4(148.f/255.f, 0.f, 211.f/255.f, 1.f);
            default:                             // blanco
                return ImVec4(1.f, 1.f, 1.f, 1.f);
        }
    }

    std::string GLogger::nivelToString(Niveles n)
    {
        switch (n)
        {
            case GLogger::Niveles::LOG:        return "[LOG]";
            case GLogger::Niveles::LOG_DEBUG:  return "[DEBUG]";
            case GLogger::Niveles::LOG_ERROR:  return "[ERROR]";
            case GLogger::Niveles::LOG_SEVERO: return "[SEVERO]";
            default:                           return "[ ]";
        }
    }
}
