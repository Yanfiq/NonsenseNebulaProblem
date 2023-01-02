#include <fstream>
#include <winsock.h>
#include <sstream>
#include <string>
//using namespace std;

int valueinarray(int val, int arr[])
{
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}

void deleteValInArray(int val, int arr[])
{
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (arr[i] == val)
            arr[i] = -1;
    }
}

/*
string toString(int integer)
{
    char numstr[10]; // enough to hold all numbers up to 32-bits
    sprintf(numstr, "%i", integer);
    return numstr;
}
*/

/*
float getPngSize(char** dir)
{
    std::ifstream in(dir[1]);
    unsigned int width, height;
    in.seekg(16);
    in.read((char*)&width, 4);
    in.read((char*)&height, 4);
    return ntohl(width), ntohl(height);
}
*/
;
