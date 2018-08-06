#include "AlikinsLab.hpp"


struct SVGBlank : Module {
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

    json_t *toJson() override;
    void fromJson(json_t *rootJ) override;

	SVGBlank() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
};

const char *moduleJson

json_t* SVGBlank::toJson() {
    json_t *rootJ = json_object();
    json_object_set_new(rootJ, "inputRange", json_integer(inputRange));
    json_object_set_new(rootJ, "colorMode", json_integer(colorMode));

    return rootJ;
}

void SVGBlank::fromJson(json_t *rootJ) {
	json_t *svgDataJ = json_object_get(rootJ, "SVGData");
    if (svgDataJ) {
        svgData = json_string_value(svgDataJ);
        // setModel(json_string_value(nameJ));
    }

}

struct SVGBlankWidget : ModuleWidget {
	std::string SVGData;
	SVGBlankWidget(SVGBlank *module);
};


SVGBlankWidget::SVGBlankWidget(SVGBlank *module) : ModuleWidget(module) {
	debug("SVGBlank");
	//debug("SVGBlankWidget constr imageFilename: %s", imageFilename.c_str());
	setPanel(SVG::load(assetPlugin(plugin, "res/SVGBlank.svg")));

	addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

}

Model *modelSVGBlank = Model::create<SVGBlank, SVGBlankWidget>("AlikinsLab", "SVGBlank", "SVG Panel", BLANK_TAG);
