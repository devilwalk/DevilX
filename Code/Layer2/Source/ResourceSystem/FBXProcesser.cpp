#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;

namespace NSDevilX
{
	namespace NSResourceSystem
	{
		namespace NSInternal
		{
			static Void getNodes(fbxsdk::FbxNode * node,OUT TVector<fbxsdk::FbxNode*> & nodes)
			{
				if(node->GetVisibility())
					nodes.push_back(node);
				for(auto i=0;i<node->GetChildCount();++i)
				{
					getNodes(node->GetChild(i),nodes);
				}
			}
			static Int32 makePolygonKey(Int32 polygonIndex,Int32 vertexIndex)
			{
				return (polygonIndex<<2)+vertexIndex;
			}
			static Void parsePolygonKey(Int32 key,OUT Int32 & polygonIndex,OUT Int32 & vertexIndex)
			{
				polygonIndex=key>>2;
				vertexIndex=key&0x3;
			}
			static TVector<TVector<Int32> > processPolygonKeys(fbxsdk::FbxMesh * mesh)
			{
				TVector<TVector<Int32> > ret;
				ret.resize(mesh->GetControlPointsCount());
				for(auto polygon_index=0;polygon_index<mesh->GetPolygonCount();++polygon_index)
				{
					assert(3==mesh->GetPolygonSize(polygon_index));
					for(auto vertex_index=0;vertex_index<3;++vertex_index)
					{
						ret[mesh->GetPolygonVertex(polygon_index,vertex_index)].push_back(makePolygonKey(polygon_index,vertex_index));
					}
				}
				return ret;
			}
			static Void processPositions(fbxsdk::FbxMesh * mesh,OUT TVector<CFBXProcesser::SVertex> & vertices)
			{
				fbxsdk::FbxAMatrix geo_transform(fbxsdk::FbxVector4(mesh->GetNode()->GeometricTranslation.Get()),fbxsdk::FbxVector4(mesh->GetNode()->GeometricRotation.Get()),fbxsdk::FbxVector4(mesh->GetNode()->GeometricScaling.Get()));
				for(auto polygon_index=0;polygon_index<mesh->GetPolygonCount();++polygon_index)
				{
					assert(3==mesh->GetPolygonSize(polygon_index));
					for(auto vertex_index=0;vertex_index<3;++vertex_index)
					{
						vertices[polygon_index*3+vertex_index].mPosition=(mesh->GetNode()->EvaluateGlobalTransform()*geo_transform).MultT(mesh->GetControlPointAt(mesh->GetPolygonVertex(polygon_index,vertex_index)));
					}
				}
			}
			static Void processNormals(fbxsdk::FbxMesh * mesh,const TVector<TVector<Int32> > & polygonKeys,OUT TVector<CFBXProcesser::SVertex> & vertices)
			{
				assert(mesh->GetElementNormalCount()<=1);
				if(!mesh->GetElementNormalCount())
					return;

				fbxsdk::FbxAMatrix geo_transform;
				geo_transform.SetR(fbxsdk::FbxVector4(mesh->GetNode()->GeometricRotation.Get()));
				fbxsdk::FbxAMatrix global_transform;
				global_transform.SetR(mesh->GetNode()->EvaluateGlobalTransform().GetR());

				auto layer_normals=mesh->GetElementNormal();
				switch(layer_normals->GetMappingMode())
				{
				case fbxsdk::FbxLayerElement::eByControlPoint:
				{
					switch(layer_normals->GetReferenceMode())
					{
					case fbxsdk::FbxLayerElement::eDirect:
						assert(layer_normals->GetDirectArray().GetCount()==mesh->GetControlPointsCount());
						for(auto normal_index=0;normal_index<layer_normals->GetDirectArray().GetCount();++normal_index)
						{
							auto normal=(global_transform*geo_transform).MultT(layer_normals->GetDirectArray()[normal_index]);
							for(auto key:polygonKeys[normal_index])
							{
								Int32 polygon_index;
								Int32 vertex_index;
								NSInternal::parsePolygonKey(key,polygon_index,vertex_index);
								vertices[polygon_index*3+vertex_index].mNormal=normal;
							}
						}
						break;
					case fbxsdk::FbxLayerElement::eIndex:
					case fbxsdk::FbxLayerElement::eIndexToDirect:
						assert(layer_normals->GetIndexArray().GetCount()==mesh->GetControlPointsCount());
						for(auto normal_index=0;normal_index<layer_normals->GetIndexArray().GetCount();++normal_index)
						{
							auto normal=(global_transform*geo_transform).MultT(layer_normals->GetDirectArray()[layer_normals->GetIndexArray()[normal_index]]);
							for(auto key:polygonKeys[normal_index])
							{
								Int32 polygon_index;
								Int32 vertex_index;
								NSInternal::parsePolygonKey(key,polygon_index,vertex_index);
								vertices[polygon_index*3+vertex_index].mNormal=normal;
							}
						}
						break;
					default:
						assert(false);
					}
				}
				break;
				case fbxsdk::FbxLayerElement::eByPolygonVertex:
					switch(layer_normals->GetReferenceMode())
					{
					case fbxsdk::FbxLayerElement::eDirect:
						assert(layer_normals->GetDirectArray().GetCount()==mesh->GetPolygonVertexCount());
						for(auto i=0;i<layer_normals->GetDirectArray().GetCount();++i)
						{
							auto normal=layer_normals->GetDirectArray()[i];
							vertices[i].mNormal=normal;
						}
						break;
					case fbxsdk::FbxLayerElement::eIndex:
					case fbxsdk::FbxLayerElement::eIndexToDirect:
						assert(layer_normals->GetIndexArray().GetCount()==mesh->GetPolygonVertexCount());
						for(auto i=0;i<layer_normals->GetDirectArray().GetCount();++i)
						{
							auto normal=layer_normals->GetDirectArray()[layer_normals->GetIndexArray()[i]];
							vertices[i].mNormal=normal;
						}
						break;
					default:
						assert(false);
					}
					break;
				default:
					assert(false);
				}
			}
			static Void processUV0s(fbxsdk::FbxMesh * mesh,const TVector<TVector<Int32> > & polygonKeys,OUT TVector<CFBXProcesser::SVertex> & vertices)
			{
				if(!mesh->GetUVLayerCount())
					return;

				auto layer_uv=mesh->GetElementUV();
				switch(layer_uv->GetMappingMode())
				{
				case fbxsdk::FbxLayerElement::eByControlPoint:
				{
					switch(layer_uv->GetReferenceMode())
					{
					case fbxsdk::FbxLayerElement::eDirect:
						assert(layer_uv->GetDirectArray().GetCount()==mesh->GetControlPointsCount());
						for(auto i=0;i<layer_uv->GetDirectArray().GetCount();++i)
						{
							auto uv=layer_uv->GetDirectArray()[i];
							for(auto key:polygonKeys[i])
							{
								Int32 polygon_index;
								Int32 vertex_index;
								NSInternal::parsePolygonKey(key,polygon_index,vertex_index);
								vertices[polygon_index*3+vertex_index].mUV0=uv;
							}
						}
						break;
					case fbxsdk::FbxLayerElement::eIndex:
					case fbxsdk::FbxLayerElement::eIndexToDirect:
						assert(layer_uv->GetIndexArray().GetCount()==mesh->GetControlPointsCount());
						for(auto i=0;i<layer_uv->GetDirectArray().GetCount();++i)
						{
							auto uv=layer_uv->GetDirectArray()[layer_uv->GetIndexArray()[i]];
							for(auto key:polygonKeys[i])
							{
								Int32 polygon_index;
								Int32 vertex_index;
								NSInternal::parsePolygonKey(key,polygon_index,vertex_index);
								vertices[polygon_index*3+vertex_index].mUV0=uv;
							}
						}
						break;
					default:
						assert(false);
					}
				}
				break;
				case fbxsdk::FbxLayerElement::eByPolygonVertex:
					switch(layer_uv->GetReferenceMode())
					{
					case fbxsdk::FbxLayerElement::eDirect:
						assert(layer_uv->GetDirectArray().GetCount()==mesh->GetPolygonVertexCount());
						for(auto i=0;i<layer_uv->GetDirectArray().GetCount();++i)
						{
							auto uv=layer_uv->GetDirectArray()[i];
							vertices[i].mUV0=uv;
						}
						break;
					case fbxsdk::FbxLayerElement::eIndex:
					case fbxsdk::FbxLayerElement::eIndexToDirect:
						assert(layer_uv->GetIndexArray().GetCount()==mesh->GetPolygonVertexCount());
						for(auto i=0;i<layer_uv->GetDirectArray().GetCount();++i)
						{
							auto uv=layer_uv->GetDirectArray()[layer_uv->GetIndexArray()[i]];
							vertices[i].mUV0=uv;
						}
						break;
					default:
						assert(false);
					}
					break;
				default:
					assert(false);
				}
			}
			static TVector<fbxsdk::FbxCluster*> processSkin(fbxsdk::FbxMesh * mesh,const TVector<TVector<Int32> > & polygonKeys,OUT TVector<CFBXProcesser::SVertex> & vertices)
			{
				TVector<fbxsdk::FbxCluster*> ret;
				assert(mesh->GetDeformerCount()<=1);
				if(mesh->GetDeformerCount())
				{
					for(auto deformer_index=0;deformer_index<mesh->GetDeformerCount();++deformer_index)
					{
						if(mesh->GetDeformer(deformer_index)->GetDeformerType()!=fbxsdk::FbxDeformer::eSkin)
							continue;
						auto skin=static_cast<fbxsdk::FbxSkin*>(mesh->GetDeformer(deformer_index));
						for(auto cluster_index=0;cluster_index<skin->GetClusterCount();cluster_index++)
						{
							auto cluster=skin->GetCluster(cluster_index);
							for(auto control_point_index=0;control_point_index<cluster->GetControlPointIndicesCount();++control_point_index)
							{
								for(auto polygon_key:polygonKeys[cluster->GetControlPointIndices()[control_point_index]])
								{
									Int32 polygon_index;
									Int32 vertex_index;
									NSInternal::parsePolygonKey(polygon_key,polygon_index,vertex_index);
									CFBXProcesser::SVertex::SSkinInfo skin_info;
									skin_info.mCluster=cluster;
									skin_info.mWeight=static_cast<Float>(cluster->GetControlPointWeights()[control_point_index]);
									vertices[3*polygon_index+vertex_index].mSkinInfos.push_back(skin_info);
								}
							}
							ret.push_back(cluster);
						}
					}
				}
				return ret;
			}
			static Void processMaterial(fbxsdk::FbxMesh * mesh,const TVector<TVector<Int32> > & polygonKeys,OUT TVector<CFBXProcesser::SVertex> & vertices)
			{
				for(auto element_material_index=0;element_material_index<mesh->GetElementMaterialCount();++element_material_index)
				{
					auto element_material=mesh->GetElementMaterial(element_material_index);
					switch(element_material->GetMappingMode())
					{
					//case fbxsdk::FbxLayerElement::eByControlPoint:
					//	switch(element_material->GetReferenceMode())
					//	{
					//	case fbxsdk::FbxLayerElement::eIndex:
					//	case fbxsdk::FbxLayerElement::eIndexToDirect:
					//		assert(element_material->GetIndexArray().GetCount()==mesh->GetControlPointsCount());
					//		for(auto i=0;i<element_material->GetIndexArray().GetCount();++i)
					//		{
					//			auto material=mesh->GetNode()->GetMaterial(i);
					//			for(auto key:polygonKeys[i])
					//			{
					//				Int32 polygon_index;
					//				Int32 vertex_index;
					//				NSInternal::parsePolygonKey(key,polygon_index,vertex_index);
					//				vertices[polygon_index*3+vertex_index].mMaterial.mLambert=dynamic_cast<fbxsdk::FbxSurfaceLambert*>(material);
					//				vertices[polygon_index*3+vertex_index].mMaterial.mPhong=dynamic_cast<fbxsdk::FbxSurfacePhong*>(material);
					//			}
					//		}
					//		break;
					//	default:
					//		assert(false);
					//	}
					//	break;
					//case fbxsdk::FbxLayerElement::eByPolygonVertex:
					//	switch(element_material->GetReferenceMode())
					//	{
					//	case fbxsdk::FbxLayerElement::eIndex:
					//	case fbxsdk::FbxLayerElement::eIndexToDirect:
					//		assert(element_material->GetIndexArray().GetCount()==mesh->GetPolygonVertexCount());
					//		for(auto i=0;i<element_material->GetIndexArray().GetCount();++i)
					//		{
					//			auto material=mesh->GetNode()->GetMaterial(i);
					//			vertices[i].mMaterial.mLambert=dynamic_cast<fbxsdk::FbxSurfaceLambert*>(material);
					//			vertices[i].mMaterial.mPhong=dynamic_cast<fbxsdk::FbxSurfacePhong*>(material);
					//		}
					//		break;
					//	default:
					//		assert(false);
					//	}
					//	break;
					case fbxsdk::FbxLayerElement::eByPolygon:
						switch(element_material->GetReferenceMode())
						{
						case fbxsdk::FbxLayerElement::eIndex:
						case fbxsdk::FbxLayerElement::eIndexToDirect:
							assert(element_material->GetIndexArray().GetCount()==mesh->GetPolygonCount());
							for(auto i=0;i<element_material->GetIndexArray().GetCount();++i)
							{
								auto material=mesh->GetNode()->GetMaterial(element_material->GetIndexArray()[i]);
								if(material->GetClassId().Is(fbxsdk::FbxSurfacePhong::ClassId))
								{
									for(auto vertex_index=0;vertex_index<3;++vertex_index)
									{
										auto index=i*3+vertex_index;
										vertices[index].mMaterial=static_cast<fbxsdk::FbxSurfacePhong*>(material);
									}
								}
								else if(material->GetClassId().Is(fbxsdk::FbxSurfaceLambert::ClassId))
								{
									for(auto vertex_index=0;vertex_index<3;++vertex_index)
									{
										auto index=i*3+vertex_index;
										vertices[index].mMaterial=static_cast<fbxsdk::FbxSurfaceLambert*>(material);
									}
								}
							}
							break;
						default:
							assert(false);
						}
						break;
					case fbxsdk::FbxLayerElement::eAllSame:
						switch(element_material->GetReferenceMode())
						{
						case fbxsdk::FbxLayerElement::eIndex:
						case fbxsdk::FbxLayerElement::eIndexToDirect:
							assert(element_material->GetIndexArray().GetCount()==1);
							{
								auto material=mesh->GetNode()->GetMaterial(element_material->GetIndexArray()[0]);
								if(material->GetClassId().Is(fbxsdk::FbxSurfacePhong::ClassId))
								{
									for(auto & vertex:vertices)
									{
										vertex.mMaterial=static_cast<fbxsdk::FbxSurfacePhong*>(material);
									}
								}
								else if(material->GetClassId().Is(fbxsdk::FbxSurfaceLambert::ClassId))
								{
									for(auto & vertex:vertices)
									{
										vertex.mMaterial=static_cast<fbxsdk::FbxSurfaceLambert*>(material);
									}
								}
							}
							break;
						default:
							assert(false);
						}
						break;
					default:
						assert(false);
					}
				}
			}
			class CFBXStream
				:public fbxsdk::FbxStream
				,public TBaseObject<CFBXStream>
			{
			protected:
				CDataStreamReader*mResource;
			public:
				CFBXStream(IResourceImp * res)
					:mResource(res->getBuffer()->createReader())
				{}
				~CFBXStream()
				{
					mResource->getStream()->destroyReader(mResource);
				}
				/** Query the current state of the stream. */
				virtual fbxsdk::FbxStream::EState GetState() override
				{
					return eOpen;
				}

				/** Open the stream.
				* \return True if successful.
				* \remark Each time the stream is open or closed, the stream position must be reset to zero. */
				virtual bool Open(void* pStreamData) override
				{
					mResource->setPosition(0);
					return true;
				}

				/** Close the stream.
				* \return True if successful.
				* \remark Each time the stream is open or closed, the stream position must be reset to zero. */
				virtual bool Close() override
				{
					mResource->setPosition(0);
					return true;
				}

				/** Empties the internal data of the stream.
				* \return True if successful. */
				virtual bool Flush() override
				{
					return false;
				}

				/** Writes a memory block.
				* \param pData Pointer to the memory block to write.
				* \param pSize Size (in bytes) of the memory block to write.
				* \return The number of bytes written in the stream. */
				virtual int Write(const void* /*pData*/,int /*pSize*/) override
				{
					return 0;
				}

				/** Read bytes from the stream and store them in the memory block.
				* \param pData Pointer to the memory block where the read bytes are stored.
				* \param pSize Number of bytes read from the stream.
				* \return The actual number of bytes successfully read from the stream. */
				virtual int Read(void* pData,int pSize) const override
				{
					return static_cast<int>(mResource->process(pSize,pData));
				}

				/** If not specified by KFbxImporter::Initialize(), the importer will ask
				* the stream to select an appropriate reader ID to associate with the stream.
				* FbxIOPluginRegistry can be used to locate id by extension or description.
				* Return -1 to allow FBX to select an appropriate default. */
				virtual int GetReaderID() const override
				{
					return -1;
				}

				/** If not specified by KFbxExporter::Initialize(), the exporter will ask
				* the stream to select an appropriate writer ID to associate with the stream.
				* KFbxIOPluginRegistry can be used to locate id by extension or description.
				* Return -1 to allow FBX to select an appropriate default. */
				virtual int GetWriterID() const override
				{
					return -1;
				}

				/** Adjust the current stream position.
				* \param pSeekPos Pre-defined position where offset is added (FbxFile::eBegin, FbxFile::eCurrent:, FbxFile::eEnd)
				* \param pOffset Number of bytes to offset from pSeekPos. */
				virtual void Seek(const fbxsdk::FbxInt64& pOffset,const fbxsdk::FbxFile::ESeekPos& pSeekPos) override
				{
					fbxsdk::FbxInt64 begin_pos=0;
					switch(pSeekPos)
					{
					case fbxsdk::FbxFile::eBegin:begin_pos=0;break;
					case fbxsdk::FbxFile::eEnd:begin_pos=mResource->getStream()->getSize()-1;break;
					case fbxsdk::FbxFile::eCurrent:begin_pos=mResource->getPosition();break;
					}
					mResource->setPosition(static_cast<UInt32>(begin_pos+pOffset));
				}

				/** Get the current stream position.
				* \return Current number of bytes from the beginning of the stream. */
				virtual long GetPosition() const override
				{
					return static_cast<long>(mResource->getPosition());
				}

				/** Set the current stream position.
				* \param pPosition Number of bytes from the beginning of the stream to seek to. */
				virtual void SetPosition(long pPosition) override
				{
					mResource->setPosition(static_cast<UInt32>(pPosition));
				}

				/** Return 0 if no errors occurred. Otherwise, return 1 to indicate
				* an error. This method will be invoked whenever FBX needs to verify
				* that the last operation succeeded. */
				virtual int GetError() const override
				{
					return 0;
				}

				/** Clear current error condition by setting the current error value to 0. */
				virtual void ClearError() override
				{

				}
			};
		}
	}
}

