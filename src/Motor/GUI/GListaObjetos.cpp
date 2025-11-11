#include "GListaObjetos.hpp"
#include "../Camaras/CamarasGestor.hpp"
#include <imgui.h>
#include "Motor/Primitivos/GestorEscenas.hpp"
#include <imgui-SFML.h>

namespace CE
{
    void GListaObjetos::OnInit(const MotorConfig& des) { }
    void GListaObjetos::OnUpdate(float dt) { }

    void GListaObjetos::OnRender(void)
    {
        ImGui::Begin("Objetos", nullptr, 0);

        static int id_escena_actual = 0;
        auto lista = GestorEscenas::Get().getKeys();
        const char* str_escena = GestorEscenas::Get().getEscenaActual().nombre.c_str();

        // --- Selector de escena ---
        if (ImGui::BeginCombo("Escenas", str_escena, 0))
        {
            for (int i = 0; i < lista.size(); ++i)
            {
                const bool seleccion = (id_escena_actual == i);
                if (ImGui::Selectable(lista[i].c_str(), seleccion))
                    id_escena_actual = i;

                if (seleccion)
                    ImGui::SetItemDefaultFocus();
            }

            GestorEscenas::Get().cambiarEscena(lista[id_escena_actual]);
            ImGui::EndCombo();
        }

        // --- Lista de objetos de la escena actual ---
        if (ImGui::TreeNode("Objetos"))
        {
            auto& pool = GestorEscenas::Get().getEscenaActual().getPool();

            for (auto& obj : pool.getPool())
            {
                if (ImGui::Button(obj->toString().c_str()))
                {
                    GestorCamaras::Get().getCamaraActiva().lockEnObjeto(obj);
                }
            }

            ImGui::TreePop();
        }

        ImGui::End();
    }



}
