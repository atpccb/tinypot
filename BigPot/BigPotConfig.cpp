#include "BigPotConfig.h"

BigPotConfig BigPotConfig::_config;

BigPotConfig::BigPotConfig()
{
	_this = &_config;
	//init();
}


BigPotConfig::~BigPotConfig()
{
	//delete doc;
	//write();
}

void BigPotConfig::init(const string& filepath)
{
#ifdef USINGJSON
	_filename = _filepath + "/config.json";
	printf("try find config file: %s\n", _filename.c_str());
	
	Json::Reader reader;
	_content = readStringFromFile(_filename);
	reader.parse(_content, _value);

	if (_value["record"].isObject())
		_record = _value["record"];
#else
	_filename = filepath + "/config.xml";
	printf("try find config file: %s\n", _filename.c_str());
	_doc.LoadFile(_filename.c_str());
#ifdef _DEBUG
	//_doc.Print();
#endif
	//��ʼ���ṹ
	if (_doc.Error())
	{
		//_doc.DeleteChildren();
		_doc.LinkEndChild(_doc.NewDeclaration());
		_root = _doc.NewElement("root");
	}
	else
	{
		_root = _doc.FirstChildElement("root");
	}

	_record = _root->FirstChildElement("record");
	if (!_record)
		_record = _root->InsertFirstChild(_doc.NewElement("record"))->ToElement();
#endif
}

void BigPotConfig::write()
{
#ifdef USINGJSON
	Json::StyledWriter writer;

	_value["record"] = _record;
	_content = writer.write(_value);

	ofstream ofs;
	ofs.open(_filename);
	ofs << _content;
#else
	//_doc.LinkEndChild(_doc.NewDeclaration());
	_doc.LinkEndChild(_root);
	_doc.SaveFile(_filename.c_str());
#endif
}

XMLElement* BigPotConfig::getElement(XMLElement *parent, const char * name)
{
	auto p = parent->FirstChildElement(name);
	if (p)
	{
		return p;
	}
	else
	{
		p = parent->InsertFirstChild(_doc.NewElement(name))->ToElement();
		p->SetText("");
		return p;
	}
}

