#include "BasicHashMap.h"

int main()
{
    HashMap<int, std::string, MyKeyHash> hmap;
	
    hmap.put(1, "val1");
    hmap.put(2, "val2");
    hmap.put(3, "val3");

    std::string value;
    hmap.get(2, value);
	
    std::cout << value << '\n';
	
    bool res = hmap.get(3, value);
	
    if (res)
    {
        std::cout << value << '\n';
    }
	
    hmap.remove(3);
    res = hmap.get(3, value);
	
    if (res) 
    {
        std::cout << value << '\n';
    }
  
    return 0;
}
