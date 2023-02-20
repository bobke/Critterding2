#ifndef ADMIN_LOOKUP_BUFFER_H_INCLUDED
#define ADMIN_LOOKUP_BUFFER_H_INCLUDED

#include <unordered_map>
#include <vector>

	class BEntity;

	// 	CONFIG LIBRARIES WINDOW
		class BAdminLookupBuffer
		{
			public:
				BAdminLookupBuffer();
				virtual ~BAdminLookupBuffer() {};
				
				void registerAdminEntity( BEntity* entity, BEntity* admin_entity );
				std::vector<BEntity*>* findAdminEntities( BEntity* entity );
				void removeAdminEntities( BEntity* entity );
				 std::unordered_map<BEntity*, std::vector<BEntity*>> m_admin_map;
			private:
		};


#endif
