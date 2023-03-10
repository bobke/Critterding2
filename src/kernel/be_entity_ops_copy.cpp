#include "be_entity_ops_copy.h"
#include "be_entity_core_types.h"
#include "be_entity_io_handler.h"
// #include "be_entity_children_handler.h"
// #include <iostream>
#include <fstream>
// #include <iostream>
// #include <typeinfo>

	// COPY
	BEntity* BEntityCopy::copyEntity( BEntity* entity )
	{
		// PREPARE
			m_translation_map.clear();

		// COPY
			auto entity_new = _copyEntity( entity, entity->parent(), true );

		// WIRE
			_wireNewEntity();

		// PRINT ORIGINAL
			// entity_new->childHandler()->print( entity, 5 );
			
		// PRINT NEW
			// entity_new->childHandler()->print( entity_new, 5 );
			
		// exit(0);
		
		return entity_new;
	}
	
	BEntity* BEntityCopy::_copyEntity( BEntity* entity, BEntity* to_parent, bool force )
	{
		// IDENTIFY AND ADD NEW CHILD TO TO_PARENT
		BEntity* entity_new(0);

		// IF BUILTIN FIND IT
		if ( !force && entity->isBuiltin() )
		{
			entity_new = to_parent->getChild( entity->name().c_str(), 1 );  // FIXME
		}
		// IF NOT BUILTIN CREATE IT
		else
		{
			// EXTERNAL CHILD
			if ( dynamic_cast<BEntity_external*>( entity ) )
			{
				auto entity_referenced = entity->get_reference();

				entity_new = to_parent->addChild( entity->name(), new BEntity_external() );
				auto entity_referenced_new = _copyEntity( entity_referenced, entity_referenced->parent(), true );

				entity_new->set( entity_referenced_new );
			}
			else
			{
				// ENTITY HANDLES CREATION
				entity_new = entity->customCopy( to_parent, entity, m_translation_map );
				// return it if created
				if ( entity_new )
				{
					return entity_new;
				}

				// BASIC ENTITY
				else if ( std::string(entity->class_id()) == "entity" )
				{
					// std::cout << "'" << entity->name() << "'" << std::endl;
					entity_new = to_parent->addChild( entity->name(), new BEntity() );
				}

				// ENTITIES WITH CLASS ID
				else if ( std::string(entity->class_id()) != "entity" )
				{
					entity_new = to_parent->addChild( entity->name(), entity->class_id() );
				}

				else
				{
					std::cout << "not copied: " << entity->name() << std::endl;
				}
			}
		}

		// IF SUCCESS
		if ( entity_new )
		{
			// UPDATE TRANSLATION MAP
			m_translation_map.insert( std::make_pair( entity, entity_new ) );

			// RECURSE INTO ENTITY CHILDREN
			if ( entity->hasChildren() )
			{
				for_all_children_of( entity )
				{
					_copyEntity( *child, entity_new );
				}
			}
		}

		return entity_new;
	}

	BEntity* BEntityCopy::_wireNewEntity()
	{
		for ( auto it = m_translation_map.begin(); it != m_translation_map.end(); ++it )
		{
			auto copy = it->second;
			if ( copy )
			{
				auto original = it->first;

				// exception for all references not named _external_child
				// external child is already taken care of
				// update all other refs

				// if ( original->name() != "_external_child" )
				if ( !dynamic_cast<BEntity_external*>( original ) )
				{
					// APPLY REFERENCES
					auto ref = dynamic_cast<BEntity_reference*>( original );
					if ( ref )
					{
						BEntity* found = m_translation_map[ original->get_reference() ];
						if ( found )
						{
							copy->set( found );
						}
						else
						{
							// refer to same entity if not found in translation_map
							copy->set( original->get_reference() );
							// std::cout << "wiring: not ok" << std::endl;
						}
					}
					// APPLY VALUES
					else
					{
						original->apply( copy );
					}
				}

				// COPY CONNECTIONS
				if ( original && original->hasOutput() ) // !original->isBuiltin()  || ! //  && original->isBuiltin()
				{
					auto t_output = original->getOutput();
					for ( auto conn_it(t_output->m_connections.begin()); conn_it != t_output->m_connections.end(); ++conn_it )
					{
						auto connection = dynamic_cast<BEOutputConnectionBase*>(*conn_it);
						if ( connection )
						{
							auto orig_connected_to = connection->getInputEntity();
							auto new_entity_to_connect_to = m_translation_map[orig_connected_to];
							if ( new_entity_to_connect_to )
							{
								copy->connectServerServer(new_entity_to_connect_to);
							}
							else
							{
								std::cout << "connection not ok, copy of '" << orig_connected_to->name() << "' or type '" << orig_connected_to->class_id() << "' entity not found in translation_map" << std::endl;
							}
						}
// 						if ( connection->m_isLocal )
// 						{
// 							const unsigned int orig_id = connection->m_input->getBeParent()->id();
// 							BEntity* new_id_ent = m_translation_map[orig_id];
// 							if ( new_id_ent && copy->hasOutput() && new_id_ent->hasInput() )
// 							{
// 								copy->entity_connect_local(new_id_ent);
// 							}
// 						}
					}
				}
			}
		}

		// for ( auto it = m_translation_map.begin(); it != m_translation_map.end(); ++it )
		// {
		// 	auto copy = it->second;
		// 	if ( copy )
		// 	{
		// 		// FIXME POSTCOPY?
		// 		if ( copy->name() == "hinge" )
		// 		{
		// 			// std::cout << "CREATED HINGE " << copy->name() << std::endl;
		// 			copy->set( "create_hinge", true );
		// 		}
		// 	}
		// }

		return 0;
	}	

	// SAVING
		void BEntitySave::saveEntity( BEntity* entity )
		{
			std::cout << "SAVE TOP: " << entity->id() << std::endl;
			
			std::map<unsigned int, BEntity*> external_entity_list;
			std::stringstream file_content;
		// 	file_content << std::setprecision(100);
			file_content << std::fixed;
			std::stringstream file_external_parents_content;

			// BODY
			save_entity(entity, file_content, external_entity_list, false, false, false);

			// HEAD
				// external parents
				for ( auto it(external_entity_list.begin()); it != external_entity_list.end(); ++it )
				{
					BEntity* e_parent(it->second);
					file_external_parents_content << "\t<external_parent";
					file_external_parents_content << " id=\"" << e_parent->id() << "\"";
					file_external_parents_content << " type=\"" << e_parent->class_id() << "\"";
					file_external_parents_content << " name=\"" << e_parent->name() << "\"";
					
					BEntity* e_parent_parent(e_parent->parent());
					if ( e_parent_parent != 0 )
					{
						file_external_parents_content << " parent_id=\"" << e_parent_parent->id() << "\"";
						file_external_parents_content << " parent_type=\"" << e_parent_parent->class_id() << "\"";
						file_external_parents_content << " parent_name=\"" << e_parent_parent->name() << "\"";
					}
					file_external_parents_content << " />" << std::endl;
				}
			
		// 	std::cout << file_content.str() << std::endl;

			std::stringstream t_filename;
			t_filename << "entity_" << entity->id() << ".ent";
			
			std::fstream file_op(t_filename.str(),std::ios::out);
			file_op << "<root>" << std::endl;
			file_op << std::endl;
			file_op << file_external_parents_content.str();
			file_op << std::endl;
			file_op << file_content.str();
			file_op << std::endl;
			file_op << "</root>" << std::endl;
			file_op.close();
			
		}

		void BEntitySave::save_entity(BEntity* entity_to_save, std::stringstream& file_content, std::map<unsigned int, BEntity*>& external_entity_list, const bool isBuiltin, const bool isExternal, const unsigned int level)
		{
			if ( entity_to_save )
			{
				// TYPE NAME
					// const std::string& entity_type_name = entity_to_save->class_id();

				// INDENTATION SPACES CALCULATION
					std::string spaces;
					for ( unsigned int i(0); i < level; ++i )
						spaces.append("\t");
				
				// FIXME
				// EXTERNAL CHILD'S PARENT ID
					std::stringstream external_parent;
					if ( isExternal )
					{
						BEntity* e_parent(entity_to_save->parent());

						if ( !external_entity_list[e_parent->id()] )
							external_entity_list[e_parent->id()] = e_parent;
					
						external_parent << " parent_id=\"" << e_parent->id() << "\"";
					}

				// ENTITY LOCATION CALCULATION scene/server/client
					// std::string entity_location;

					file_content << spaces << "<" << entity_to_save->class_id() << " id=\"" << entity_to_save->id() << "\"" << " name=\"" << entity_to_save->name() << "\"" << external_parent.str() << ">" << std::endl;

				// VALUE
					// std::cout << "dealing with A '" << entity_to_save->class_id() << "'" << std::endl;
					if ( entity_to_save->class_id() == std::string("reference") )
					{
						// std::cout << "dealing with " << entity_to_save->class_id() << std::endl;
						file_content << spaces << "\t" << "<value>" << entity_to_save->get_reference()->id() << "</value>" << std::endl;
					}
					else if ( entity_to_save->class_id() == std::string("bool") || entity_to_save->class_id() == std::string("bool_property") )
					{
						// std::cout << "dealing with " << entity_to_save->class_id() << std::endl;
						file_content << spaces << "\t" << "<value>" << entity_to_save->get_bool() << "</value>" << std::endl;
					}
					else if ( entity_to_save->class_id() == std::string("uint") || entity_to_save->class_id() == std::string("uint_property") )
					{
						// std::cout << "dealing with " << entity_to_save->class_id() << std::endl;
						file_content << spaces << "\t" << "<value>" << entity_to_save->get_uint() << "</value>" << std::endl;
					}
					else if ( entity_to_save->class_id() == std::string("int") || entity_to_save->class_id() == std::string("int_property") )
					{
						// std::cout << "dealing with " << entity_to_save->class_id() << std::endl;
						file_content << spaces << "\t" << "<value>" << entity_to_save->get_int() << "</value>" << std::endl;
					}
					else if ( entity_to_save->class_id() == std::string("float") || entity_to_save->class_id() == std::string("float_property") )
					{
						// std::cout << "dealing with " << entity_to_save->class_id() << std::endl;
						file_content << spaces << "\t" << "<value>" << entity_to_save->get_float() << "</value>" << std::endl;
					}
					else if ( entity_to_save->class_id() == std::string("double") || entity_to_save->class_id() == std::string("double_property") )
					{
						// std::cout << "dealing with " << entity_to_save->class_id() << std::endl;
						file_content << spaces << "\t" << "<value>" << entity_to_save->get_double() << "</value>" << std::endl;
					}
					else if ( entity_to_save->class_id() == std::string("string") || entity_to_save->class_id() == std::string("string_property") )
					{
						// std::cout << "dealing with " << entity_to_save->class_id() << std::endl;
						file_content << spaces << "\t" << "<value>" << entity_to_save->get_string() << "</value>" << std::endl;
					}

				// CONNECTIONS
					if ( entity_to_save->hasOutput() ) // !original->isBuiltin()  || ! //  && original->isBuiltin()
					{
						BEOutput* t_output(entity_to_save->getOutput());
						const auto& conn_end(t_output->m_connections.end());
						for ( auto conn_it(t_output->m_connections.begin()); conn_it != conn_end; ++conn_it )
						{
							BEOutputConnectionLocal* local_connection = dynamic_cast<BEOutputConnectionLocal*>(*conn_it);
							if ( local_connection )
							{
								const unsigned int id = local_connection->getInputEntity()->id();
								file_content << spaces << "\t" << "<connection id=\"" << id << "\" />" << std::endl;
							}

							BEOutputConnectionCommandBuffer* remote_connection = dynamic_cast<BEOutputConnectionCommandBuffer*>(*conn_it);
							if ( remote_connection )
							{
								const unsigned int id = remote_connection->getInputEntity()->id();
								if ( id != entity_to_save->id() )
									file_content << spaces << "\t" << "<connection_remote id=\"" << id << "\" />" << std::endl;
							}
						}
					}
					

				// EXTERNAL CHILDREN
					// if ( entity_to_save->name() == "_external_child" )
					if ( dynamic_cast<BEntity_external*>( entity_to_save ) )
					{
						// fetch the entity the extchild points to SERVER
						BEntity* e_extchild = entity_to_save->get_reference();
						if ( e_extchild )
						{
							save_entity(e_extchild, file_content, external_entity_list, false, true, 1+level);
						}
						else
						{
							file_content << "EXTERNAL CHILD NOT FOUND" << std::endl;
							exit(1);
						}
					}
				// // EXTERNAL CHILDREN
				// 	if ( entity_to_save->entityType() == entityType_EXTERNAL_CHILD )
				// 	{
				// 		// fetch the entity the extchild points to SERVER
				// 		BEntity* e_extchild = entity_to_save->getExternalChild();
				// 		if ( e_extchild )
				// 		{
				// 			save_entity(e_extchild, file_content, external_entity_list, false, true, 1+level);
				// 		}
				// 		else
				// 		{
				// 			file_content << "EXTERNAL CHILD NOT FOUND" << std::endl;
				// 			exit(1);
				// 		}
				// 	}

				// CHILDREN
					// const auto& end(entity_to_save->children_end());
					// for ( auto it = entity_to_save->children_begin(); it != end; ++it )
					for_all_children_of( entity_to_save )
					{
						if ( isBuiltin || entity_to_save->isBuiltin() || (*child)->isBuiltin() )
							save_entity( *child, file_content, external_entity_list, true, false, 1+level );
						else
							save_entity( *child, file_content, external_entity_list, isBuiltin, false, 1+level );
					}
				// // CHILDREN
				// 	// const auto& end(entity_to_save->children_end());
				// 	// for ( auto it = entity_to_save->children_begin(); it != end; ++it )
				// 	for_all_children_of(entity_to_save)
				// 	{
				// 		if ( isBuiltin || entity_to_save->isBuiltin() || (*child)->isBuiltin() )
				// 			save_entity( *child, file_content, external_entity_list, true, false, 1+level );
				// 		else
				// 			save_entity( *child, file_content, external_entity_list, isBuiltin, false, 1+level );
				// 	}

				file_content << spaces << "</" << entity_to_save->class_id() << ">" << std::endl;
			}
		}



	// LOADING
		void BEntityLoad::loadEntity( BEntity* parent, const std::string& filename )
		{
			std::cout << "::LOAD TOP: " << parent->id() << std::endl;
			
			// std::stringstream t_filenamestream;
			// t_filenamestream << "./entity_load.ent";
			// std::string filename(t_filenamestream.str());
			
			// BeFile befile;
			// if ( m_fileSystem.load(befile, filename) )
			{
				TiXmlDocument document;
				const bool result = document.LoadFile( filename.c_str() );
				if(result)
				{
					// std::cout << "::FILE FOUND: " << filename << std::endl;
					
					const TiXmlElement* const rootElementPtr=document.RootElement();
					if(rootElementPtr)
					{
						const TiXmlElement& rootElement=(*rootElementPtr);

						std::map<unsigned int, BEntity*> translation_map;
						std::map<unsigned int, BEntity*> external_entity_list;

						// LOAD
							// std::cout << "::load entities" << std::endl;
							const TiXmlElement* elementPtr=rootElement.FirstChildElement();
							while(elementPtr)
							{
								const TiXmlElement& element=(*elementPtr);
								
								// std::cout << element.ValueTStr().c_str() << std::endl;

									if ( element.ValueTStr() == "external_parent" )
									{
										loadExternalParentFromXML(parent, element, external_entity_list);
									}
									else
									{
										loadEntityFromXML(parent, element, translation_map, external_entity_list, 1);
									}
								
									// if ( element.ValueTStr() == "server_entity" )
									// {
									// 	loadEntityFromXML(parent, element, translation_map, external_entity_list, 1);
									// }
									// else if ( element.ValueTStr() == "client_entity" )
									// {
									// 	loadEntityFromXML(parent, element, translation_map, external_entity_list, 2);
									// }

								elementPtr=element.NextSiblingElement();
							}
							
						// CONNECTIONS
							// std::cout << "load connections" << std::endl;
							elementPtr=rootElement.FirstChildElement();
							while(elementPtr)
							{
								const TiXmlElement& element=(*elementPtr);

									if ( element.ValueTStr() != "external_parent" )
									{
										loadEntityFromXMLConnections(element, translation_map);
									}

								elementPtr=element.NextSiblingElement();
							}
						
						// FIXME TRY "create_hinge" command from here?

					}
					else
					{
						std::cout << "FILE NOT FOUND: '" << filename << "'" << std::endl;
						std::cout << document.ErrorDesc() << std::endl;
						std::cout << "error on row: " << document.ErrorRow() << std::endl;
					}
				}
				else
					std::cout << "SERVER::WARNING file could not be found: " << filename << std::endl;
			}


		}

		void BEntityLoad::loadExternalParentFromXML( BEntity* parent, const TiXmlElement& element, std::map<unsigned int, BEntity*>& external_entity_list)
		{
			// ID AND TYPE
				int e_id(-1);
				std::string e_type("");
				std::string e_name("");  // FIXME only used for external parents, make <>

				int external_parent_id(-1);
				std::string external_parent_type("");
				std::string external_parent_name("");

				BeXmlHelper xmlHelper;
					xmlHelper.addInt("id", e_id);
					xmlHelper.addString("type", e_type);
					xmlHelper.addString("name", e_name);

					xmlHelper.addInt("parent_id", external_parent_id);
					xmlHelper.addString("parent_type", external_parent_type);
					xmlHelper.addString("parent_name", external_parent_name);
				xmlHelper.parse(element);


			// EXTERNAL PARENT
			// parent parent by id
			auto Scene = parent->topParent()->getChild( "Scene", 1 );
			bool parent_parent_found(false);
			BEntity* external_parent_parent(0);
			// BEntity* external_parent_parent = parent->topParent()->getChild( (unsigned int)external_parent_id) ;
			// // matches type?
			// if ( external_parent_parent && external_parent_parent->entityType() == BEntityTypeManager::Instance()->getEntityID(external_parent_type) )
			// {
			// 	// matches name?
			// 	if ( external_parent_parent->name() == external_parent_name )
			// 		parent_parent_found = true;
			// }

			// parent parent by name
			if ( !parent_parent_found && external_parent_name.size()>0 )
			{
				external_parent_parent = Scene->getChild( external_parent_name.c_str() );
				// matches type?
				if ( external_parent_parent && external_parent_parent->class_id() == external_parent_type )
				{
					parent_parent_found = true;
					// std::cout << "parent parent:" << external_parent_parent->name() << std::endl;
				}
			}

			if ( parent_parent_found )
			{
		// 		// find parent by id
		// 			BEntity* external_parent = external_parent_parent->get((unsigned int)e_id, 1);
		// 			if ( external_parent && external_parent->entityType() == BEntityTypeManager::Instance()->getEntityID(e_type) )
		// 			{
		// // 				if ( !external_entity_list[external_parent->id()] )
		// 				external_entity_list[(unsigned int)e_id] = external_parent.get();
		// // 				std::cout << e_id << " --> " << external_parent.get() << std::endl;
		// 			}
					// else
					if ( e_name.size() > 0 )
					{
						// find parent by name
						auto external_parent = external_parent_parent->getChild( e_name.c_str() );
						if ( external_parent && external_parent->class_id() == e_type )
						{
		// 					if ( !external_entity_list[external_parent->id()] )
							external_entity_list[(unsigned int)e_id] = external_parent;
							// std::cout << e_id << " --> " << external_parent << " " << e_name << std::endl;
						}
						else
							std::cout << "warning: entity_load: external entity not found, name: " << e_name.c_str() <<  " id: " << e_id << std::endl;
					}
			}
			else
				std::cout << "warning: entity_load: external parent's parent not found, name: " << external_parent_name.c_str() <<  " id: " << external_parent_id << std::endl;
			
			// RETURN, no entity needs saving
			// FIXME TODO fix this entire external parent mess into a seperate function man

		}

		

		void BEntityLoad::loadEntityFromXML(BEntity* parent, const TiXmlElement& element, std::map<unsigned int, BEntity*>& translation_map, std::map<unsigned int, BEntity*>& external_entity_list, const unsigned int scene_server_client)
		{
			// ID AND TYPE
				int e_id(-1);
				std::string e_name("");
				int external_parent_id(-1);

				BeXmlHelper xmlHelper;
				xmlHelper.addInt("id", e_id);
				xmlHelper.addString("name", e_name);
				// xmlHelper.addString("type", e_type);
				xmlHelper.addInt("parent_id", external_parent_id);


				xmlHelper.parse(element);
				std::string e_type = element.ValueTStr().c_str();

			// // FIND NAME BEFORE CREATING ENTITY
			// 	std::string e_name;
			// 	const TiXmlElement* childElementPtr = element.FirstChildElement();
			// 	while(childElementPtr)
			// 	{
			// 		const TiXmlElement& childElement=*childElementPtr;
   // 
			// 			if(childElement.ValueTStr()=="name")
			// 				e_name = childElement.GetText();
   // 
			// 		childElementPtr=childElement.NextSiblingElement();
			// 	}

			// CREATE THE ENTITY
				BEntity* this_entity(0);
				if ( scene_server_client == 1 )
				{
					if ( external_parent_id == -1 )
					{
						// this_entity = add_serverentity(e_name, parent.get(), BEntityTypeManager::Instance()->getEntityID(e_type));
						if ( e_type == "connection" )
						{
							return;
						}
						else if ( e_name == "body_fixed1" )
						{
							this_entity = parent->addChild( "body_fixed1", "BodyFixed1" );

							// this_entity = parent->addChild( e_name.c_str(), "BodyFixed1" );
							// this_entity = parent->getChildCustom( parent, "generate_fixed_1" );
							
							// std::cout << ":: BODY FIXED " << this_entity->id() << std::endl;
							// TRANSLATION MAP
							translation_map.insert(std::make_pair(e_id, this_entity));

							// HACK SPECIAL CASE
							// LOOP ENTITY & ENTITY_NEW TO ADD THEM TO THE TRANSLATION_MAP
							
							// auto bodyparts = entity->getChild( "bodyparts", 1 );
							// auto constraints = entity->getChild( "constraints", 1 );
							
							auto bodyparts_new = this_entity->getChild( "bodyparts", 1 );
							auto constraints_new = this_entity->getChild( "constraints", 1 );
							const TiXmlElement* childElementPtr2 = element.FirstChildElement();
							while(childElementPtr2)
							{
								const TiXmlElement& childElement2=*childElementPtr2;

								std::string e_name2;
								int c_id(-1);
								BeXmlHelper xmlHelper2;
								xmlHelper2.addInt("id", c_id);
								xmlHelper2.addString("name", e_name2);
								xmlHelper2.parse(childElement2);

								if( e_name2 == "bodyparts" )
								{
									translation_map.insert( std::make_pair( c_id, bodyparts_new ) );

									const auto& children_vector_new = bodyparts_new->children();
									auto child_new = children_vector_new.begin();

									const TiXmlElement* childElementPtr3 = childElement2.FirstChildElement();
									while(childElementPtr3)
									{
										const TiXmlElement& childElement3=*childElementPtr3;

										if( childElement3.ValueTStr() == "external_child" )
										{
											// std::cout << "::FOUND REFERENCE" << std::endl;
											int r_id2(-1);
											BeXmlHelper xmlHelper3;
											xmlHelper3.addInt("id", r_id2);
											xmlHelper3.parse(childElement3);

											const TiXmlElement* childElementPtr4 = childElement3.FirstChildElement();
											while(childElementPtr4)
											{
												const TiXmlElement& childElement4=*childElementPtr4;
							
												if( childElement4.ValueTStr() != "value" )
												{
													int c_id2(-1);
													BeXmlHelper xmlHelper4;
													xmlHelper4.addInt("id", c_id2);
													xmlHelper4.parse(childElement4);

													// std::cout << childElement4.ValueTStr().c_str() << std::endl;
													// const Buint e_id = atoi( childElement4.GetText() );
													// std::cout << ":: ID " << c_id2 << std::endl;
													
													if ( child_new != children_vector_new.end() )
													{
														translation_map.insert( std::make_pair( r_id2, *child_new ) );
														translation_map.insert( std::make_pair( c_id2, (*child_new)->get_reference() ) );
													}
													child_new++;
												}
												childElementPtr4=childElement4.NextSiblingElement();
											}
										}
										childElementPtr3=childElement3.NextSiblingElement();
									}
								}
								else if( e_name2 == "constraints" )
								{
									translation_map.insert( std::make_pair( c_id, constraints_new ) );

									const auto& children_vector_new = constraints_new->children();
									auto child_new = children_vector_new.begin();

									const TiXmlElement* childElementPtr3 = childElement2.FirstChildElement();
									while(childElementPtr3)
									{
										const TiXmlElement& childElement3=*childElementPtr3;

										if( childElement3.ValueTStr() == "external_child" )
										{
											// std::cout << "::FOUND REFERENCE" << std::endl;
											int r_id2(-1);
											BeXmlHelper xmlHelper3;
											xmlHelper3.addInt("id", r_id2);
											xmlHelper3.parse(childElement3);

											const TiXmlElement* childElementPtr4 = childElement3.FirstChildElement();
											while(childElementPtr4)
											{
												const TiXmlElement& childElement4=*childElementPtr4;
							
												// if( childElement4.ValueTStr() != "value" )
												{
													int c_id2(-1);
													BeXmlHelper xmlHelper4;
													xmlHelper4.addInt("id", c_id2);
													xmlHelper4.parse(childElement4);

													// std::cout << childElement4.ValueTStr().c_str() << std::endl;
													// const Buint e_id = atoi( childElement4.GetText() );
													// std::cout << ":: ID " << c_id2 << std::endl;
													
													if ( child_new != children_vector_new.end() )
													{
														translation_map.insert( std::make_pair( r_id2, *child_new ) );
														translation_map.insert( std::make_pair( c_id2, (*child_new)->get_reference() ) );
														
														// FIXME FIND ANGLE FROM XML
														
														
														
														const TiXmlElement* childElementPtr5 = childElement4.FirstChildElement();
														while(childElementPtr5)
														{
															const TiXmlElement& childElement5=*childElementPtr5;

															if( childElement5.ValueTStr() == "float" )
															{
																int a_id(-1);
																std::string a_name;
																BeXmlHelper xmlHelper5;
																xmlHelper5.addInt("id", a_id);
																xmlHelper5.addString("name", a_name);
																xmlHelper5.parse(childElement5);
																
																if ( a_name == std::string("angle") )
																{
																	translation_map.insert( std::make_pair( a_id, (*child_new)->get_reference()->getChild("angle", 1) ) );
																	
																}
															}
															childElementPtr5=childElement5.NextSiblingElement();
														}
														
														
														
														
													}
													child_new++;
												}
												childElementPtr4=childElement4.NextSiblingElement();
											}
										}
										childElementPtr3=childElement3.NextSiblingElement();
									}
								}
								
								childElementPtr2=childElement2.NextSiblingElement();
							}

							// MAKE SURE NOT NOT ADD CHILDREN
							return;
						}
						else if ( e_type == "entity" )
						{
							// std::cout << parent->name() << "::" << e_type << "::" << e_name << std::endl;
							this_entity = parent->addChild( e_name.c_str(), new BEntity() );
						}
						else
						{
							// std::cout << parent->name() << "::" << e_type << "::" << e_name << std::endl;
							this_entity = parent->addChild( e_name.c_str(), e_type.c_str() );
						}
					}
					else
					{
						// EXTERNAL ENTITY
						BEntity* external_parent = external_entity_list[external_parent_id];
	
						if ( external_parent )
						{
							// std::cout << external_parent->name() << "::" << e_type << "::" << e_name << std::endl;
							this_entity = external_parent->addChild( e_name.c_str(), e_type.c_str() );
							parent->set(this_entity);
						}
						else
							std::cout << "warning: external parent not found" << external_parent_id << std::endl;
					}
				}
				else if ( scene_server_client == 3 )
				{
		// 			std::cout << "> parent: " << e_name << std::endl;
					this_entity = parent->getChild( e_name.c_str(), 1 );
				}

			// FIXME CHECKS

				if ( this_entity == 0 )
				{
					std::cout << "warning: no entity was found: " << parent->name() << "::" << e_name << std::endl;
					std::cout << "warning: scene_server_client=" << scene_server_client << std::endl;
					std::cout << "warning: parent: " << parent->id() << std::endl;
				}
				else
				{
					// TRANSLATION MAP
					translation_map.insert(std::make_pair(e_id, this_entity));

					// BUILTINS MAP
					std::map<std::string, BEntity*> builtins_map;
					for_all_children_of( this_entity )
					{
						builtins_map[ (*child)->name() ] = *child;
					}

					// value, connections, other entities
					auto childElementPtr = element.FirstChildElement();
					while(childElementPtr)
					{
						const TiXmlElement& childElement=*childElementPtr;
					
						if( childElement.ValueTStr() == "value" )
						{
							// NOTE external children are handled somewhere else, because at this point it doesn't exist yet
							if ( e_type == "reference" )
							{
								// if ( this_entity->name() != "_external_child" )
								{
									const Buint e_value = atoi(childElement.GetText());
									BEntity* ref_entity( translation_map[ e_value ] );
									if ( ref_entity )
									{
										this_entity->set(ref_entity);
									}
									else
									{
										// IF THE REFERRED ENTITY IS NOT IN TRANSLATION MAP REMOVE IT (IT WAS EXTERNAL, BUT NOT CHILD)
										// std::cout << "copy child: removing reference '" << this_entity->name() << "'" << std::endl;
										this_entity->parent()->removeChild( this_entity );
									}
									// std::cout << e_value << " to " << this_entity->id() << ":" << this_entity->name() << std::endl;
								}
							}

							else if ( e_type == "bool" || e_type == "bool_property" )
							{
								if ( childElement.GetText() == std::string("1") )
									this_entity->set(true);
								// std::cout << " " << " value " << e_type << ": " << e_value << std::endl;
							}

							else if ( e_type == "uint" || e_type == "uint_property" )
							{
								if ( this_entity->name() == "age" )
								{
									this_entity->set( Buint(0) );
								}
								else
								{
									const Buint e_value = atoi(childElement.GetText());
									this_entity->set( e_value );
								}
								// std::cout << " " << " value " << e_type << ": " << e_value << std::endl;
							}

							else if ( e_type == "int" || e_type == "int_property" )
							{
								const Bint e_value = atoi(childElement.GetText());
								this_entity->set( e_value );
								// std::cout << " " << " value " << e_type << ": " << e_value << std::endl;
							}

							else if ( e_type == "float" || e_type == "float_property" )
							{
								const Bfloat e_value = atof(childElement.GetText());
								this_entity->set( e_value );
								// std::cout << " " << " value " << e_type << ": " << e_value << std::endl;
							}

							else if ( e_type == "double" || e_type == "double_property" )
							{
								const Bdouble e_value = atof(childElement.GetText());
								this_entity->set( e_value );
								// std::cout << " " << " value " << e_type << ": " << e_value << std::endl;
							}

							else if ( e_type == "string" || e_type == "string_property" )
							{
								std::string e_value(childElement.GetText());
								this_entity->set( e_value.c_str() );
								// std::cout << " " << " value " << e_type << ": " << e_value << std::endl;
							}
						}

						else
						{
							
							std::string e_c_name("");
							BeXmlHelper xmlHelper;
							xmlHelper.addString("name", e_c_name);
							xmlHelper.parse(childElement);
							
							if ( builtins_map[ e_c_name ] )
							{
								loadEntityFromXML(this_entity, childElement, translation_map, external_entity_list, 3);
							}
							else
							{
								loadEntityFromXML(this_entity, childElement, translation_map, external_entity_list, 1);
							}
						}

						childElementPtr=childElement.NextSiblingElement();
					}
				}
			
		}


		void BEntityLoad::loadEntityFromXMLConnections(const TiXmlElement& element, std::map<unsigned int, BEntity*>& translation_map)
		{
			// value, connections, other entities
				const TiXmlElement* childElementPtr = element.FirstChildElement();
				while(childElementPtr)
				{
					const TiXmlElement& childElement=*childElementPtr;

					if( childElement.ValueTStr() == "connection" )
					{
						int e_id(-1);
						BeXmlHelper xmlHelper;
						xmlHelper.addInt("id", e_id);
						xmlHelper.parse(element);

						int e_conn_id(-1);
						BeXmlHelper xmlHelper2;
						xmlHelper2.addInt("id", e_conn_id);
						xmlHelper2.parse(childElement);
							
						if ( e_id != -1 && e_conn_id != -1 )
						{
							BEntity* this_entity(translation_map[(unsigned int)e_id]);
							BEntity* e_target(translation_map[(unsigned int)e_conn_id]);
							
							// SHOULD BE OK BECAUSE MISSING CONNECTIONS ARE TAKEN CARE OF WHEN CREATING body_fixed1
							if ( this_entity && e_target )
							{
								this_entity->connectServerServer(e_target);
							}
							else
							{
								if ( !e_target )
								{
									std::cout << "xml loading: connection target not found in translation_map, source:" << e_id << std::endl;
								}
							}
						}
					}

					// CHILDREN
						loadEntityFromXMLConnections(childElement, translation_map);

					childElementPtr=childElement.NextSiblingElement();
				}
		}
