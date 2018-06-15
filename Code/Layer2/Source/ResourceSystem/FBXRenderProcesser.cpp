#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		namespace NSInternal
		{
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
			static Void processPositions(fbxsdk::FbxMesh * mesh,OUT TVector<CFBXRenderProcesser::SVertex> & vertices)
			{
				fbxsdk::FbxAMatrix geo_transform(fbxsdk::FbxVector4(mesh->GetNode()->GeometricTranslation.Get()),fbxsdk::FbxVector4(mesh->GetNode()->GeometricRotation.Get()),fbxsdk::FbxVector4(mesh->GetNode()->GeometricScaling.Get()));
				const auto global_transform=mesh->GetNode()->EvaluateGlobalTransform();
				for(auto polygon_index=0;polygon_index<mesh->GetPolygonCount();++polygon_index)
				{
					assert(3==mesh->GetPolygonSize(polygon_index));
					for(auto vertex_index=0;vertex_index<3;++vertex_index)
					{
						vertices[polygon_index*3+vertex_index].mPosition=(global_transform*geo_transform).MultT(mesh->GetControlPointAt(mesh->GetPolygonVertex(polygon_index,vertex_index)));
					}
				}
			}
			static Void processNormals(fbxsdk::FbxMesh * mesh,const TVector<TVector<Int32> > & polygonKeys,OUT TVector<CFBXRenderProcesser::SVertex> & vertices)
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
			static Void processTangents(fbxsdk::FbxMesh * mesh,const TVector<TVector<Int32> > & polygonKeys,OUT TVector<CFBXRenderProcesser::SVertex> & vertices)
			{
				assert(mesh->GetElementTangentCount()<=1);
				if(!mesh->GetElementTangentCount())
					return;

				fbxsdk::FbxAMatrix geo_transform;
				geo_transform.SetR(fbxsdk::FbxVector4(mesh->GetNode()->GeometricRotation.Get()));
				fbxsdk::FbxAMatrix global_transform;
				global_transform.SetR(mesh->GetNode()->EvaluateGlobalTransform().GetR());

				auto layer_tangents=mesh->GetElementTangent();
				switch(layer_tangents->GetMappingMode())
				{
				case fbxsdk::FbxLayerElement::eByControlPoint:
				{
					switch(layer_tangents->GetReferenceMode())
					{
					case fbxsdk::FbxLayerElement::eDirect:
						assert(layer_tangents->GetDirectArray().GetCount()==mesh->GetControlPointsCount());
						for(auto tangent_index=0;tangent_index<layer_tangents->GetDirectArray().GetCount();++tangent_index)
						{
							auto tangent=(global_transform*geo_transform).MultT(layer_tangents->GetDirectArray()[tangent_index]);
							for(auto key:polygonKeys[tangent_index])
							{
								Int32 polygon_index;
								Int32 vertex_index;
								NSInternal::parsePolygonKey(key,polygon_index,vertex_index);
								vertices[polygon_index*3+vertex_index].mTangent=tangent;
							}
						}
						break;
					case fbxsdk::FbxLayerElement::eIndex:
					case fbxsdk::FbxLayerElement::eIndexToDirect:
						assert(layer_tangents->GetIndexArray().GetCount()==mesh->GetControlPointsCount());
						for(auto tangent_index=0;tangent_index<layer_tangents->GetIndexArray().GetCount();++tangent_index)
						{
							auto tangent=(global_transform*geo_transform).MultT(layer_tangents->GetDirectArray()[layer_tangents->GetIndexArray()[tangent_index]]);
							for(auto key:polygonKeys[tangent_index])
							{
								Int32 polygon_index;
								Int32 vertex_index;
								NSInternal::parsePolygonKey(key,polygon_index,vertex_index);
								vertices[polygon_index*3+vertex_index].mTangent=tangent;
							}
						}
						break;
					default:
						assert(false);
					}
				}
				break;
				case fbxsdk::FbxLayerElement::eByPolygonVertex:
					switch(layer_tangents->GetReferenceMode())
					{
					case fbxsdk::FbxLayerElement::eDirect:
						assert(layer_tangents->GetDirectArray().GetCount()==mesh->GetPolygonVertexCount());
						for(auto i=0;i<layer_tangents->GetDirectArray().GetCount();++i)
						{
							auto normal=layer_tangents->GetDirectArray()[i];
							vertices[i].mTangent=normal;
						}
						break;
					case fbxsdk::FbxLayerElement::eIndex:
					case fbxsdk::FbxLayerElement::eIndexToDirect:
						assert(layer_tangents->GetIndexArray().GetCount()==mesh->GetPolygonVertexCount());
						for(auto i=0;i<layer_tangents->GetDirectArray().GetCount();++i)
						{
							auto tangent=layer_tangents->GetDirectArray()[layer_tangents->GetIndexArray()[i]];
							vertices[i].mTangent=tangent;
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
			static Void processUV0s(fbxsdk::FbxMesh * mesh,const TVector<TVector<Int32> > & polygonKeys,OUT TVector<CFBXRenderProcesser::SVertex> & vertices)
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
			static Void processSkin(fbxsdk::FbxMesh * mesh,const TVector<TVector<Int32> > & polygonKeys,OUT TVector<CFBXRenderProcesser::SVertex> & vertices)
			{
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
									CFBXRenderProcesser::SVertex::SSkinInfo skin_info;
									skin_info.mCluster=cluster;
									skin_info.mWeight=static_cast<Float>(cluster->GetControlPointWeights()[control_point_index]);
									vertices[3*polygon_index+vertex_index].mSkinInfos.push_back(skin_info);
								}
							}
						}
					}
				}
			}
			static fbxsdk::FbxSurfaceLambert * processMaterial(fbxsdk::FbxMesh * mesh)
			{
				fbxsdk::FbxSurfaceLambert * ret=nullptr;
				assert(mesh->GetElementMaterialCount()<=1);
				for(auto element_material_index=0;element_material_index<mesh->GetElementMaterialCount();++element_material_index)
				{
					auto element_material=mesh->GetElementMaterial(element_material_index);
					switch(element_material->GetMappingMode())
					{
					case fbxsdk::FbxLayerElement::eAllSame:
						switch(element_material->GetReferenceMode())
						{
						case fbxsdk::FbxLayerElement::eIndex:
						case fbxsdk::FbxLayerElement::eIndexToDirect:
							assert(element_material->GetIndexArray().GetCount()==1);
							{
								ret=static_cast<fbxsdk::FbxSurfaceLambert*>(mesh->GetNode()->GetMaterial(element_material->GetIndexArray()[0]));
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
				return ret;
			}
		}
	}
}

NSDevilX::NSResourceSystem::CFBXRenderProcesser::CFBXRenderProcesser(CFBXProcesser * processer)
	:mFBXProcesser(processer)
{
}

NSDevilX::NSResourceSystem::CFBXRenderProcesser::~CFBXRenderProcesser()
{
}

Boolean NSDevilX::NSResourceSystem::CFBXRenderProcesser::_loadImpMT()
{
	auto & meshes=mFBXProcesser->getCommonProcesser()->getMeshes();
	TVector<SMeshInfo> mesh_infos;
	for(auto mesh:meshes)
	{
		auto material=mesh->GetNode()->GetMaterial(mesh->GetElementMaterial()->GetIndexArray()[0]);
		SMeshInfo mesh_info;
		TVector<TVector<Int32> > polygon_keys_by_control_point_index=NSInternal::processPolygonKeys(mesh);
		TVector<SVertex> vertices;
		auto num_vertices=mesh->GetPolygonCount()*3;
		vertices.resize(num_vertices);
		NSInternal::processPositions(mesh,vertices);
		NSInternal::processNormals(mesh,polygon_keys_by_control_point_index,vertices);
		NSInternal::processTangents(mesh,polygon_keys_by_control_point_index,vertices);
		NSInternal::processUV0s(mesh,polygon_keys_by_control_point_index,vertices);
		NSInternal::processSkin(mesh,polygon_keys_by_control_point_index,vertices);
		mesh_info.mMaterial=NSInternal::processMaterial(mesh);

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
			TVector<UInt32> indices;
			indices.resize(vertices.size());
			for(SizeT vertex_index=0;vertex_index<new_vertices.size();++vertex_index)
			{
				for(auto index_position:index_positions[vertex_index])
				{
					indices[index_position]=static_cast<UInt32>(vertex_index);
				}
			}
			mesh_info.mIndices=indices;
			mesh_info.mVertices=new_vertices;
		}
		mesh_infos.push_back(mesh_info);
	}
	mMeshes=mesh_infos;
	return true;
}
