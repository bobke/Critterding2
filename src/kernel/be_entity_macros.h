			
			
// #define SAFE_GET(X) String PASTE(str_, X) = getFunction(STRINGIFY(X));
// String str_foo = getFunction("foo");

	#define STRINGIFY2(x) #x
	#define STRINGIFY(x) STRINGIFY2(x)
	#define PASTE2(a, b) a##b
	#define PASTE(a, b) PASTE2(a, b)
	
	#define SAFE_CHECK(X) \
		if ( id == STRINGIFY(X) )	\
		{ \
			if ( PASTE(m_, X) != value ) \
			{ \
				PASTE(m_, X) = value; \
				return true; \
			} \
		} \

	#define SAFE_GET(X) \
		if ( id == STRINGIFY(X) ) \
		{ \
			return PASTE(m_, X); \
		}

	#define DATA_1(type, m) \
		private: \
			PASTE(B, type) PASTE(m_, m); \
		public: \
		bool set( const Bstring& id, const Bfloat& value ) \
		{ \
			SAFE_CHECK(m); \
			return false; \
		} \
		PASTE(B, type) PASTE(get_, type)( const Bstring& id ) \
		{ \
			SAFE_GET(m) \
			return 0; \
		}

	#define DATA_2(type, m, m2) \
		private: \
			PASTE(B, type) PASTE(m_, m); \
			PASTE(B, type) PASTE(m_, m2); \
		public: \
		bool set( const Bstring& id, const PASTE(B, type)& value ) \
		{ \
			SAFE_CHECK(m); \
			SAFE_CHECK(m2); \
			return false; \
		} \
		PASTE(B, type) PASTE(get_, type)( const Bstring& id ) \
		{ \
			SAFE_GET(m) \
			SAFE_GET(m2) \
			return 0; \
		}


	#define DATA_3(type, m, m2, m3) \
		private: \
			PASTE(B, type) PASTE(m_, m); \
			PASTE(B, type) PASTE(m_, m2); \
			PASTE(B, type) PASTE(m_, m3); \
		public: \
		bool set( const Bstring& id, const type& value ) \
		{ \
			SAFE_CHECK(m); \
			SAFE_CHECK(m2); \
			SAFE_CHECK(m3); \
			return false; \
		} \
		PASTE(B, type) PASTE(get_, type)( const Bstring& id ) \
		{ \
			SAFE_GET(m) \
			SAFE_GET(m2) \
			SAFE_GET(m3) \
			return 0; \
		}


	#define DATA_4(type, m, m2, m3, m4) \
		private: \
			PASTE(B, type) PASTE(m_, m); \
			PASTE(B, type) PASTE(m_, m2); \
			PASTE(B, type) PASTE(m_, m3); \
			PASTE(B, type) PASTE(m_, m4); \
		public: \
		bool set( const Bstring& id, const type& value ) \
		{ \
			SAFE_CHECK(m); \
			SAFE_CHECK(m2); \
			SAFE_CHECK(m3); \
			SAFE_CHECK(m4); \
			return false; \
		} \
		PASTE(B, type) PASTE(get_, type)( const Bstring& id ) \
		{ \
			SAFE_GET(m) \
			SAFE_GET(m2) \
			SAFE_GET(m3) \
			SAFE_GET(m4) \
			return 0; \
		}

	#define PROCESS \
			virtual void process() {



	#define ENTITY(name) \
			class name : public BEntity \
			{ \
				public: \
					name()  { setProcessing(); } \
					virtual ~name() {};

	// #define ENTITY_PROC_SIMPLEST(name) \
	// 		class name : public BEntity \
	// 		{ \
	// 			public: \
	// 				name() { setProcessing(); } \
	// 				virtual ~name() {}; \
	// 				virtual void process()

	#define ENTITY_SIMPLEST(name) \
			class name : public BEntity \
			{ \
				public: \
					name() { setProcessing(); } \
					virtual ~name() {}; \
					virtual void process()

	/* #define ENTITY_SIMPLEST_END \
			}; */


	#define END \
			};
			
			 
