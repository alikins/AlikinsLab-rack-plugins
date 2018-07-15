#include "AlikinsLab.hpp"

/*
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
*/

/*
struct ImageBlankWidget : ModuleWidget {
	ImageBlankWidget(ImageBlank *module, std::string imageFilename);
};
*/

ImageBlankWidget::ImageBlankWidget(ImageBlank *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, imageFilename)));

	addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

}

// Model *modelCableMadness = Model::create<CableMadness, CableMadnessWidget>("AlikinsLab", "CableMadness", "Cable Madness", OSCILLATOR_TAG);