NSDevilX::NSResourceSystem::CFBXProcesser::CFBXProcesser(IResourceImp * res)
	:mResource(res)
{
}

NSDevilX::NSResourceSystem::CFBXProcesser::~CFBXProcesser()
{
}

Void NSDevilX::NSResourceSystem::CFBXProcesser::process(NSRenderSystem::IEntity * entity)
{
	auto manager=fbxsdk::FbxManager::Create();
	auto importer=fbxsdk::FbxImporter::Create(manager,"");
	auto scene=fbxsdk::FbxScene::Create(manager,"");
	NSInternal::CFBXStream stream(mResource);
	if(!importer->Initialize(&stream,nullptr,manager->GetIOPluginRegistry()->GetNativeReaderFormat()))
	{
#ifdef _MSC_VER
		OutputDebugStringA("\r\n");
		OutputDebugStringA(importer->GetStatus().GetErrorString());
		OutputDebugStringA("\r\n");
#endif
	}
	importer->Import(scene);
	importer->Destroy();
	fbxsdk::FbxGeometryConverter converter(manager);
	converter.RemoveBadPolygonsFromMeshes(scene);
	converter.Triangulate(scene,true);
	fbxsdk::FbxAxisSystem::DirectX.ConvertScene(scene);
	TVector<fbxsdk::FbxNode*> nodes;
	NSInternal::getNodes(scene->GetRootNode(),nodes);
	struct SMeshInfo
	{
		TVector<TVector<SVertex> > mVerticesByMaterial;
		TVector<TVector<Int32> > mIndicesByMaterial;
		TVector<fbxsdk::FbxCluster*> mClusters;
		TVector<fbxsdk::FbxSurfaceLambert*> mMaterials;
	};
	TVector<SMeshInfo> mesh_infos;
	for(auto node:nodes)
	{
		if(node->GetNodeAttributeCount()>0)
		{
			for(auto attr_index=0;attr_index<node->GetNodeAttributeCount();++attr_index)
			{
				auto attr=node->GetNodeAttributeByIndex(attr_index);
				switch(attr->GetAttributeType())
				{
				case fbxsdk::FbxNodeAttribute::eMesh:
				{
					SMeshInfo mesh_info;
					auto mesh=static_cast<fbxsdk::FbxMesh*>(attr);
					TVector<TVector<Int32> > polygon_keys_by_control_point_index=NSInternal::processPolygonKeys(mesh);
					TVector<SVertex> vertices;
					auto num_vertices=mesh->GetPolygonCount()*3;
					vertices.resize(num_vertices);
					NSInternal::processPositions(mesh,vertices);
					NSInternal::processNormals(mesh,polygon_keys_by_control_point_index,vertices);
					NSInternal::processUV0s(mesh,polygon_keys_by_control_point_index,vertices);
					mesh_info.mClusters=NSInternal::processSkin(mesh,polygon_keys_by_control_point_index,vertices);
					NSInternal::processMaterial(mesh,polygon_keys_by_control_point_index,vertices);

					//collect material
					for(SizeT vertex_index=0;vertex_index<vertices.size();vertex_index+=3)
					{
						assert(vertices[vertex_index].mMaterial==vertices[vertex_index+1].mMaterial);
						assert(vertices[vertex_index].mMaterial==vertices[vertex_index+2].mMaterial);
						if(!mesh_info.mMaterials.has(vertices[vertex_index].mMaterial))
						{
							mesh_info.mMaterials.push_back(vertices[vertex_index].mMaterial);
						}
					}
					//sort polygon by material
					if(mesh_info.mMaterials.size()>1)
					{
						for(auto const & material:mesh_info.mMaterials)
						{
							TVector<SVertex> temp;
							for(SizeT vertex_index=0;vertex_index<vertices.size();vertex_index+=3)
							{
								if(vertices[vertex_index].mMaterial==material)
								{
									temp.push_back(vertices[vertex_index]);
									temp.push_back(vertices[vertex_index+1]);
									temp.push_back(vertices[vertex_index+2]);
								}
							}
							mesh_info.mVerticesByMaterial.push_back(temp);
						}
					}
					else
					{
						mesh_info.mVerticesByMaterial.push_back(vertices);
					}
					for(auto & vertices:mesh_info.mVerticesByMaterial)
					{//fill indices
						TVector<SVertex> new_vertices;
						TVector<TVector<Int32> > index_positions;
						for(SizeT vertex_index=0;vertex_index<vertices.size();++vertex_index)
						{
							auto const &vertex=vertices[vertex_index];
							auto iter=new_vertices.find(vertex);
							if(new_vertices.end()!=iter)
							{
								SizeT new_vertex_position=iter-new_vertices.begin();
								if(index_positions.size()<=new_vertex_position)
									index_positions.resize(new_vertex_position+1);
								index_positions[new_vertex_position].push_back(vertex_index);
							}
							else
							{
								SizeT new_vertex_position=new_vertices.size();
								if(index_positions.size()<=new_vertex_position)
									index_positions.resize(new_vertex_position+1);
								index_positions[new_vertex_position].push_back(vertex_index);
								new_vertices.push_back(vertex);
							}
						}
						TVector<Int32> indices;
						indices.resize(vertices.size());
						for(SizeT vertex_index=0;vertex_index<new_vertices.size();++vertex_index)
						{
							for(auto index_position:index_positions[vertex_index])
							{
								indices[index_position]=vertex_index;
							}
						}
						mesh_info.mIndicesByMaterial.push_back(indices);
						vertices=new_vertices;
					}
					mesh_infos.push_back(mesh_info);
				}
				break;
				}
			}
		}
	}
	TVector<fbxsdk::FbxCluster*> clusters;
	TMap<fbxsdk::FbxCluster*,UInt8> cluster_indices;
	for(auto & mesh_info:mesh_infos)
	{
		for(auto cluster:mesh_info.mClusters)
		{
			if(clusters.has(cluster))
				continue;
			bool has_same=false;
			for(SizeT i=0;i<clusters.size();++i)
			{
				auto test=clusters[i];
				fbxsdk::FbxAMatrix src_mat,dst_mat;
				if((test->GetTransformMatrix(src_mat)==cluster->GetTransformMatrix(dst_mat))
					&&(test->GetTransformLinkMatrix(src_mat)==cluster->GetTransformLinkMatrix(dst_mat))
					&&(test->GetLink()==cluster->GetLink())
					)
				{
					cluster_indices[cluster]=static_cast<UInt8>(i);
					has_same=true;
					break;
				}
			}
			if(has_same)
				continue;
			cluster_indices[cluster]=static_cast<UInt8>(clusters.size());
			clusters.push_back(cluster);
		}
	}
	TVector<SVertex> vertices;
	for(const auto & mesh_info:mesh_infos)
	{
		for(const auto & ver:mesh_info.mVerticesByMaterial)
		{
			vertices.insert(vertices.end(),ver.begin(),ver.end());
		}
	}
	TVector<UInt32> indices;
	for(const auto & mesh_info:mesh_infos)
	{
		for(const auto & ind:mesh_info.mIndicesByMaterial)
		{
			indices.insert(indices.end(),ind.begin(),ind.end());
		}
	}
	auto geo=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createGeometry(entity->queryInterface_ISceneElement()->getName());
	geo->getVertexBuffer()->setCount(static_cast<UInt32>(vertices.size()));
	CFloat3 * positions=static_cast<CFloat3*>(DEVILX_ALLOC(sizeof(CFloat3)*vertices.size()));
	for(SizeT i=0;i<vertices.size();++i)
	{
		positions[i]=CFloat3(static_cast<Float>(vertices[i].mPosition[0]),static_cast<Float>(vertices[i].mPosition[1]),static_cast<Float>(vertices[i].mPosition[2]));
	}
	geo->getVertexBuffer()->setPositions(positions);
	CFloat3 * normals=static_cast<CFloat3*>(DEVILX_ALLOC(sizeof(CFloat3)*vertices.size()));
	for(SizeT i=0;i<vertices.size();++i)
	{
		normals[i]=CFloat3(static_cast<Float>(vertices[i].mNormal[0]),static_cast<Float>(vertices[i].mNormal[1]),static_cast<Float>(vertices[i].mNormal[2]));
	}
	geo->getVertexBuffer()->setNormals(normals);
	CFloat2 * uv0s=static_cast<CFloat2*>(DEVILX_ALLOC(sizeof(CFloat2)*vertices.size()));
	for(SizeT i=0;i<vertices.size();++i)
	{
		uv0s[i]=CFloat2(static_cast<Float>(vertices[i].mUV0[0]),static_cast<Float>(vertices[i].mUV0[1]));
	}
	geo->getVertexBuffer()->setTextureCoords(uv0s);
	CFloat4 * blend_weights=static_cast<CFloat4*>(DEVILX_ALLOC(sizeof(CFloat4)*vertices.size()));
	UInt8 * blend_indices=static_cast<UInt8*>(DEVILX_ALLOC(sizeof(UInt8)*4*vertices.size()));
	for(SizeT i=0;i<vertices.size();++i)
	{
		Float weights[]={0,0,0,0};
		UInt8 index[]={255,255,255,255};
		auto j=0;
		for(auto const & skin_info:vertices[i].mSkinInfos)
		{
			index[j]=cluster_indices.get(skin_info.mCluster);
			weights[j++]=skin_info.mWeight;
		}
		blend_weights[i]=CFloat4(weights[0],weights[1],weights[2],weights[3]);
		for(auto j=0;j<4;j++)
			blend_indices[i*4+j]=index[j];
	}
	geo->getVertexBuffer()->setBlendWeights(blend_weights);
	geo->getVertexBuffer()->setBlendIndices(blend_indices);
	geo->getIndexBuffer()->setCount(static_cast<UInt32>(indices.size()));
	UInt32 * indices_buf=static_cast<UInt32*>(DEVILX_ALLOC(sizeof(UInt32)*indices.size()));
	memcpy(indices_buf,&indices[0],sizeof(UInt32)*indices.size());
	geo->getIndexBuffer()->setIndices(indices_buf);

	UInt32 index_start=0;
	UInt32 vertex_start=0;
	for(const auto & mesh_info:mesh_infos)
	{
		for(SizeT i=0;i<mesh_info.mMaterials.size();++i)
		{
			auto sub_entity=entity->createSubEntity(CStringConverter::toString(entity->getSubEntityCount()));
			sub_entity->setGeometry(geo);
			sub_entity->queryInterface_IGeometryUsage()->setVertexBufferOffset(vertex_start);
			sub_entity->queryInterface_IGeometryUsage()->setVertexCount(static_cast<UInt32>(mesh_info.mVerticesByMaterial[i].size()));
			sub_entity->queryInterface_IGeometryUsage()->setIndexBufferOffset(index_start);
			sub_entity->queryInterface_IGeometryUsage()->setIndexCount(static_cast<UInt32>(mesh_info.mIndicesByMaterial[i].size()));
			sub_entity->queryInterface_IGeometryUsage()->setOperationType(NSRenderSystem::IEnum::EOperationType_TriangleList);
			sub_entity->setRenderable(true);
			sub_entity->setAmbientModel(NSRenderSystem::IEnum::EMaterialAmbientModel_Constant);
			sub_entity->setDiffuseModel(NSRenderSystem::IEnum::EMaterialDiffuseModel_Lambert);
			sub_entity->getDiffuseColourUnitState()->setEnable(true);
			CFloatRGB diffuse(static_cast<Float>(mesh_info.mMaterials[i]->Diffuse.Get()[0]),static_cast<Float>(mesh_info.mMaterials[i]->Diffuse.Get()[1]),static_cast<Float>(mesh_info.mMaterials[i]->Diffuse.Get()[2]));
			sub_entity->getDiffuseColourUnitState()->setValue(CFloatRGB(diffuse*static_cast<Float>(mesh_info.mMaterials[i]->DiffuseFactor.Get())));
			if(mesh_info.mMaterials[i]->GetClassId()==fbxsdk::FbxSurfacePhong::ClassId)
			{
				auto phong=static_cast<fbxsdk::FbxSurfacePhong*>(mesh_info.mMaterials[i]);
				sub_entity->setSpecularModel(NSRenderSystem::IEnum::EMaterialSpecularModel_Phong);
				sub_entity->getSpecularColourUnitState()->setEnable(true);
				CFloatRGB specular(static_cast<Float>(phong->Specular.Get()[0]),static_cast<Float>(phong->Specular.Get()[1]),static_cast<Float>(phong->Specular.Get()[2]));
				sub_entity->getSpecularColourUnitState()->setValue(CFloatRGB(specular*static_cast<Float>(phong->SpecularFactor.Get())));
				sub_entity->getSpecularPowerUnitState()->setEnable(true);
				sub_entity->getSpecularPowerUnitState()->setValue(static_cast<Float>(phong->Shininess.Get()));
			}
			for(auto src_obj_index=0;src_obj_index<mesh_info.mMaterials[i]->Diffuse.GetSrcObjectCount<fbxsdk::FbxTexture>();++src_obj_index)
			{

			}

			vertex_start+=mesh_info.mVerticesByMaterial[i].size();
			index_start+=mesh_info.mIndicesByMaterial[i].size();
		}
	}
	manager->Destroy();
}
