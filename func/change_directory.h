#pragma once
#include <windows.h>

namespace cd
{
    void change_common_directory()
    {
        std::string path, new_path = "";
        TCHAR buffer[MAX_PATH];
        GetCurrentDirectory(sizeof(buffer), buffer);
        CharToOemA(buffer, buffer);
        path = buffer;
        int k;
        if (path[path.size() - 1] == 'g')
        {
            k = 19;
        }
        else
        {
            k = 20;
        }
        for (int i = 0; i < static_cast<int>(path.size()) - k; i++)
        {
            new_path = new_path + path[i];
        }
        char new_path_char[256];
        strcpy_s(new_path_char, sizeof(new_path_char), new_path.c_str());
        SetCurrentDirectory(new_path_char);
    }
}
