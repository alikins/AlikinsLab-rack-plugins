#include "rack.hpp"


using namespace rack;

// Forward-declare the Plugin, defined in Template.cpp
extern Plugin *plugin;

// Forward-declare each Model, defined in each module source file
extern Model *modelCableMadness;
extern Model *modelSampleDelay;
extern Model *modelCredits;
extern Model *modelSVGBlank;

struct ImageBlank : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	ImageBlank() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
};

struct ImageBlankWidget : ModuleWidget {
    std::string imageFilename;

	ImageBlankWidget(ImageBlank *module, std::string svgPath);
};
