#include "ladder.h"
#include <cmath>

#include <queue>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// if there's a one character addition
// ex. cutey && cute | cheat && chat
bool one_added_character_different(const string& larger, const string& smaller)
{
    // substring the different character out and seeing if its the same?

    int i = 0;
    for (; i < larger.length(); i++)
        if (larger[i] != smaller[i])
            break;
    string cop = larger;
    cop.replace(i, 1, "");
    // cout << cop;
    // cout << "hello";
    return cop == smaller;

}

bool one_transpose_different(const string& word1, const string& word2)
{
    size_t diffCount = 0;

    for (int i = 0; i < word1.length(); ++i)
    {
        if (word1[i] != word2[i])
            ++diffCount;
    }
    return diffCount == 1;
}

bool is_adjacent(const string& word1, const string& word2)
{
    // checking if w1 and w2 are neighbors.
    if (word1 == word2)
        return false;

    int w1_len = word1.length();
    int w2_len = word2.length();

    if (w1_len == w2_len) //|| w1_len - w2_len == abs(1)
    {
        return one_transpose_different(word1, word2);
    }
    else if (w1_len - w2_len == 1) {
        return one_added_character_different(word1, word2);
    }
    else if (w1_len - w2_len == -1) {
        return one_added_character_different(word2, word1);
    }
    return false;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if (begin_word == end_word) // making sure that begin is different from end
        error(begin_word, end_word, "begin and end equal");


    std::queue<std::vector<std::string>> ladder_queue;  // creating a queue of strings "ladder_queue"   * what exactly is ladder_queue?
    ladder_queue.push(vector<string>{begin_word});      // push [begin_word] into the ladder queue
    set<string> visited;                                // create set visited
    visited.insert(begin_word);                         // mark begin_word to visited

    while (!ladder_queue.empty())                   // while the ladder_queue
    {
        auto ladder = ladder_queue.front();             // get front of queue = ladder
        ladder_queue.pop();                             // pop the front of queue
        string last_word = ladder[ladder.size() - 1];   // gets the last word in ladder     * why?
        for (string word : word_list)                   // for every word in word list
        {
            if (is_adjacent(last_word, word))           // check if the word is adjacent to the last word in ladder     * why?
            {
                if (visited.find(word) == visited.end())    // if word has not been visited
                {
                    visited.insert(word);           // mark word as visited
                    auto new_ladder = ladder;       // copy ladder to new_ladder
                    new_ladder.push_back(word);     // push the word onto new_ladder    * why?
                    if (word == end_word)           // if word == end word
                        return new_ladder;          // return the new_ladder
                    ladder_queue.push(new_ladder);  // push new_ladder onto ladder_queue
                }
            }
        }
    }
    // return no ladder found :,(
    return vector<string>();
}

void error(string word1, string word2, string msg)
{
    cerr << "Error: " << msg <<  ". ( " << word1 << ", " << word2 << " )" << endl;
}