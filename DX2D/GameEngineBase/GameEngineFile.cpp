#include "PreCompile.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"

GameEngineFile::GameEngineFile() 
	: FilePtr(nullptr)
{
}

GameEngineFile::GameEngineFile(const char* _Path)
	: FilePtr(nullptr)
{
	Path_ = _Path;
}

GameEngineFile::GameEngineFile(const std::filesystem::path& _Path)
	: FilePtr(nullptr)
{
	Path_ = _Path;
}

GameEngineFile::GameEngineFile(const GameEngineFile& _Other)
	: FilePtr(nullptr)
{
	Path_ = _Other.Path_;
}

GameEngineFile::~GameEngineFile() 
{
	GameEngineFile::Close();
}

uintmax_t GameEngineFile::GetFileSize(const std::filesystem::path& _Path)
{
	return std::filesystem::file_size(_Path);
}

void GameEngineFile::Open(OpenMode _OpenMode, FileMode _FileMode)
{
	std::string OpenMode = "";
	switch (_OpenMode)
	{
	case OpenMode::Read:
		OpenMode += "r";
		break;
	case OpenMode::Write:
		OpenMode += "w";
		break;
	default:
		break;
	}

	switch (_FileMode)
	{
	case FileMode::Text:
		OpenMode += "t";
		break;
	case FileMode::Binary:
		OpenMode += "b";
		break;
	default:
		break;
	}

	fopen_s(&FilePtr, Path_.string().c_str(), OpenMode.c_str());

	if (nullptr == FilePtr)
	{
		MsgBoxAssert("파일이 정상적으로 열리지 않았습니다.");
	}
}

void GameEngineFile::Close()
{
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
		FilePtr = nullptr;
	}
}

void GameEngineFile::Write(void* _WriteData, size_t _DataSize)
{
	fwrite(_WriteData, _DataSize, 1, FilePtr);
}

void GameEngineFile::Read(void* _Buffer, size_t _BufferSize, size_t _ReadSize)
{
	fread_s(_Buffer, _BufferSize, _ReadSize, 1, FilePtr);
}

std::string GameEngineFile::GetString()
{
	std::string AllString;
	uintmax_t Size = GetFileSize();

	AllString.resize(Size);

	Read(&AllString[0], Size, Size);

	return AllString;
}

uintmax_t GameEngineFile::GetFileSize() const
{
	return GetFileSize(Path_);
}

