#include "RecordTable.h"
#include "Record.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Settings.h"

using namespace SnakeGame;

std::vector<Models::Record> Models::RecordTable::_top = {};

const std::vector<Models::Record> SnakeGame::Models::RecordTable::GetTop()
{
    return _top;
}

const int SnakeGame::Models::RecordTable::getScore(std::string name)
{
    Load(SnakeGame::FILE_RECORD_TOP);
    for (auto it = RecordTable::_top.begin(); it != RecordTable::_top.end(); ++it)
    {
        if (it->Name == name) {
            return it->score;
        }
    }
    return 0;
}

void SnakeGame::Models::RecordTable::Add(Record adddValue)
{
    RecordTable::_top.push_back(adddValue);
    std::sort(RecordTable::_top.begin(), RecordTable::_top.end());
    if (RecordTable::_top.size() > 10)
        RecordTable::_top.resize(10);
    Save(SnakeGame::FILE_RECORD_TOP);
}

void SnakeGame::Models::RecordTable::Load()
{
    Load(SnakeGame::FILE_RECORD_TOP);
}

void SnakeGame::Models::RecordTable::Load(std::string file)
{
    std::ifstream ifs(file, std::ios::binary);

    if (!ifs.is_open())
    {
        _top.clear();
        return;
    }

    _top.clear();

    size_t size;
    ifs.read((char*)&size, sizeof(size));

    for (size_t i = 0; i < size; i++)
    {
        Record r;

        size_t len;
        ifs.read((char*)&len, sizeof(len));

        r.Name.resize(len);
        ifs.read(&r.Name[0], len);

        ifs.read((char*)&r.score, sizeof(r.score));

        _top.push_back(r);
    }
}

void SnakeGame::Models::RecordTable::Save(std::string file)
{
    std::ofstream ofs(file, std::ios::binary);

    size_t size = _top.size();
    ofs.write((char*)&size, sizeof(size));

    for (auto& r : _top)
    {
        size_t len = r.Name.size();
        ofs.write((char*)&len, sizeof(len));
        ofs.write(r.Name.c_str(), len);

        ofs.write((char*)&r.score, sizeof(r.score));
    }
}
