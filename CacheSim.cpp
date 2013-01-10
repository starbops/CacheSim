#include <iostream>
#include <list>
using namespace std;

void PrintTag(unsigned int, unsigned int);

int main(void) {
    unsigned int x = 0, y = 0, z = 0, replaceAlgo = 0, m = 0, memAddr = 0;
    unsigned int cacheSize = 1, blockSize = 1, blockNum = 0, way = 1, setNum = 0, setNumLog = 0, tagLength = 0;
    list<unsigned int> * setQueue = NULL;

    cin >> x >> y >> z >> replaceAlgo >> m;

    for(unsigned int i = x; i > 0; i--)
        cacheSize <<= 1;
    for(unsigned int i = y; i > 0; i--)
        blockSize <<= 1;
    for(unsigned int i = z; i > 0; i--)
        way <<= 1;
    blockNum = cacheSize / blockSize;
    setNum = blockNum / way;
    for(unsigned int i = setNum; i != 1; setNumLog++)
        i>>=1;
    tagLength = 20 - y - setNumLog;
    setQueue = new list<unsigned int> [setNum];

    cout << blockNum << endl;
    cout << setNum << endl;
    cout << tagLength << endl;

    for(unsigned int i = 0; i < m; i++) {
        unsigned int mask = (setNum - 1) << y;
        unsigned int index = 0, tag = 0;
        list<unsigned int>::iterator it;

        cin >> hex >> memAddr;

        index = (memAddr & mask) >> y;
        tag = (memAddr & (~mask)) >> y >> setNumLog;
        for(it = setQueue[index].begin(); it!=setQueue[index].end(); it++)
            if(tag == *it) break;
        if((it == setQueue[index].end()) && (*it != tag)) {
            cout << "miss" << endl;
            if(setQueue[index].size() < way) {
                PrintTag(0, tagLength);
                cout << "->";
                PrintTag(tag, tagLength);
                cout << endl << "0->1" << endl;
            } else {
                PrintTag(setQueue[index].back(), tagLength);
                cout << "->";
                PrintTag(tag, tagLength);
                cout << endl;
                cout << "1->1" << endl;

                setQueue[index].pop_back();
            }
            setQueue[index].push_front(tag);
        } else {
            cout << "hit" << endl;
            PrintTag(*it, tagLength);
            cout << "->";
            PrintTag(tag, tagLength);
            cout << endl << "1->1" << endl;

            if(replaceAlgo == 1) {
                setQueue[index].erase(it);
                setQueue[index].push_front(tag);
            }
        }
    }

    delete [] setQueue;

    return 0;
}

void PrintTag(unsigned int value, unsigned int width) {
    unsigned int mask = 1 << (width - 1);
    while(mask > 0) {
        if((value & mask) == 0)
            cout << "0";
        else
            cout << "1";
        mask >>= 1;
    }

    return ;
}
