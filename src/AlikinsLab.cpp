#include "AlikinsLab.hpp"


Plugin *plugin;

struct ImageBlankModel : Model
{
	std::string imageFilename;
	ModuleWidget *createModuleWidget() override
	{
		ImageBlank *module = new ImageBlank();
		ImageBlankWidget *moduleWidget = new ImageBlankWidget(module, imageFilename);
		moduleWidget->model = this;
		moduleWidget->imageFilename = imageFilename;
		return moduleWidget;
	}

	ModuleWidget *createModuleWidgetNull() override
	{
		ImageBlankWidget *moduleWidget = new ImageBlankWidget(NULL, imageFilename);
		moduleWidget->model = this;
		moduleWidget->imageFilename = imageFilename;
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
	std::string localPath = "res/blank_panels";
	std::string res_path = p->path + "/" + localPath;

	for (std::string svgPath : systemListEntries(res_path)) {
		if (stringExtension(svgPath) != "svg")
			continue;

		info("Found blank panels at svgPath: %s", svgPath.c_str());
		std::string imageFileBaseName = stringFilename(svgPath);

		debug("Using imageFilename=%s", imageFileBaseName.c_str());

		std::string slugName = stringf("ImagePanel%s", imageFileBaseName.c_str());
		debug("slugName: %s", slugName.c_str());

		std::string name = stringf("Image Panel %s", imageFileBaseName.c_str());
		debug("name: %s", name.c_str());

		std::string pluginRelativeSvgPath = localPath + "/" + imageFileBaseName;
		std::list<ModelTag> tags = {BLANK_TAG};
		// Create a Model instance
		// Model *modelImageBlank = Model::create<ImageBlank, ImageBlankWidget>("AlikinsLab", slugName, name, BLANK_TAG);
		ImageBlankModel *modelImageBlank = new ImageBlankModel();
		modelImageBlank->author = "AlikinsLab";
		modelImageBlank->slug = slugName;
		modelImageBlank->name = name;
		modelImageBlank->tags = tags;
		modelImageBlank->imageFilename = pluginRelativeSvgPath;
		// return ;

		// Add it as a module
		p->addModel(modelImageBlank);

	}
}
