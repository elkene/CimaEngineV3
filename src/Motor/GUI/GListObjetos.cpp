#include "GListObjetos.hpp"
#include "../Camaras/CamarasGestor.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

namespace CE
{
    void GListaObjetos::OnInit(const MotorConfig& des) { }

    void GListaObjetos::OnUpdate(float dt) { }

    void GListaObjetos::OnRender(void)
    {
        ImGui::Begin("Objetos", nullptr, 0);

        if (ImGui::TreeNode("Camaras"))
        {
            auto camaras=GestorCamaras::Get().getListaCamaras();
            for (int i = 0; i < camaras.size(); i++)
            {
                auto cam = camaras[i];
                auto strCam = cam->nombre;

                // Color del botón
                if (cam->estaActivo)
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, 0xff00A5FF);
                    ImGui::PushStyleColor(ImGuiCol_Text, 0xff000000);
                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, 0xffffbf00);
                    ImGui::PushStyleColor(ImGuiCol_Text, 0xff000000);
                }

                bool boton = ImGui::Button(strCam.c_str(), ImVec2(150, 30));
                if (boton)
                {
                    GestorCamaras::Get().setCamaraActiva(i);
                }

                ImGui::PopStyleColor(2);
            }
            ImGui::TreePop();
            ImGui::Spacing();
        }

        if (ImGui::TreeNode("Objetos"))
        {
            // Más adelante se implementará para que
            // muestre los objetos de la escena
            ImGui::TreePop();
        }

        ImGui::End();
    }
}
