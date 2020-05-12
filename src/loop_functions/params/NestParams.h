#ifndef NEST_PARAMS_H
#define NEST_PARAMS_H

#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class NestParams {

	private:
		// Params
		CVector2 size;

	public:
		// Constructors
		NestParams();

		// Getters
		const CVector2& getSize() const;

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif