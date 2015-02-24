
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "AutoCutterException.h"
//#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"

class ConfigurationManager
{
public:

	std::string getValue(const char* pKey);
	std::string getValue(std::string& pKey);
	static ConfigurationManager* instance();

	static void create();
private:
	ConfigurationManager(void);
	ConfigurationManager(ConfigurationManager const&);
	ConfigurationManager& operator=(ConfigurationManager const&);


	static const std::string CONFIG_FILE;
	static ConfigurationManager* _configManager;

	std::string _content;
	rapidxml::xml_document<> _doc;
	rapidxml::xml_node<>* _rootNode;


};

