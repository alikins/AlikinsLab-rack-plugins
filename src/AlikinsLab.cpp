#include "AlikinsLab.hpp"


Plugin *plugin;


void init(Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);

	// Add all Models defined throughout the plugin
	p->addModel(modelCableMadness);
	p->addModel(modelSampleDelay);
	p->addModel(modelCredits);

	std::string res_path = "res/blank_panels/";
	for (std::string packagePath : systemListEntries(res_path)) {
		if (stringExtension(packagePath) != "svg")
			continue;

		info("Found blank panels %s", packagePath.c_str());
		std::string imageFilename = stringFilename(packagePath);

		debug("Using imageFilename=%s", imageFilename.c_str());

		std::string slugName = stringf("ImagePanel%s", imageFilename.c_str());
		debug("slugName: %s", slugName.c_str());

		std::string name = stringf("Image Panel %s", imageFilename.c_str());
		debug("name: %s", name.c_str());

		std::list<ModelTag> tags = {BLANK_TAG};
		// Create a Model instance
		// Model *modelImageBlank = Model::create<ImageBlank, ImageBlankWidget>("AlikinsLab", slugName, name, BLANK_TAG);
		Model *modelImageBlank = new Model();
		modelImageBlank->author = "AlikinsLab";
		modelImageBlank->slug = slugName;
		modelImageBlank->name = name;
		modelImageBlank->tags = tags;
		// return ;

		// Add it as a module
		p->addModel(modelImageBlank);

	}
}
