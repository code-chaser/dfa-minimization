/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~
--||author : codechaser||-- 
~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// templates for easy input/output of complex data structures, directly using cin/cout;
// not related to DFA minimization;
template <typename... T>
void print(T... arg)
{
    ((cout << arg), ...);
}
template <typename T1, typename T2>
ostream &operator<<(ostream &cout, pair<T1, T2> p)
{
    cout << p.first << " " << p.second;
    return cout;
}
template <typename T>
ostream &operator<<(ostream &cout, vector<T> v)
{
    int cnt = 0;
    for (auto &i : v)
        cout << i << ((++cnt) != v.size() ? " " : "");
    return cout;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &cout, map<T1, T2> m)
{
    for (auto i : m)
        cout << i << "\n";
    cout << "\n";
    return cout;
}
template <typename... T>
void input(T &...arg)
{
    ((cin >> arg), ...);
}
template <typename T1, typename T2>
istream &operator>>(istream &cin, pair<T1, T2> &p)
{
    cin >> p.first >> p.second;
    return cin;
}
template <typename T>
istream &operator>>(istream &cin, vector<T> &v)
{
    for (auto &i : v)
        cin >> i;
    return cin;
}
// templates end here

int numberOfStates, alphabetSize, initialState, numberOfFinalStates;
map<int, bool> isReachable, isFinal;
map<int, map<char, int>> transitionTable;
vector<char> alphabet;
// transitionTable[i][j] is the state we reach on entering symbol 'j' on state 'i';

void reachable(int currentState, vector<char> alphabet = alphabet)
{
    isReachable[currentState] = 1;
    for (auto i : alphabet)
    {
        if ((transitionTable[currentState][i] != -1) && (transitionTable[currentState][i] != currentState) && (!isReachable[transitionTable[currentState][i]]))
            reachable(transitionTable[currentState][i], alphabet);
        isReachable[transitionTable[currentState][i]] = 1;
    }
    return;
}

int transition(int state, char symbol)
{
    return transitionTable[state][symbol];
}

bool equivalent(int state1, int state2)
{
    if (state1 == state2 || ((isFinal[state1]) && (isFinal[state2])))
        return 1;
    for (auto i : alphabet)
    {
        if (!equivalent(transitionTable[state1][i], transitionTable[state2][i]))
            return 0;
    }
    return 1;
}

int main()
{
    cout << "\nEnter the total number of states:\n";
    cin >> numberOfStates;
    vector<int> states(numberOfStates);
    for (int i = 0; i < numberOfStates; i++)
        states[i] = i + 1;

    cout << "\nEnter the size of Alphabet (i.e. number of valid input symbols):\n";
    cin >> alphabetSize;
    vector<char> temp(alphabetSize);
    cout << "\nEnter the valid input symbols:\n";
    cin >> temp;
    alphabet = temp;

    cout << "\nNow, building the transition table:\nEnter the following details:\n";
    getchar();
    for (int i = 0; i < numberOfStates; i++)
    {
        cout << "\nFor state " << i + 1 << " which state do we get to, on entering following symbols (leave empty for phi):\n";
        for (int j = 0; j < alphabetSize; j++)
        {
            cout << "\n"
                 << alphabet[j] << " : ";
            string temp;
            getline(cin, temp);
            if (temp.size())
                transitionTable[i + 1][alphabet[j]] = temp[0] - '0';
            else
                transitionTable[i + 1][alphabet[j]] = -1;
        }
    }
    cout << "\nTransition Table built successfully!\nMoving furhter!";

    cout << "\n\nEnter the index of the initial state:\n";
    cin >> initialState;

    cout << "\nEnter the total number of final states:\n";
    cin >> numberOfFinalStates;
    vector<int> finalStates(numberOfFinalStates);
    cout << "\nNow enter the " << ((numberOfFinalStates == 1) ? "index of the final state" : "indices of the final states") << ":\n";
    cin >> finalStates;
    for (auto i : finalStates)
        isFinal[i] = 1;

    cout << transitionTable;

    // marking reachable states;
    reachable(initialState, alphabet);
    vector<int> reachableStates, reachableFinalStates;
    for (auto i : isReachable)
    {
        if (i.second)
        {
            reachableStates.push_back(i.first);
            if (isFinal[i.first])
                reachableFinalStates.push_back(i.first);
        }
        else
            isFinal[i.first] = 0;
    }

    vector<vector<int>> table(reachableStates.size(), vector<int>(reachableStates.size(), -2));
    for (int i = 1; i < reachableStates.size(); i++)
        table[0][i] = i;
    for (int i = 1; i < reachableStates.size(); i++)
        table[i][0] = reachableStates.size() - i + 1;

    vector<vector<int>> partitions;
    partitions.pb(reachableFinalStates);

    vector<int> nonFinalStates;
    for (auto i : reachableStates)
        if (!isFinal[i])
            nonFinalStates.push_back(i);

    partitions.push_back(nonFinalStates);

    map<int, int> stateInPartition;

    while (1)
    {
        for (int i = 1; i <= partitions.size(); i++)
        {
            for (auto j : partitions[i - 1])
            {
                stateInPartition[j] = i;
            }
        }
        for (auto partition : partitions)
        {
            for (int i = 0; i < partition.size(); i++)
            {
                for (int j = i + 1; j < partition.size(); j++)
                {
                    for (auto symbol : alphabet)
                    {
                        if (stateInPartition[transitionTable[partition[i]][symbol]] == stateInPartition[transitionTable[partition[j]][symbol]])
                        {
                            continue;
                        }
                        else
                        {
                            partition.erase(find(partition.begin(),partition.end(),i))
                        }
                    }
                }
            }
        }
    }

    return 0;
}
/*
    |---------------------------------------------------|
    |||   https://codeforces.com/profile/codechaser   |||
    |||   https://www.codechef.com/users/codechaser   |||
    |||        https://github.com/code-chaser         |||
    |---------------------------------------------------|
*/