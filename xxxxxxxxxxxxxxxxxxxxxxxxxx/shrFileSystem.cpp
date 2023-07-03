#include "shrFileSystem.h"
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

namespace shr
{
	Buffer FileSystem::ReadFileBinary(const std::filesystem::path& filepath)
	{
		std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

		if (!stream)
		{
			// Failed to open the file
			return {};
		}


		std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		uint64_t size = end - stream.tellg();

		if (size == 0)
		{
			// File is empty
			return {};
		}

		Buffer buffer(size);
		stream.read(buffer.As<char>(), size);
		stream.close();
		return buffer;
	}

	//static MonoAssembly* LoadMonoAssembly(const std::filesystem::path& assemblyPath, bool loadPDB = false)
	//{
	//	ScopedBuffer fileData = FileSystem::ReadFileBinary(assemblyPath);

	//	// NOTE: We can't use this image for anything other than loading the assembly because this image doesn't have a reference to the assembly
	//	MonoImageOpenStatus status;
	//	MonoImage* image = mono_image_open_from_data_full(fileData.As<char>(), fileData.Size(), 1, &status, 0);

	//	if (status != MONO_IMAGE_OK)
	//	{
	//		const char* errorMessage = mono_image_strerror(status);
	//		// Log some error message using the errorMessage data
	//		return nullptr;
	//	}

	//	if (loadPDB)
	//	{
	//		std::filesystem::path pdbPath = assemblyPath;
	//		pdbPath.replace_extension(".pdb");
	//		 
	//		if (std::filesystem::exists(pdbPath))
	//		{
	//			ScopedBuffer pdbFileData = FileSystem::ReadFileBinary(pdbPath);
	//			mono_debug_open_image_from_memory(image, pdbFileData.As<const mono_byte>(), pdbFileData.Size());
	//			//HZ_CORE_INFO("Loaded PDB {}", pdbPath);
	//		}
	//	}

	//	std::string pathString = assemblyPath.string();
	//	MonoAssembly* assembly = mono_assembly_load_from_full(image, pathString.c_str(), &status, 0);
	//	mono_image_close(image);

	//	return assembly;
	//}
}