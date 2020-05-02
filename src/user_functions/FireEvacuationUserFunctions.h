#ifndef FIRE_EVACUATION_USER_FUNCTIONS_H
#define FIRE_EVACUATION_USER_FUNCTIONS_H

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include "params/DividerParams.h"

using namespace argos;

class FireEvacuationUserFunctions : public CQTOpenGLUserFunctions {

	private:
		// Params
		DividerParams dividerParams;

	public:
		// Simulator methods
		virtual void Init(TConfigurationNode &configurationNode);
		virtual void DrawInWorld();

};

#endif