#include <string>
#include <iostream>
#include <filesystem>

//Finds .mp3 file in current directory and converts it to a .wav
//Requires ffmpeg.exe
namespace fs = std::filesystem;

int main()
{
    std::string path = std::filesystem::current_path().string();
    std::vector<std::string> files;
    std::string temp = "";

    for (const auto& entry : fs::directory_iterator(path))
    {
        std::string comp = entry.path().string();
        if (strstr(comp.c_str(), ".mp3")) //change here to set base conversion
        {
            std::cout << entry.path() << std::endl;
            temp = entry.path().string();
            temp.erase(temp.length() - 4, temp.length());

            files.push_back(temp);
        }
    }

    std::string p1 = "\"PATH_TO\\ffmpeg.exe\" -i ";
    //input 
    std::string p2 = ".mp3 -acodec pcm_s16le -ac 1 -ar 44100 ";
    //output
    //std::string p2 = ".wav -f s16le -acodec pcm_s16le "; //for wav to raw
    std::string cmd = "";

    for (int i = 0; i < files.size(); i++)
    {
        std::cout << files[i] << '\n';
    }

    for (int i = 0; i < files.size(); i++)
    {
        cmd = p1;
        cmd += files[i].c_str();
        cmd += p2;
        cmd += files[i].c_str();
        cmd += ".wav"; //change if using a diff conversion

        system(cmd.c_str());
    }

    return 0;
}
