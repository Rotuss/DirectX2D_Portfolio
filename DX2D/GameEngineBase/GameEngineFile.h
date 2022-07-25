#pragma once
#include "GameEnginePath.h"

enum class OpenMode
{
	Read,
	Write,
};

enum class FileMode
{
	Binary,
	Text,
};

// Ό³Έν :
class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const char* _Path);
	GameEngineFile(const std::filesystem::path& _Path);
	GameEngineFile(const GameEngineFile& _Other);
	~GameEngineFile();

	// delete Function
	static uintmax_t GetFileSize(const std::filesystem::path& _Path);
	
	void Open(OpenMode _OpenMode, FileMode _FileMode);

	void Close();

	void Create()
	{
		Open(OpenMode::Write, FileMode::Binary);
		Close();
	}

	void Write(void* _WriteData, size_t _DataSize);
	void Read(void* _Buffer, size_t _BufferSize, size_t _ReadSize);

	std::string GetString();
	uintmax_t GetFileSize() const;

protected:

private:
	FILE* FilePtr;
};

