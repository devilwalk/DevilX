#pragma once
namespace NSDevilX
{
	class CDirectory
		:public TMemoryAllocatorObject<CDirectory>
	{
	protected:
		const String mName;
		CDirectory * const mParent;
	public:
		static String cleanPath(const String & path);
		static String getCurrentDirectory();
		static String getApplicationDirectory();
		static String getSystemFontsDirectory();
		static String getAbsolutePath(const String & path,String currentPath="");
		static Void create(const String & fullName);
		static String getDirectoryName(const String & name);
		static String getExtensionName(const String & name);
		CDirectory(const String & name,CDirectory * parent=nullptr)
			:mName(name)
			,mParent(parent)
		{}
		~CDirectory(){}
		CDirectory * getParent()const
		{
			return mParent;
		}
		const String & getName()const
		{
			return mName;
		}
		//like:test/test/test
		String getDerivedName()const
		{
			String ret;
			if(mParent)
			{
				ret+=mParent->getDerivedName();
				ret+="/"+getName();
			}
			else
			{
				ret=getName();
			}
			return ret;
		}
		//like:c:/test/test/test
		String getFullName()const
		{
			return getAbsolutePath(getDerivedName());
		}
		Boolean hasFile(const String & name)const
		{
			auto full_name=getFullName()+"/"+name;
			std::ifstream file_stream(full_name.c_str());
			return file_stream.is_open();
		}
		Boolean hasDirectory(const String & name)const;
		Void create();
		Void getChildFiles(TVector<String> & files)const;
	};
}