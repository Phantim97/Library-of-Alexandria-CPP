#include <windows.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <omp.h>

void add_rel_path_prefix(std::vector<std::string>& values)
{
  std::string path = std::filesystem::current_path().u8string();

  for (size_t i = 0; i < values.size(); i++)
  {
    values[i] = path + "\\" + values[i]; 
  }
}

static bool parallel_registry_create(std::vector<std::string>& variables, std::vector<std::string>& values)
{
	add_rel_path_prefix(values);
  
	HKEY hKey;
	LPCSTR keyPath = TEXT("System\\CurrentControlSet\\Control\\Session Manager\\Environment");
	LSTATUS lOpenStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyPath, 0, KEY_ALL_ACCESS, &hKey); //Open Environment Variable folder
	if (lOpenStatus == ERROR_SUCCESS)
	{
		omp_set_num_threads(5);
    
		#pragma omp parallel for shared(hKey)
		for (int i = 0; i < 5; i++)
		{
			RegSetValueEx(hKey, variables[i].c_str(), 0, REG_SZ, (LPBYTE)values[i].c_str(), values[i].size()); //Create the Environment Variable and value for each string in array
		}
		RegCloseKey(hKey);
	}

	return true;
}

static bool extendPathVariable(std::vector<std::string>& env_paths)
{
	HKEY hKey;
	DWORD dwType = REG_EXPAND_SZ; //Path is a REG_EXPAND_SZ type of registry as opposed to other system variables that are type "REG_SZ"
	DWORD value_length = 2056;
	LPCSTR keyPath = TEXT("System\\CurrentControlSet\\Control\\Session Manager\\Environment");
	LSTATUS lOpenStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyPath, 0, KEY_ALL_ACCESS, &hKey);
	if (lOpenStatus == ERROR_SUCCESS)
	{
		char value[2056]; //A large enough buffer to capture all the environment variables
		RegQueryValueEx(hKey, "Path", NULL, &dwType, (LPBYTE)& value, &value_length); //store the values from Path into value buffer
		RegCloseKey(hKey);

		std::string s;
		//store path variables and append the desired environment variables at the end
		s.append(value);
    //We add new values such as %GTEST_DIR\\x64\\vc16\\bin; and append with all of the desired values"
    for (size_t i = 0; i < env_paths.size(); i++)
    {
      s.append(env_paths[i]);
      s += ';';
    }
    
    //Path must end with this
    s += '\0';

		lOpenStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyPath, 0, KEY_ALL_ACCESS, &hKey); //Open Path again
		if (lOpenStatus == ERROR_SUCCESS)
		{
			LSTATUS lSetStatus = RegSetValueEx(hKey, "Path", 0, REG_EXPAND_SZ, (LPBYTE)s.c_str(), s.size()); //Update Path with new list of environment variables 

			RegCloseKey(hKey);

			if (lSetStatus == ERROR_SUCCESS)
			{
				std::cout << "Value set\n";
				SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)L"Environment", SMTO_BLOCK, 100, NULL); //Broadcast to the OS that the change was made
				return true;
			}
			else
			{
				std::cout << "Error setting environment variable\n";
				return false;
			}
		}
		else
		{
			std::cout << "Failed to open environment variable again\n";
			return false;
		}
	}
	else
	{
		return false;
	}
}
