#pragma once
#include "CommonResourceContainer.h"
namespace NSDevilX
{
	template<class RangeT>
	class TTreeNode
	{
	public:
		struct SData
			:public TBaseObject<SData>
		{
			const RangeT mRange;
			TResourcePtrVector<TTreeNode<RangeT> > * mChildren;
			SData(const RangeT & range)
				:mRange(range)
				,mChildren(nullptr)
			{}
			~SData()
			{
				DEVILX_DELETE(mChildren);
			}
		};
	protected:
		TTreeNode * mParent;
		VoidPtr mData;
	public:
		TTreeNode(const RangeT & range,TTreeNode<RangeT> * parent=nullptr)
			:mData(nullptr)
			,mParent(parent)
		{
			mData=DEVILX_NEW SData(range);
		}
		virtual ~TTreeNode()
		{
			DEVILX_DELETE(static_cast<SData*>(mData));
			if(static_cast<SData*>(mData)->mChildren)
			{
				for(auto node:*static_cast<SData*>(mData)->mChildren)
				{
					DEVILX_DELETE(node);
				}
			}
		}
		TTreeNode<RangeT> * getParent()const
		{
			return mParent;
		}
		SData * get()const
		{
			return static_cast<SData*>(mData);
		}
		Void addChild(TTreeNode<RangeT> * node)
		{
			static_cast<SData*>(mData)->mChildren.push_back()
		}
		virtual TTreeNode<RangeT> * createOrRetrieve(const CInt3 & position)
		{
			TTreeNode<RangeT> * ret=nullptr;
			if(static_cast<SData*>(mData)->mRange.contains(position))
			{
				if(!static_cast<SData*>(mData)->mChildren)
				{
					static_cast<SData*>(mData)->mChildren=DEVILX_NEW TResourcePtrVector<TTreeNode<RangeT> >;
					fillChildrenData();
				}
				for(auto child:*static_cast<SData*>(mData)->mChildren)
				{
					ret=child->createOrRetrieve(position);
					if(ret)
						break;
				}
				assert(ret);
			}
			return ret;
		}
		virtual TTreeNode<RangeT> * retrieve(const CInt3 & position)const
		{
			TTreeNode<RangeT> * ret=nullptr;
			if(static_cast<SData*>(mData)->mRange.contains(position))
			{
				for(auto child:*static_cast<SData*>(mData)->mChildren)
				{
					ret=child->retrieve(position);
					if(ret)
						break;
				}
				assert(ret);
			}
			return ret;
		}
		virtual Boolean remove(const CInt3 & position)
		{
			if(static_cast<SData*>(mData)->mRange.contains(position))
			{
				for(auto child:*static_cast<SData*>(mData)->mChildren)
				{
					if(child->remove(position))
					{
						Boolean all_invalidate=true;
						for(auto child2:*static_cast<SData*>(mData)->mChildren)
						{
							all_invalidate&=!child2->_isValidate();
						}
						if(all_invalidate)
						{
							DEVILX_DELETE(static_cast<SData*>(mData)->mChildren);
							static_cast<SData*>(mData)->mChildren=nullptr;
						}
						break;
					}
				}
				return true;
			}
			else
				return false;
		}
		virtual Void fillChildrenData()=0;
		virtual Boolean isLeaf()const
		{
			return false;
		}
	protected:
		virtual Boolean _isValidate()const
		{
			return nullptr!=static_cast<SData*>(mData)->mChildren;
		}
	};
	class C3DTreeNode
		:public TTreeNode<CRange3I>
	{
	public:
		C3DTreeNode(const CRange3I & range);
		~C3DTreeNode();
		virtual Void fillChildrenData() override;
	};

