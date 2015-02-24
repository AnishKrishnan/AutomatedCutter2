#include "../stdafx.h"
#include "ConfigurationManager.h"

const std::string ConfigurationManager::CONFIG_FILE = "app.config";
ConfigurationManager* ConfigurationManager::_configManager = NULL;

ConfigurationManager::ConfigurationManager(void)
{

	std::ifstream inputStream (CONFIG_FILE);
	
	if(!inputStream.is_open())
	{
		throw AutoCutterException("Could not open config file");
	}

	stringstream buffer;
	buffer << inputStream.rdbuf();
	inputStream.close();

	_content = buffer.str();

	_doc.parse<0>(&_content[0]);

	
	_rootNode = _doc.first_node();

}

ConfigurationManager* ConfigurationManager::instance(){

	if(!_configManager)
	{
		_configManager = new ConfigurationManager();
	}

	return _configManager;
}

std::string ConfigurationManager::getValue(std::string& pKey)
{
	return getValue(pKey.c_str());
}

std::string ConfigurationManager::getValue(const char* pKey)
{
	rapidxml::xml_node<>* node = _rootNode->first_node(pKey);

	if(!node)
	{
		throw AutoCutterException("Could not find node [" + string(pKey) + "]");
	}
	std::string value = node->value();

	return value;
}