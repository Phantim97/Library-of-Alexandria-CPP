#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace boost;

struct Journal
{
  std::string title;
  std::vector<std::string> entries;

  Journal(const std::string &title) : title(title) {}

  void add_entry(const std::string &entry)
  {
    static int count = 1;
    entries.push_back(lexical_cast<std::string>(count++) + ": " + entry);
  }

  //Although we would do this here it is not recommended (outside scope of journal's functionality)
  /*void save (const std::string &filename)
    {
       std::ofstream ofs(filename)
       for (std::vector<std::string>::iterator it = entries.begin(); it != entries.end(); it++)
       {
       ofs << *it << std::endl;
       }
    }
   */
};

struct PersistenceManager
{
  //all persistence code (saving) in a single place
  static void save(const Journal& J,const std::string& filename)
  {
    std::ofstream ofs(filename);
    for (std::vector<std::string>::const_iterator it = J.entries.begin(); it != J.entries.end(); it++)
      {
	ofs << *it << '\n';
      }
  }
};

int main()
{
  Journal journal {"Log"};
  journal.add_entry("Screamed into the void");
  journal.add_entry("Help me");

  PersistenceManager pm;
  pm.save(journal, "log.txt");
  
  getchar();
  
  return 0;
}
