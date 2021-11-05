#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

std::string command_output_get(std::string cmd)
{
  std::string data;
  FILE* cmd_output;
  const int max_buff = 256;
  char buff[max_buff];
  cmd.append(" 2>&1");

  cmd_output = popen(cmd.c_str(), "r");

  if (cmd_output)
    {
      while (!feof(cmd_output))
	{
	  if (fgets(buff, max_buff, cmd_output) != NULL)
	    {
	      data.append(buff);
	    }
	}
      pclose(cmd_output);
    }

  return data;
}

int main()
{
  std::string cmd = "ls";
  std::cout << command_output_get(cmd) << '\n';
  return 0;
}
