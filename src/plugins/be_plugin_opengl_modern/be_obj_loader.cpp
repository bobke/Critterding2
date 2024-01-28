#include "be_parser.h"
#include "be_obj_loader.h"
#include "be_texture_2d_resource.h"
#include "filesystem/be_filesystem.h"
#include "filesystem/be_file.h"
#include "LinearMath/btTransform.h"

// #include "kernel/be_profiler.h"

// FIXME DISABLED FOR NOW
// BeObjLoader::BeObjLoader( BeFilesystem& filesystem, BeFile& befile, const Vector3& scale )
BeObjLoader::BeObjLoader( BeFilesystem& filesystem, BeFile& befile, const btVector3& scale, const btTransform& transform )
 :	m_numberVertices(0),
	m_numberNormals(0),
	m_numberTexCoor(0),
	m_numberVIndices(0),
	m_numberTIndices(0),
	m_numberNIndices(0)
// 	m_logDebug("OBJ")
{
	char profilerId[2048];
// 	sprintf( profilerId, "%s %s", BE_FUNCTION_ID, befile.getFilename().c_str() );
// 	BeProfiler profiler(profilerId);
	m_filename = befile.getFilename();

	gVertices = new btScalar[500000];
	gNormals = new float[500000];
	gTexCoor = new float[500000];
	gVIndices = new int[500000];
	gTIndices = new int[500000];
	gNIndices = new int[500000];

    const bool hasScale=scale!=btVector3(1,1,1);
    const bool hasTransform=!(transform==btTransform::getIdentity());

// 	cerr << "loading model: " << filename << endl;
	
	std::string line;
	BeParser parseH;
	while ( befile.getLine(line) )
	{
		parseH.reset();
// 		std::cerr << line << std::endl;
		// trim spaces
		parseH.trimWhitespaces(line);
		// remove comment lines
		parseH.removeCommentlines(line);

		if ( parseH.position_index < line.length() )
		{
// 				unsigned int type;
			const std::string& otype = parseH.returnUntillStrip( ' ', line );
			if ( !otype.empty() )
			{
				if ( otype == "v" )
				{
					btVector3 position;
                    parseH.parseVector3(line, position);

                    if(hasTransform)
                    {
					    position = transform * position;
                    }
                    
                    if(hasScale)	//	FIXME PLACING IT HERE ALSO SCALES THE POSITION, BUT PLACING IT ABOVE WILL BADLY SCALE THE MESH , REVERSE THEMMMMMMM?? TODO TODO TODO TODO TODO TODO
                    {
                        position = scale * position;
                    }

                    
					gVertices[ m_numberVertices++ ] = position.x();
					gVertices[ m_numberVertices++ ] = position.y();
					gVertices[ m_numberVertices++ ] = position.z();
// 						std::cerr << "vectors: " << m_numberVertices << std::endl;
// 						std::cerr << "x: " << x << std::endl;
// 						std::cerr << "y: " << y << std::endl;
// 						std::cerr << "z: " << z << std::endl;
//					}
//					else
//						m_logDebug << "::OBJ warning: this line sucks: '" << line << "'\n";
// 						gVertices.push_back(v);
				}

				else if ( otype == "vt" )
				{
					float u=0.0f, v=0.0f;

					// u
					parseH.trimWhitespaces(line);
					//std::string us = parseH.returnUntillStrip( ' ', line );
					//u = atof( us.c_str() );
                    parseH.parseFloat(line, u);

					// v
					parseH.trimWhitespaces(line);
					//std::string vs = parseH.returnUntillStrip( ' ', line );
					//v = atof( vs.c_str() );
                    parseH.parseFloat(line, v);

					//if ( !us.empty() && !vs.empty() )  // && line == ""
					{
// 							cerr << "got a texture coordinate here" << endl;
						gTexCoor[m_numberTexCoor++] = u;
// 							if ( u < 0.0f )
// 							cerr << "u: " << m_numberTexCoor << ": '" << u << "'" << endl;
						gTexCoor[m_numberTexCoor++] = -v;
// 							if ( v < 0.0f )
// 							cerr << "v: " << m_numberTexCoor << ": '" << v << "'" << endl;
					}
				}

				else if ( otype == "vn" )
				{

                    btVector3 normal;
					
                    parseH.parseVector3(line, normal);

// 						if ( !xs.empty() && !ys.empty() && !zs.empty() )
// 						{
// 							std::cerr << "got a normal here" << std::endl;
// 							std::cerr << "x: " << x << std::endl;
// 							std::cerr << "y: " << y << std::endl;
// 							std::cerr << "z: " << z << std::endl;
                    if(hasTransform)
                    {
						normal = transform * normal;
                        normal.normalize();
                    }
                                                            //Dont think we want to scale vectors
						gNormals[ m_numberNormals++ ] = normal.x();// * scale.x();
						gNormals[ m_numberNormals++ ] = normal.y();//* scale.y();
						gNormals[ m_numberNormals++ ] = normal.z();// * scale.z();
// 						gNormals[ m_numberNormals++ ] = x;
// 						gNormals[ m_numberNormals++ ] = y;
// 						gNormals[ m_numberNormals++ ] = z;
// 						}
				}
				else if ( otype == "mtllib" ) // material library
				{
					parseH.trimWhitespaces(line);
					const std::string& materialfile = parseH.returnUntillStrip( ' ', line );
					loadMaterialfile( filesystem, befile.getDirectory(), materialfile );
				}

				else if ( otype == "usemtl" ) // material library
				{
					parseH.trimWhitespaces(line);
					const std::string& usematerial = parseH.returnUntillStrip( ' ', line );

					matit = matlist.find( usematerial ); // Search for "Test" key
					if ( matit != matlist.end() )
					{
						Facematerial facematerial;

						facematerial.faceindex_first = m_numberVIndices;
						facematerial.faceindex_number = 0;
						facematerial.material = usematerial;
						facematerials.push_back( facematerial );
					}
				}

				else if ( otype == "f" )
				{
					std::string vindex1, vindex2, vindex3, vindex4;
					std::string tindex1, tindex2, tindex3;
					std::string nindex1, nindex2, nindex3;
					int vi1 = 0, vi2 = 0, vi3 = 0;
					int ti1 = 0, ti2 = 0, ti3 = 0;
					int ni1 = 0, ni2 = 0, ni3 = 0;

// 						cerr << line << endl;
					// 1
					parseH.trimWhitespaces(line);
					vindex1 = parseH.returnUntillStrip( '/', line );
					if ( !vindex1.empty() ) vi1 = atoi( vindex1.c_str() );
					tindex1 = parseH.returnUntillStrip( '/', line );
					if ( !tindex1.empty() ) ti1 = atoi( tindex1.c_str() );
					nindex1 = parseH.returnUntillStrip( ' ', line );
					if ( !nindex1.empty() ) ni1 = atoi( nindex1.c_str() );

					// 2
					parseH.trimWhitespaces(line);
					vindex2 = parseH.returnUntillStrip( '/', line );
					if ( !vindex2.empty() ) vi2 = atoi( vindex2.c_str() );
					tindex2 = parseH.returnUntillStrip( '/', line );
					if ( !tindex2.empty() ) ti2 = atoi( tindex2.c_str() );
					nindex2 = parseH.returnUntillStrip( ' ', line );
					if ( !nindex2.empty() ) ni2 = atoi( nindex2.c_str() );

					// 3
					parseH.trimWhitespaces(line);
					vindex3 = parseH.returnUntillStrip( '/', line );
					if ( !vindex3.empty() ) vi3 = atoi( vindex3.c_str() );
					tindex3 = parseH.returnUntillStrip( '/', line );
					if ( !tindex3.empty() ) ti3 = atoi( tindex3.c_str() );
					nindex3 = parseH.returnUntillStrip( ' ', line );
					if ( !nindex3.empty() ) ni3 = atoi( nindex3.c_str() );
					
					if ( vi1 != 0 && vi2 != 0 && vi3 != 0 )
					{
						// TODO REMOVE T & N NUMS, unneeded, always the same yo (addition ????????? really, are we sure they can be removed????)
						
						
						addFace( vi1, vi2, vi3, ti1, ti2, ti3, ni1, ni2, ni3 );
						
						
						parseH.trimWhitespaces(line);

						// TEST VOR A NEW VERTEX INDEX
						vindex4 = parseH.returnUntillStrip( '/', line );
						
						bool alternate(true);
// 						unsigned int count(0);
						while ( !vindex4.empty() )
						{
							std::string tindex4, nindex4;
							
							int vi4 = 0;
							int ti4 = 0;
							int ni4 = 0;
							
								vi4 = atoi( vindex4.c_str() );
								tindex4 = parseH.returnUntillStrip( '/', line );
								if ( !tindex4.empty() ) ti4 = atoi( tindex4.c_str() );
								nindex4 = parseH.returnUntillStrip( ' ', line );
								if ( !nindex4.empty() ) ni4 = atoi( nindex4.c_str() );
/*
								if ( vi4 != 0 )
								{
									int bvi1 = vi1;
									int bvi2 = vi2;
									int bvi3 = vi3;

									int bti1 = ti1;
									int bti2 = ti2;
									int bti3 = ti3;
									
									int bni1 = ni1;
									int bni2 = ni2;
									int bni3 = ni3;


									if ( alternate )
									{
// 										std::cout << "a" << std::endl;
										
	// 									vi1 = vi3;
	// 									ti1 = ti3;
	// 									ni1 = ni3;
										
										vi2 = bvi3;
										ti2 = bti3;
										ni2 = bni3;
										
										vi3 = vi4;
										ti3 = ti4;
										ni3 = ni4;
									}
									else
									{
// 										std::cout << "b      " << line << std::endl;
										
										vi2 = bvi1;
										ti2 = bti1;
										ni2 = bni1;

										vi1 = vi4;
										ti1 = ti4;
										ni1 = ni4;
										
	// 									vi3 = vi4;
	// 									ti3 = ti4;
	// 									ni3 = ni4;
									}

									addFace( vi1, vi2, vi3, ti1, ti2, ti3, ni1, ni2, ni3 );
								}*/

								
								if ( vi4 != 0 )
								{
									int bvi1 = vi1;
									int bvi2 = vi2;
									int bvi3 = vi3;

									int bti1 = ti1;
									int bti2 = ti2;
									int bti3 = ti3;
									
									int bni1 = ni1;
									int bni2 = ni2;
									int bni3 = ni3;

									
									
									if ( alternate )
									{
// 										std::cout << "a" << std::endl;
										
										vi1 = bvi3;
										ti1 = bti3;
										ni1 = bni3;
										
										vi2 = vi4;
										ti2 = ti4;
										ni2 = ni4;
										
										vi3 = bvi1;
										ti3 = bti1;
										ni3 = bni1;
									}
									else
									{
// 										std::cout << "b      " << line << std::endl;
										
										vi1 = vi4;
										ti1 = ti4;
										ni1 = ni4;

										vi3 = bvi2;
										ti3 = bti2;
										ni3 = bni2;

										vi2 = bvi3;
										ti2 = bti3;
										ni2 = bni3;
										
									}

									addFace( vi1, vi2, vi3, ti1, ti2, ti3, ni1, ni2, ni3 );
								}
								

							alternate = !alternate;
							parseH.trimWhitespaces(line);
							vindex4 = "";
							vindex4 = parseH.returnUntillStrip( '/', line );
						}
						
						
						
						
						
// 						// 4
// 						int vi4 = -1, vi5 = -1, vi6 = -1;
// 						int ti4 = -1, ti5 = -1, ti6 = -1;
// 						int ni4 = -1, ni5 = -1, ni6 = -1;
// 						
// 						
// 						std::string vindex4, tindex4, vindex5, tindex5, vindex6, tindex6;
// 
// 						vindex4 = parseH.returnUntillStrip( '/', line );
// 						if ( !vindex4.empty() ) vi4 = atoi( vindex4.c_str() );
// 						tindex4 = parseH.returnUntillStrip( '/', line );
// 						if ( !tindex4.empty() ) ti4 = atoi( tindex4.c_str() );
// 						parseH.parseInt(line, ni4);
// 
// 						if ( vi4 != -1 )
// 						{
// 							addFace( vi1, vi3, vi4, ti1, ti3, ti4, ni1, ni3, ni4 );
// 						
// 							// 5
// 							parseH.trimWhitespaces(line);
// 							vindex5 = parseH.returnUntillStrip( '/', line );
// 							if ( !vindex5.empty() ) vi5 = atoi( vindex5.c_str() );
// 							tindex5 = parseH.returnUntillStrip( '/', line );
// 							if ( !tindex5.empty() ) ti5 = atoi( tindex5.c_str() );
// 							parseH.parseInt(line, ni5);
// 					
// 							if ( vi5 != -1 )
// 							{
// 								addFace( vi1, vi4, vi5, ti1, ti4, ti5, ni1, ni4, ni5 );
// 								
// 								
// 								// 6
// 								parseH.trimWhitespaces(line);
// 								vindex6 = parseH.returnUntillStrip( '/', line );
// 								if ( !vindex6.empty() ) vi6 = atoi( vindex5.c_str() );
// 								tindex6 = parseH.returnUntillStrip( '/', line );
// 								if ( !tindex6.empty() ) ti6 = atoi( tindex6.c_str() );
// 								parseH.parseInt(line, ni6);
// 						
// 								if ( vi6 != -1 )
// 								{
// 									addFace( vi5, vi4, vi6, ti5, ti4, ti6, ni5, ni4, ni6 );
// 								}
// 								
// 							}
// 							
// 						}

					}
					
					
// 					exit(0);
// 						cerr << m_numberTIndices<< endl;
					assert ( m_numberNIndices ==  m_numberVIndices && m_numberVIndices == m_numberTIndices  );

				}
// 				else
// 				{
// 					std::cout << "obj: type '" << otype << "' not recognised" << std::endl;
// 				}
			}
		}
	}

	const size_t size=facematerials.size();

	// calculate facematerial triangle numbers
	for ( unsigned int i=1; i < size; i++ )
	{
		Facematerial* previousFM = &facematerials[ i-1 ];
		previousFM->faceindex_number = facematerials[i].faceindex_first - previousFM->faceindex_first;
	}
	// to calculate the last one we need to use m_numberVIndices
	Facematerial* previousFM = &facematerials[ size-1 ];
	previousFM->faceindex_number = m_numberVIndices - previousFM->faceindex_first;

// 	cerr << "end loading obj" << endl;
}

