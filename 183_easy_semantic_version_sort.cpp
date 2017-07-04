/* https://www.reddit.com/r/dailyprogrammer/comments/2igfj9/10062014_challenge_183_easy_semantic_version_sort/ */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

bool semantic_compare(string x, string y)
{
    regex rgx("^(\\w+)\\.(\\w+)\\.(\\w+)(-\\w+)?(\\+\\w+)?");
    smatch match_x, match_y;

    regex_search(x, match_x, rgx);
    regex_search(y, match_y, rgx);

    for (int i = 1; i < match_x.size() && i < match_y.size(); ++i)
    {
        string str_x(match_x[i]);
        string str_y(match_y[i]);

        if (str_x == "-alpha" || str_x == "-prerelease")
            return true;

        if (atoi(str_x.c_str()) != atoi(str_y.c_str()))
            return atoi(str_x.c_str()) < atoi(str_y.c_str());
    }

    return false; // string x was shorter than string y
}

int main(int argc, char * argv[])
{
    string line;
    vector<string> input;
    ifstream infile("test_data.txt");

    getline(infile, line);          // throw away first line
    while (getline(infile, line))   // read each line in the file
        input.push_back(line);      // store each line into an array

    sort(input.begin(), input.end(), semantic_compare);

    for each (auto x in input)
        cout << x << endl;

    system("pause"); // warning: not portable off Windows
    return 0;
}