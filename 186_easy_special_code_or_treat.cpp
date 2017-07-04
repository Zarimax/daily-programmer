/* https://www.reddit.com/r/dailyprogrammer/comments/2kwfqr/10312014_challenge_186_special_code_or_treat/ */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <array>

using namespace std;

int main()
{
    ifstream infile("CandyBag.txt");
    string candy;
    int longest_name = 0;
    double candy_total = 0;

    // string = name, double[0] = count, double[1] = % of total
    map<string, array<double, 2>> candy_bag;

    while (getline(infile, candy))
    {
        if (candy.size() > longest_name)
            longest_name = candy.size();
        candy_total++;
        candy_bag[candy][0]++;
        candy_bag[candy][1] = (candy_bag[candy][0] / candy_total);
    }

    for (auto s : candy_bag)
    {
        cout << setw(longest_name) << s.first << " - " << s.second[0];
        cout << " pieces (" << s.second[1] * 100.0 << "%)" << endl;
    }

    system("pause"); // warning - Windows-only
    return 0;
}