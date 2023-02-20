#include "admin_lookup_buffer.h"
#include "kernel/be_entity_interface.h"
// #include <iostream>

	BAdminLookupBuffer::BAdminLookupBuffer()
	{
	}
 
	void BAdminLookupBuffer::registerAdminEntity( BEntity* entity, BEntity* admin_entity )
	{
		// find entity in map
		auto search = m_admin_map.find( entity );
		if ( search != m_admin_map.end() )
		{
			// if entity found in map, add admin_entity to found vector
			// std::cout << "BAdminLookupBuffer::registerAdminEntity > Found " << search->first->id() << " " << &search->second << '\n';
			auto entity_vector = &search->second;
			entity_vector->push_back( admin_entity );
		}
		else
		{
			// if entity not found in map, push new vector onto map
			// std::cout << "BAdminLookupBuffer::registerAdminEntity > Not Found " << '\n';
			std::vector<BEntity*> v;
			v.push_back( admin_entity );
			m_admin_map[entity] = v;
		}
		
		entity->setHasAdmin();
		admin_entity->setIsAdmin();
		
	}

	std::vector<BEntity*>* BAdminLookupBuffer::findAdminEntities( BEntity* entity )
	{
		// find entity in map
		auto search = m_admin_map.find( entity );
		if ( search != m_admin_map.end() )
		{
			// if entity found in map, return pointer
			// std::cout << "BAdminLookupBuffer::findAdminEntities > Found " << search->first->id() << " " << &search->second << '\n';
			return &search->second;
		}

		return 0;
	}

	void BAdminLookupBuffer::removeAdminEntities( BEntity* entity )
	{
		// FIXME NEED TO CHECK IF THERE ARE STILL ADMIN ITEMS FOR ENTITY, TO SET HASADMIN
		if ( entity->isAdmin() )
		{
			// as item in vector
			auto itr = m_admin_map.begin();
			while ( itr != m_admin_map.end() )
			{
				unsigned int i(0);
				while ( i < itr->second.size() )
				{
					if ( itr->second[i] == entity )
					{
						// std::cout << "removing item" << std::endl;
						itr->second.erase( itr->second.begin() + i);
					}
					else
					{
						i++;
					}
				}
  
				if ( itr->second.size() == 0 )
				{
					// std::cout << "removing vector" << std::endl;
					itr->first->unsetHasAdmin();
					itr = m_admin_map.erase(itr);
				}
				else
				{
					++itr;
				}
			}
		}

		if ( entity->hasAdmin() )
		{
			// as key in lookup_buffer
			auto search = m_admin_map.find( entity );
			if ( search != m_admin_map.end() )
			{
				// remove all admin items
				for( auto i : search->second )
				{
					// std::cout << "rm" << std::endl;
					i->unsetIsAdmin();
					i->parent()->removeChild( i );
				}

				// recheck redundancy and remove vector from lookup_buffer
				search = m_admin_map.find( entity );
				if ( search != m_admin_map.end() )
				{
					m_admin_map.erase(search);
					entity->unsetHasAdmin();
				}
			}
		}

// 		// find entity in map
// 		auto search = m_admin_map.find( entity );
// 		if ( search != m_admin_map.end() )
// 		{
// 			// if entity found in map, return pointer
// 			// std::cout << "BAdminLookupBuffer::removeAdminEntities > Found " << search->first->id() << " " << &search->second << '\n';
// 			
// 			m_admin_map.erase( search );
// 		}
	}
