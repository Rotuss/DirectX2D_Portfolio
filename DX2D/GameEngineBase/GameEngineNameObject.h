#pragma once
#include <string>

// Ό³Έν :
class GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineNameObject();
	virtual ~GameEngineNameObject();

	inline void SetName(const std::string& _Name)
	{
		Name_ = _Name;
	}

	std::string GetNameCopy() const
	{
		return Name_;
	}

	const std::string& GetNameConstRef()
	{
		return Name_;
	}

	const char* GetNameConstPtr()
	{
		return Name_.c_str();
	}

protected:

private:
	std::string Name_;
};

