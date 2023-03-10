#ifndef BE_ENTITY_OPS_COPY_H_INCLUDED
#define BE_ENTITY_OPS_COPY_H_INCLUDED

// #include <vector>
// #include <unordered_map>
// #include "be_entity_interface.h"
// #include "be_timer.h"

#include "tinyxml/tinyxml.h"
#include <sstream>
#include <map>

	class BEntity;
	// class TiXmlElement;
	typedef std::map<BEntity*, BEntity*> Btranslation_map;
	

	class BEntityCopy
	{
			public:
				BEntityCopy() {};
				virtual ~BEntityCopy() {};

				BEntity* copyEntity( BEntity* entity );

			private:
				BEntity* _copyEntity( BEntity* entity, BEntity* to_parent, bool force=false );
				BEntity* _wireNewEntity();
				
				Btranslation_map m_translation_map;

	};

	class BEntitySave
	{
			public:
				BEntitySave() {};
				virtual ~BEntitySave() {};

				void saveEntity( BEntity* entity );
			private:
				void save_entity(BEntity* entity_to_save, std::stringstream& file_content, std::map<unsigned int, BEntity*>& external_entity_list, const bool isBuiltin, const bool isExternal, const unsigned int level);
	};

	class BEntityLoad
	{
			public:
				BEntityLoad() {};
				virtual ~BEntityLoad() {};

				void loadEntity( BEntity* parent, const std::string& filename );
				void loadExternalParentFromXML( BEntity* parent, const TiXmlElement& element, std::map<unsigned int, BEntity*>& external_entity_list);
				void loadEntityFromXML(BEntity* parent, const TiXmlElement& element, std::map<unsigned int, BEntity*>& translation_map, std::map<unsigned int, BEntity*>& external_entity_list, const unsigned int scene_server_client);
				void loadEntityFromXMLConnections(const TiXmlElement& element, std::map<unsigned int, BEntity*>& translation_map);
			private:
				// void save_entity(BEntity* entity_to_save, std::stringstream& file_content, std::map<unsigned int, BEntity*>& external_entity_list, const bool isBuiltin, const bool isExternal, const unsigned int level);
				// Btranslation_map m_translation_map;
	};

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
						*(bool*)(entry.pointer)=(attribute->Value());
						break;
					case eTypeInt:
						*(int*)(entry.pointer)=atoi(attribute->Value()); //boost::lexical_cast<int>(attribute->Value());  //lexical_cast<> is throwing exceptions for int and float
						break;
					case eTypeFloat:
						*(float*)(entry.pointer)=atof(attribute->Value()); //boost::lexical_cast<float>(attribute->Value());
						break;
					case eTypeString:
						*(std::string*)(entry.pointer)=(attribute->Value());
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
