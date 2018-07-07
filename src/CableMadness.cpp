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
		BLINK_LIGHT,
		NUM_LIGHTS
	};

	float tension = 0.5;
	float opacity = 0.5;

	CableMadness() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - onReset, onRandomize, onCreate, onDelete: implements special behavior when user clicks these from the context menu
};


void CableMadness::step() {

    if (inputs[TENSION_INPUT].active) {
        params[TENSION_PARAM].value = inputs[TENSION_INPUT].value;
    }

	if (inputs[OPACITY_INPUT].active) {
        params[OPACITY_PARAM].value = inputs[OPACITY_INPUT].value;
    }

	tension = params[TENSION_PARAM].value;
	opacity = params[OPACITY_PARAM].value;

	gToolbar->wireTensionSlider->setValue(tension);
	gToolbar->wireOpacitySlider->setValue(opacity * 100.0f);

}


struct CableMadnessWidget : ModuleWidget {
	CableMadnessWidget(CableMadness *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/CableMadness.svg")));

		addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(ParamWidget::create<Davies1900hBlackKnob>(Vec(4, 87), module, CableMadness::TENSION_PARAM, 0.0f, 1.0f, 0.5));
		addParam(ParamWidget::create<Davies1900hBlackKnob>(Vec(44 - 4, 87), module, CableMadness::OPACITY_PARAM, 0.0f, 1.0f, 0.5));

		addInput(Port::create<PJ301MPort>(Vec(4, 186), Port::INPUT, module, CableMadness::TENSION_INPUT));
		addInput(Port::create<PJ301MPort>(Vec(44, 186), Port::INPUT, module, CableMadness::OPACITY_INPUT));

		addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(41, 59), module, CableMadness::BLINK_LIGHT));
	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelCableMadness = Model::create<CableMadness, CableMadnessWidget>("AlikinsLab", "CableMadness", "Cable Madness", OSCILLATOR_TAG);
