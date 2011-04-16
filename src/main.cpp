#include <iostream>
#include <fstream>
#include "list.h"
#include <sstream>

int main(void)
{
    try {
        
        std::cout << "simple sorted linked list:\n";
        LinkedList<int> ll;
        for (int i = 0; i < 10; i++) 
            ll.insert(i);
        ll.print();

        std::cout << "\n2 level linked list:\n";
        RootLinkedList<char, int> rll;
        rll.insert('A', 4);
        rll.insert('C');
        rll.insert('B', 2);
        rll.insert('A', 3);
        rll.remove('A', 3);
        rll.remove('C');
        rll.insert('D', 5);
        rll.print();
        rll.deleteall();

        std::cout << "\n3 level linked list:\n";
        MainLinkedList<char, int, double> mll;
        mll.insert('Z', 5, 3.14);
        mll.insert('F', 2, 2.71);
        mll.insert('H', 4, 1.43);
        mll.insert('A', 9, 1.73);
        mll.insert('F', 4, 2.0);
        mll.insert('F', 2, 2.23);
        mll.print();
        mll.remove('A', 9, 1.73);
        mll.remove('Z', 5);
        mll.deleteall();

        std::cout << "\n3 level linked list from file:\n";
        std::ifstream idata("list.dat");
        if (!idata) throw "IO error";
        char c;
        int i;
        double d;
        while (!idata.eof()) {
            std::string line;
            std::getline(idata, line);
            if (line.empty()) continue;
            std::istringstream ss(line);

            ss >> c >> i >> d;
            mll.insert(c, i, d);
        }
        mll.print();
    }
    catch (ListException& e) {
        std::cout << e.what() << '\n';
    }
    catch (const char *e) {
        std::cout << e << '\n';
    }


    return 0;
}

