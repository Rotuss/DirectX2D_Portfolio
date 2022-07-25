#include "PreCompile.h"
#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineFile.h"
#include "GameEngineString.h"

GameEngineDirectory::GameEngineDirectory() 
{
    SetCurrentPath();
}

GameEngineDirectory::GameEngineDirectory(const char* _Path)
{
    Path_ = _Path;
    if (false == IsExists())
    {
        MsgBoxAssert("�������� �ʴ� ������ ���͸��� �ʱ�ȭ�Ϸ��� �߽��ϴ�.");
    }
}

GameEngineDirectory::GameEngineDirectory(const std::filesystem::path& _Path)
{
    Path_ = _Path;
    if (false == IsExists())
    {
        MsgBoxAssert("�������� �ʴ� ������ ���͸��� �ʱ�ȭ�Ϸ��� �߽��ϴ�.");
    }
}

GameEngineDirectory::GameEngineDirectory(const GameEngineDirectory& _Other)
{
    Path_ = _Other.Path_;
    if (false == IsExists())
    {
        MsgBoxAssert("�������� �ʴ� ������ ���͸��� �ʱ�ȭ�Ϸ��� �߽��ϴ�.");
    }
}

GameEngineDirectory::~GameEngineDirectory() 
{
}

void GameEngineDirectory::MoveParent()
{
    Path_ = Path_.parent_path();
}

void GameEngineDirectory::MoveParent(const std::string& _Name)
{
    while (false == IsRoot())
    {
        Path_ = Path_.parent_path();

        if (GetFileName() == _Name)
        {
            break;
        }
    }
}

bool GameEngineDirectory::MoveParentToExitsChildDirectory(const std::string& _Name)
{
    std::string FindDirectory = _Name;
    GameEngineString::ToUpper(FindDirectory);

    std::vector<GameEngineFile> Return;

    while (true)
    {
        std::filesystem::directory_iterator DirIter(Path_);

        for (const std::filesystem::directory_entry& Entry : DirIter)
        {
            if (true == Entry.is_directory())
            {
                std::string CurrentFileName = Entry.path().filename().string();
                GameEngineString::ToUpper(CurrentFileName);

                if (CurrentFileName == FindDirectory)
                {
                    return true;
                }
            }
        }

        if (true == IsRoot())
        {
            return false;
        }

        MoveParent();
    }

    return false;
}

bool GameEngineDirectory::IsRoot()
{
    return Path_ == Path_.root_path();
}

void GameEngineDirectory::Move(const std::string& _Name)
{
    std::filesystem::path CheckPath = Path_;

    CheckPath.append(_Name);

    if (false == std::filesystem::exists(CheckPath))
    {
        MsgBoxAssertString(_Name + " ��ΰ� �������� �ʽ��ϴ�.");
        return;
    }

    Path_ = CheckPath;
}

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _Ext)
{
    std::filesystem::directory_iterator DirIter(Path_);

    std::string Ext = _Ext;

    if (Ext != "")
    {
        GameEngineString::ToUpper(Ext);
        if (std::string::npos == Ext.find("."))
        {
            Ext = "." + Ext;
        }
    }

    std::vector<GameEngineFile> Return;
    
    for (const std::filesystem::directory_entry& Entry : DirIter)
    {
        if (true == Entry.is_directory())
        {
            continue;
        }

        if (Ext != "")
        {
            GameEnginePath NewPath = Entry.path();
            std::string OtherExt = NewPath.GetExtension();
            GameEngineString::ToUpper(OtherExt);

            if (OtherExt != Ext)
            {
                continue;
            }
        }

        Return.push_back(GameEngineFile(Entry.path()));
    }

    return Return;
}

std::vector<GameEngineDirectory> GameEngineDirectory::GetAllDirectory()
{
    std::filesystem::directory_iterator DirIter(Path_);

    std::vector<GameEngineDirectory> Return;
    
    for (const std::filesystem::directory_entry& Entry : DirIter)
    {
        if (true == Entry.is_directory())
        {
            Return.push_back(GameEngineDirectory(Entry.path()));
            continue;
        }
    }

    return Return;
}

std::vector<GameEngineDirectory> GameEngineDirectory::GetRecursiveAllDirectory()
{
    std::vector<GameEngineDirectory> Return;

    std::filesystem::recursive_directory_iterator DirIter = std::filesystem::recursive_directory_iterator(Path_);

    for (const std::filesystem::directory_entry& Entry : DirIter)
    {
        if (true == Entry.is_directory())
        {
            Return.push_back(GameEngineDirectory(Entry.path()));
        }
    }

    return Return;
}