	class CBaseTreeLeaf
	{
	public:
		CBaseTreeLeaf(){}
		virtual ~CBaseTreeLeaf(){}
	};
	template<class RangeT,typename PositionT>
	class TTreeLeaf
		:public TTreeNode<RangeT>
		,public CBaseTreeLeaf
	{
	public:
		struct SData
			:public TBaseObject<SData>
		{
			PositionT mPosition;
			VoidPtr mData;
			SData(const PositionT & position)
				:mPosition(position)
				,mData(nullptr)
			{}
		};
	protected:
	public:
		TTreeLeaf(const PositionT & position)
			:TTreeNode<RangeT>(RangeT(0,0))
		{
			DEVILX_DELETE(static_cast<TTreeNode<RangeT>::SData*>(mData));
			mData=DEVILX_NEW SData(position);
		}
		virtual ~TTreeLeaf()
		{
			DEVILX_DELETE(static_cast<SData*>(mData));
			mData=nullptr;
		}
		SData * get()const
		{
			return static_cast<SData*>(mData);
		}
		virtual TTreeNode<RangeT> * createOrRetrieve(const CInt3 & position) override
		{
			if(static_cast<SData*>(mData)->mPosition==position)
				return this;
			else
				return nullptr;
		}
		virtual TTreeNode<RangeT> * retrieve(const CInt3 & position) const override
		{
			if(static_cast<SData*>(mData)->mPosition==position)
				return const_cast<TTreeLeaf<RangeT,PositionT>*>(this);
			else
				return nullptr;
		}
		virtual Boolean remove(const CInt3 & position) override
		{
			if(static_cast<SData*>(mData)->mPosition==position)
			{
				static_cast<SData*>(mData)->mData=nullptr;
				return true;
			}
			else
				return false;
		}
		virtual Void fillChildrenData() override
		{}
		virtual Boolean isLeaf() const override
		{
			return true;
		}
	protected:
		virtual Boolean _isValidate() const override
		{
			return static_cast<SData*>(mData)->mData!=nullptr;
		}
	};
	class C3DTreeLeaf
		:public TTreeLeaf<CRange3I,CInt3>
	{
	public:
		C3DTreeLeaf(const CInt3 & position);
		~C3DTreeLeaf();
	};
	template<class RangeT>
	class TTreeContainer
	{
	public:
		struct SIterator
		{
			static const SIterator sEnd=SIterator(nullptr);
			TTreeNode<RangeT> * mLeaf;
			TVector<UInt32> mChildrenIndexStack;
			SIterator(TTreeNode<RangeT> * leaf)
				:mLeaf(node)
			{}
			SIterator & operator ++()
			{
				auto node=mLeaf;
				while(node)
				{
					node=node->getParent();
					auto next_child_index=mChildrenIndexStack.back()+1;
					mChildrenIndexStack.pop_back();
					if(node->getChild(next_child_index))
					{
						node=node->getChild(next_child_index);
						mChildrenIndexStack.push_back(next_child_index);
						break;
					}
				}
				while(node&&(!node->isLeaf()))
				{
					node=node->getChild(0);
					mChildrenIndexStack.push_back(0);
				}
				mLeaf=node;
			}
			SIterator operator ++(Int32)
			{
				SIterator ret=*this;
				++(*this);
				return ret;
			}
			Boolean operator==(const SIterator & test)const
			{
				return mLeaf==test.mLeaf;
			}
			Boolean operator!=(const SIterator & test)const
			{
				return mLeaf!=test.mLeaf;
			}
			VoidPtr operator *()const
			{
				return static_cast<CBaseTreeLeaf*>(mLeaf)->getValue();
			}
		};
		typedef SIterator iterator;
	protected:
		TTreeNode<RangeT> * mRoot;
	public:
		TTreeContainer():mRoot(nullptr){}
		virtual ~TTreeContainer()
		{
			DEVILX_DELETE(mRoot);
		}
		iterator begin()
		{
			iterator ret(nullptr);
			TTreeNode<RangeT> * node=mRoot;
			while(node&&(!node->isLeaf()))
			{
				node=node->getChild(0);
				ret.mChildrenIndexStack.push_back(0);
			}
			ret.mLeaf=node;
			return ret;
		}
		const iterator & end()const
		{
			return SIterator::sEnd;
		}
		template<typename T>
		Void destroy()
		{
			if(mRoot)
			{
				for(auto value:*this)
				{
					DEVILX_DELETE(static_cast<T*>(value));
				}
			}
			DEVILX_DELETE(this);
		}
	};

	class C3DTreeContainer
		:public TTreeContainer<CRange3I>
	{
	public:
		C3DTreeContainer(){}
		~C3DTreeContainer(){}
		ConstVoidPtr operator[](const CInt3 & position)const
		{
			assert(mRoot);
			auto node=mRoot->retrieve(position);
			assert(node);
			return static_cast<C3DTreeLeaf*>(node)->get()->mData;
		}
		VoidPtr & operator[](const CInt3 & position)
		{
			if(!mRoot)
			{
				mRoot=DEVILX_NEW C3DTreeNode(CRange3I(position/2*2,position/2*2+1));
			}
			TTreeNode<CRange3I> * node=nullptr;
			while(!(node=mRoot->createOrRetrieve(position)))
			{
				auto new_root=DEVILX_NEW C3DTreeNode(CRange3I(mRoot->get()->mRange.getMin()/2*2,mRoot->get()->mRange.getMin()/2*2+mRoot->get()->mRange.getMax()-mRoot->get()->mRange.getMin()+1));
				new_root->fillChildrenData();
				for(int i=0;i<8;++i)
				{
					auto & child=(*new_root->get()->mChildren)[i];
					if(child->get()->mRange.contains(mRoot->get()->mRange))
					{
						DEVILX_DELETE(child);
						child=mRoot;
						break;
					}
				}
				mRoot=new_root;
			}
			return static_cast<C3DTreeLeaf*>(node)->get()->mData;
		}
		Void remove(const CInt3 & position)
		{
			if(mRoot)
			{
				mRoot->remove(position);
			}
		}
	};
}