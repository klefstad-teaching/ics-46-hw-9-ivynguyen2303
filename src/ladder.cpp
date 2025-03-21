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
        return true;

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

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();

    if (abs(len1 - len2) > d) return false;

    vector<int> prev(len2 + 1), curr(len2 + 1);

    for (int j = 0; j <= len2; ++j)
        prev[j] = j;

    for (int i = 1; i <= len1; ++i) {
        curr[0] = i;
        for (int j = 1; j <= len2; ++j) {
            if (str1[i - 1] == str2[j - 1])
                curr[j] = prev[j - 1];
            else
                curr[j] = 1 + min({prev[j], curr[j - 1], prev[j - 1]});
        }
        swap(prev, curr);
    }

    return prev[len2] <= d;
}


void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        error("", "", "cannot open file!");
    }

    string word;
    while (file >> word) {
        // normalize to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }

    file.close();
}


void print_word_ladder(const vector<string>& ladder)
{
    if (ladder.size() == 0)
    {
        cout << "No word ladder found.\n";
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i)
        cout << ladder[i] << " ";
    cout << endl;
}


void error(string word1, string word2, string msg)
{
    cerr << "Error: " << msg <<  ". ( " << word1 << ", " << word2 << " )" << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}