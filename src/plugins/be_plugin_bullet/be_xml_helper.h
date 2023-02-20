#ifndef BE_XML_HELPER_H_INCLUDED
#define BE_XML_HELPER_H_INCLUDED

#include "tinyxml/tinyxml.h"
#include <map>
// #include <string>
#include <boost/lexical_cast.hpp>

class BeXmlHelper
{

	enum Type
	{
		eTypeBool,
		eTypeInt,
		eTypeFloat,
		eTypeString
	};

	struct Entry
	{
		void* pointer;
		Type type;
	};

	typedef std::map<std::string, Entry> EntryMap;

	EntryMap m_entryMap;

public:

	BeXmlHelper()
	{
	}

	void addBool(const char* const name, bool& value)
	{
		addEntry(name, &value, eTypeBool);
	}

	void addInt(const char* const name, int& value)
	{
		addEntry(name, &value, eTypeInt);
	}

	void addFloat(const char* const name, float& value)
	{
		addEntry(name, &value, eTypeFloat);
	}

	void addString(const char* const name, std::string& value)
	{
		addEntry(name, &value, eTypeString);
	}

	void parse( const TiXmlElement& element )
	{
		const TiXmlAttribute* attribute=element.FirstAttribute();
		while(attribute)
		{
			EntryMap::iterator iterator=m_entryMap.find(attribute->Name());
			if(iterator!=m_entryMap.end())
			{
				Entry& entry=iterator->second;
				switch(entry.type)
				{
				case eTypeBool:
					*(bool*)(entry.pointer)=boost::lexical_cast<bool>(attribute->Value());
					break;
				case eTypeInt:
					*(int*)(entry.pointer)=atoi(attribute->Value()); //boost::lexical_cast<int>(attribute->Value());  //lexical_cast<> is throwing exceptions for int and float
					break;
				case eTypeFloat:
					*(float*)(entry.pointer)=static_cast<float>(atof(attribute->Value())); //boost::lexical_cast<float>(attribute->Value());
					break;
				case eTypeString:
					*(std::string*)(entry.pointer)=boost::lexical_cast<std::string>(attribute->Value());
					break;
				default:
					assert(0);
				}
			}
			attribute=attribute->Next();
		}
	}

private:

	void addEntry( const char* const name, void* const pointer, const Type type )
	{
		Entry entry;
		entry.pointer=pointer;
		entry.type=type;
		m_entryMap[std::string(name)]=entry;
	}

};

#endif
 
