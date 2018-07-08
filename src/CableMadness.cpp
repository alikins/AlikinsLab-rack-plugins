#include "AlikinsLab.hpp"

struct CableMadness : Module {
	enum ParamIds {
		TENSION_PARAM,
		OPACITY_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		TENSION_INPUT,
		OPACITY_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	// float tension = 0.5;
	// float opacity = 0.5;

	CableMadness() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

};


void CableMadness::step() {

    if (inputs[TENSION_INPUT].active) {
        params[TENSION_PARAM].value = inputs[TENSION_INPUT].value;
    }

	if (inputs[OPACITY_INPUT].active) {
        params[OPACITY_PARAM].value = inputs[OPACITY_INPUT].value;
    }

	float in_tension = clamp(params[TENSION_PARAM].value, 0.0f, 10.0f);
	float in_opacity = clamp(params[OPACITY_PARAM].value, 0.0f, 10.0f);

	float tension = rescale(in_tension, 0.0f, 10.0f, 0.0f, 1.0f);
	float opacity = rescale(in_opacity, 0.0f, 10.0f, 0.0f, 100.0f);

	// Kind of overkill to do this at audio rate but this is
	// a pretty ridiculous concept to start with...
	gToolbar->wireTensionSlider->value = tension;
	gToolbar->wireOpacitySlider->value = opacity;

}

struct CableMadnessWidget : ModuleWidget {
	CableMadnessWidget(CableMadness *module);
};

CableMadnessWidget::CableMadnessWidget(CableMadness *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, "res/CableMadness.svg")));

	addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

	addParam(ParamWidget::create<Davies1900hBlackKnob>(Vec(25, 95), module, CableMadness::TENSION_PARAM, 0.0f, 10.0f, 0.5));
	addInput(Port::create<PJ301MPort>(Vec(29, 140), Port::INPUT, module, CableMadness::TENSION_INPUT));

	addParam(ParamWidget::create<Davies1900hBlackKnob>(Vec(25, 220), module, CableMadness::OPACITY_PARAM, 0.0f, 10.0f, 0.5));
	addInput(Port::create<PJ301MPort>(Vec(29, 265), Port::INPUT, module, CableMadness::OPACITY_INPUT));
}

Model *modelCableMadness = Model::create<CableMadness, CableMadnessWidget>("AlikinsLab", "CableMadness", "Cable Madness", OSCILLATOR_TAG);