void BeObjLoader::addFace( const int vi1, const int vi2, const int vi3, const int ti1, const int ti2, const int ti3, const int ni1, const int ni2, const int ni3 )
{
	const auto m_numberVertices_by_3 = (m_numberVertices / 3)+1;
	const auto m_numberTexCoor_by_2 = (m_numberTexCoor / 2)+1;
	const auto m_numberNormals_by_3 = (m_numberNormals / 3)+1;
	
	
// 	if ( vi1 != -1 )	gVIndices[m_numberVIndices++] = vi1;
// 	else		gVIndices[m_numberVIndices++] = m_numberVertices_by_3 + vi1;
// 	if ( vi2 != -1 )	gVIndices[m_numberVIndices++] = vi2;
// 	else		gVIndices[m_numberVIndices++] = m_numberVertices_by_3 + vi2;
// 	if ( vi3 != -1 )	gVIndices[m_numberVIndices++] = vi3;
// 	else		gVIndices[m_numberVIndices++] = m_numberVertices_by_3 + vi3;
// 
// 	if ( ti1 != -1 )	gTIndices[m_numberTIndices++] = ti1;
// 	else		gTIndices[m_numberTIndices++] = m_numberTexCoor_by_2 + ti1;
// 	if ( ti2 != -1 )	gTIndices[m_numberTIndices++] = ti2;
// 	else		gTIndices[m_numberTIndices++] = m_numberTexCoor_by_2 + ti2;
// 	if ( ti3 != -1 )	gTIndices[m_numberTIndices++] = ti3;
// 	else		gTIndices[m_numberTIndices++] = m_numberTexCoor_by_2 + ti3;
// 
// 	if ( ni1 != -1 )	gNIndices[m_numberNIndices++] = ni1;
// 	else		gNIndices[m_numberNIndices++] = m_numberNormals_by_3 + ni1;
// 	if ( ni2 != -1 )	gNIndices[m_numberNIndices++] = ni2;
// 	else		gNIndices[m_numberNIndices++] = m_numberNormals_by_3 + ni2;
// 	if ( ni3 != -1 )	gNIndices[m_numberNIndices++] = ni3;
// 	else		gNIndices[m_numberNIndices++] = m_numberNormals_by_3 + ni3;

	
	if ( vi1 > 0 )	gVIndices[m_numberVIndices++] = vi1;
	else		gVIndices[m_numberVIndices++] = m_numberVertices_by_3 + vi1;
	if ( vi2 > 0 )	gVIndices[m_numberVIndices++] = vi2;
	else		gVIndices[m_numberVIndices++] = m_numberVertices_by_3 + vi2;
	if ( vi3 > 0 )	gVIndices[m_numberVIndices++] = vi3;
	else		gVIndices[m_numberVIndices++] = m_numberVertices_by_3 + vi3;

	if ( ti1 > 0 )	gTIndices[m_numberTIndices++] = ti1;
	else		gTIndices[m_numberTIndices++] = m_numberTexCoor_by_2 + ti1;
	if ( ti2 > 0 )	gTIndices[m_numberTIndices++] = ti2;
	else		gTIndices[m_numberTIndices++] = m_numberTexCoor_by_2 + ti2;
	if ( ti3 > 0 )	gTIndices[m_numberTIndices++] = ti3;
	else		gTIndices[m_numberTIndices++] = m_numberTexCoor_by_2 + ti3;

	if ( ni1 > 0 )	gNIndices[m_numberNIndices++] = ni1;
	else		gNIndices[m_numberNIndices++] = m_numberNormals_by_3 + ni1;
	if ( ni2 > 0 )	gNIndices[m_numberNIndices++] = ni2;
	else		gNIndices[m_numberNIndices++] = m_numberNormals_by_3 + ni2;
	if ( ni3 > 0 )	gNIndices[m_numberNIndices++] = ni3;
	else		gNIndices[m_numberNIndices++] = m_numberNormals_by_3 + ni3;
	
}


