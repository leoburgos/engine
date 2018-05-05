#pragma once

#include "modules/module.h"
#include "gui/gui_widget.h"
#include "utils/variant.h"
#include "gui/gui_controller.h"
#include "gui/controllers/gui_main_menu_controller.h"

using namespace GUI;

class CModuleGUI : public IModule
{
public:
  CModuleGUI(const std::string& name);
  bool start() override;
  bool stop() override;
  void update(float delta) override;
  void renderGUI() override;

  void desactiveMainMenu();

  // widget management
  void registerWidget(GUI::CWidget* wdgt);
  GUI::CWidget* getWidget(const std::string& name, bool recursive = false) const;
  void activateWidget(const std::string& name);
  void removeWidget(const std::string& name);

  // controller management
  void registerController(GUI::CController* controller);
  void unregisterController(GUI::CController* controller);

  CCamera& getCamera();
  MVariants& getVariables();

  void renderTexture(const MAT44& world, const CTexture* texture, const VEC2& minUV, const VEC2& maxUV, const VEC4& color);
  void renderText(const MAT44& world, const std::string& text, const VEC4& color);

private:
  CCamera _orthoCamera;
  const CRenderTechnique* _technique = nullptr;
  const CRenderMesh* _quadMesh = nullptr;
  const CTexture* _fontTexture = nullptr;
  
  CMainMenuController* mmc;

  GUI::VWidgets _registeredWidgets;
  GUI::VWidgets _activeWidgets;
  MVariants _variables;
  GUI::VControllers _controllers;
};
