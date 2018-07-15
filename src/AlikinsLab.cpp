#include "AlikinsLab.hpp"


Plugin *plugin;

struct ImageBlankModel : Model
{
	std::string imageFilename;
	ModuleWidget *createModuleWidget() override
	{
		ImageBlank *module = new ImageBlank();
		ModuleWidget *moduleWidget = new ImageBlankWidget(module);
		moduleWidget->model = this;
		return moduleWidget;
	}

	ModuleWidget *createModuleWidgetNull() override
	{
		ModuleWidget *moduleWidget = new ImageBlankWidget(NULL);
		moduleWidget->model = this;
		return moduleWidget;
	}
};

void
init(Plugin *p)
{
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);

	// Add all Models defined throughout the plugin
	p->addModel(modelCableMadness);
	p->addModel(modelSampleDelay);
	p->addModel(modelCredits);

	debug("plugin path: %s", p->path.c_str());
	std::string res_path = p->path + "/" + "res/blank_panels/";
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
		ImageBlankModel *modelImageBlank = new ImageBlankModel();
		modelImageBlank->author = "AlikinsLab";
		modelImageBlank->slug = slugName;
		modelImageBlank->name = name;
		modelImageBlank->tags = tags;
		modelImageBlank->imageFilename = imageFilename;
		// return ;

		// Add it as a module
		p->addModel(modelImageBlank);

	}
}