void BeObjLoader::loadMaterialfile( BeFilesystem& filesystem, const std::string& mpath, const std::string& file )
{
	std::string fullfilename(mpath);
	fullfilename.append(file);

	BeFile materialbefile;
	
	if ( filesystem.load( materialbefile, fullfilename ) )
	{
		Material* material = 0;
		std::string line;
		std::string name;
		BeParser parseH;
		while ( materialbefile.getLine(line) )
		{
			parseH.reset();
	// 		std::cerr << line << std::endl;
			// trim spaces
			parseH.trimWhitespaces(line);
			// remove comment lines
			parseH.removeCommentlines(line);

			if ( parseH.position_index != std::string::npos )
			{

	// 				cerr << line << endl;

	// 				unsigned int type;
				const std::string& otype = parseH.returnUntillStrip( ' ', line );
				if ( !otype.empty() )
				{

					if ( otype == "newmtl" )
					{
						name = parseH.returnUntillStrip( ' ', line );
	// 						cerr << "new material, name: " << name << endl;
						matlist[name] = Material();
						material = &matlist[name];
					}

					else if ( otype == "map_Kd" )
					{
						std::string texturename = mpath;
// 						texturename.append( "textures/" );
						texturename.append( parseH.returnUntillStrip( ' ', line ) );
	// 						matlist[currentname].textureid = Texturestore::Instance()->load( texturename );
						material->m_imagePath=texturename;

	// 						cerr << "material texture: " << texturename  << " ! " << matlist[currentname].textureid << endl << endl;
					}

					else if ( otype == "map_bump" )
					{
						std::string texturename = mpath;
// 						texturename.append( "textures/" );
						texturename.append( parseH.returnUntillStrip( ' ', line ) );
	// 						matlist[currentname].textureid = Texturestore::Instance()->load( texturename );
						material->m_imagePathBump=texturename;

	// 						cerr << "material texture: " << texturename  << " ! " << matlist[currentname].textureid << endl << endl;
					}

					else if ( otype == "Ka" )
					{
                        btVector3 ambient;
                        parseH.parseVector3(line, ambient);
						material->m_material.setAmbient(ambient);
	// 						cerr << x << endl;
	// 						cerr << y << endl;
	// 						cerr << z << endl;
					}

					else if ( otype == "Kd" )
					{
                        btVector3 diffuse;
                        parseH.parseVector3(line, diffuse);
                        material->m_material.setDiffuse(diffuse);
// 												std::cerr << x << std::endl;
// 												std::cerr << y << std::endl;
// 												std::cerr << z << std::endl;

						//GL workaround for ambient set to black in obj materials
						if( material->m_material.getAmbient() == btVector3(0,0,0) )
						{
							material->m_material.setAmbient( material->m_material.getDiffuse() );
// 							m_logDebug << "::OBJ warning: " << file << " (" << name << ")" << ": Ambient 0, setting to diffuse color" << "\n";
// 							material->m_material.setAmbient( Vector4f(0.4,0.4,0.4,1) );
						}


					}
					else if ( otype == "Ks" )
					{
						btVector3 specular;
                        parseH.parseVector3(line, specular);
						material->m_material.setSpecular(specular);
						// 						cerr << x << endl;
						// 						cerr << y << endl;
						// 						cerr << z << endl;
					}
					else if( otype == "Ns" )
					{
						float shininess = 0.0f;
                        //atof(parseH.returnUntillStrip( ' ', line ).c_str())
                        parseH.parseFloat(line, shininess);
                        shininess *= 0.128;
						
//                         shininess/=1000.0f*128.0f;
	// 						cerr << "ns yo " << Ns << currentname <<  endl;
						material->m_material.setShininess(shininess);
	// 						assert( material.Ns <= 128.0f ); //Ensure its in valid gl range
					}

					else if( otype == "d" || otype == "Tr" )
					{
						//Transparency, so will store in diffuse alpha component
						//Apparently some materials use d, others use Tr
	// 						material.d = atof(parseH.returnUntillStrip( " ", line ).c_str());
						float alpha = 1.0f;
                        //atof(parseH.returnUntillStrip( ' ', line ).c_str());
                        parseH.parseFloat(line, alpha);
						material->m_material.getDiffuse().setW(alpha);
	// 						assert( material.d <= 1.0f ); //Ensure its in valid gl range
					}
				}
			}
		}
	}
// 		cerr << "loaded" << endl;
}

BeObjLoader::~BeObjLoader()
{
	delete[] gVertices;
	delete[] gNormals;
	delete[] gTexCoor;
	delete[] gVIndices;
	delete[] gTIndices;
	delete[] gNIndices;
}


 
