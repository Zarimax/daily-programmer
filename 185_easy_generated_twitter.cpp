/* https://www.reddit.com/r/dailyprogrammer/comments/2jt4cx/10202014_challenge_185_easy_generated_twitter/ */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// define a scorecard class which will keep track of the shortest or longest strings
class scorecard
{
private:
    bool bHighestWins_;                         // true = longest strings win. false = shortest strings win
    unsigned int iMaxSlots_, iFreeSlots_;       // track the max number of strings in contention
    vector<string> vTopScores_;                 // store all the winning strings

public:
    scorecard(const bool bHighestWins, const unsigned int iMaxSlots) :
        bHighestWins_(bHighestWins),
        iMaxSlots_(iMaxSlots)
    {
        iFreeSlots_ = iMaxSlots_;
    }

    void score(string word)
    {
        if (iFreeSlots_ > 0)                    // if there are still free slots, every string is a winner
        {
            vTopScores_.push_back(word);
            iFreeSlots_--;
        }
        else
        {
            for (auto &x : vTopScores_)
            {
                if ((bHighestWins_ && x.length() < word.length()) ||
                    (!bHighestWins_ && x.length() > word.length()))
                {
                    x = word;                   // the first loser found gets bumped
                    return;                     // return here or else multiple slots could be written by this word
                }
            }
        }
    }

    void print()
    {
        for each (string x in vTopScores_)
        {
            cout << x << endl;
        }
    }
};

int main(int argc, char * argv[])
{
    ifstream infile("enable1.txt");             // warning: no error checking
    string word, orig, input_str = "at", output_str = "@";
    scorecard longest(true, 10);                // longest strings win. max 10 winners
    scorecard shortest(false, 10);              // shortest strings win. max 10 winners
    bool bBonus = false;                        // bonus mode. true = multi match, false = first match

    while (infile >> word)
    {
        int iReplaced = 0;
        size_t found = -1;                      // -1 here makes the found + 1 work
        orig = word;                            // need to save the original word for concat to the final word
        while ((found = word.find(input_str, found + 1)) != string::npos)
        {
            if (bBonus || found == 0)           // when !bBonus, only input_str in the first position should be matched
            {
                iReplaced++;
                word.replace(found, input_str.length(), output_str);
                if (!bBonus)                    // when bBonus, multiple input_str in word can be matched and replaced 
                    break;
            }
        }

        if (iReplaced > 0)
        {
            longest.score(word + " : " + orig);
            shortest.score(word + " : " + orig);
        }
    }

    longest.print();
    shortest.print();

    system("pause");  // warning: not portable off Windows
    return 0;
}