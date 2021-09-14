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
#include <fstream>

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
    cout << p.first << " " << p.second << "\n";
    return cout;
}
template <typename T>
ostream &operator<<(ostream &cout, vector<T> v)
{
    int cnt = 0;
    for (auto &i : v)
        cout << i << ((++cnt) != v.size() ? " " : "\n");
    return cout;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &cout, map<T1, T2> m)
{
    for (auto i : m)
        cout << i;
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
    if (currentState != -1 && currentState)
        isReachable[currentState] = 1;
    for (auto i : alphabet)
    {
        if ((transitionTable[currentState][i] != -1) && (!isReachable[transitionTable[currentState][i]]))
            reachable(transitionTable[currentState][i], alphabet);
    }
    return;
}

int transition(int state, char symbol)
{
    return transitionTable[state][symbol];
}

int main()
{
    freopen("input.txt", "r", stdin);
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

    // marking reachable states;
    reachable(initialState, alphabet);
    vector<int> reachableStates, reachableFinalStates, reachableNonFinalStates;
    for (auto i : isReachable)
    {
        if (i.second)
        {
            reachableStates.push_back(i.first);
            if (isFinal[i.first])
                reachableFinalStates.push_back(i.first);
            else
                reachableNonFinalStates.push_back(i.first);
        }
        else
            isFinal[i.first] = 0;
    }

    vector<vector<int>> partitions;
    partitions.push_back(reachableNonFinalStates);
    partitions.push_back(reachableFinalStates);

    map<int, int> stateInPartition;

    cout << "\n";
    for (int i = 0; i < (13 * (alphabet.size() + 1)); i++)
        cout << "~";
    cout << "\n";
    cout << "\nReachable States: " << reachableStates;
    cout << "\nReachable Final States: " << reachableFinalStates;
    cout << "\nReachable Non-Final States: " << reachableNonFinalStates;
    cout << "\n";
    for (int i = 0; i < (13 * (alphabet.size() + 1)); i++)
        cout << "~";
    cout << "\n\n";
    int tempInt = 0;
    while (1)
    {
        tempInt++;
        vector<vector<int>> newPartitions;
        map<int, int> stateInNewPartition;
        map<int, bool> allocated, checked;
        for (int i = 1; i <= partitions.size(); i++)
        {
            for (auto j : partitions[i - 1])
            {
                stateInPartition[j] = i;
            }
        }
        for (auto partition : partitions)
        {
            if (partition.size() == 1)
            {
                newPartitions.push_back(partition);
                continue;
            }
            for (int i = 0; i < partition.size(); i++)
            {
                if (checked[partition[i]])
                    continue;
                if (i == partition.size() - 1)
                {
                    newPartitions.push_back({partition[i]});
                    break;
                }
                checked[partition[i]] = 1;
                for (int j = i + 1; j < partition.size(); j++)
                {
                    bool flag = 1;
                    for (auto symbol : alphabet)
                    {
                        if (!(stateInPartition[transitionTable[partition[i]][symbol]] == stateInPartition[transitionTable[partition[j]][symbol]]))
                        {
                            if (!allocated[partition[i]])
                            {
                                newPartitions.push_back({partition[i]});
                                allocated[partition[i]] = 1;
                                stateInNewPartition[partition[i]] = newPartitions.size();
                            }
                            flag = 0;
                            break;
                        }
                    }
                    if (flag)
                    {
                        checked[partition[j]] = 1;
                        if (allocated[partition[i]])
                        {
                            newPartitions[stateInNewPartition[partition[i]] - 1].push_back(partition[j]);
                            allocated[partition[j]] = 1;
                            stateInNewPartition[partition[j]] = stateInNewPartition[partition[i]];
                        }
                        else
                        {
                            newPartitions.push_back({partition[i], partition[j]});
                            allocated[partition[i]] = allocated[partition[j]] = 1;
                            stateInNewPartition[partition[i]] = stateInNewPartition[partition[j]] = newPartitions.size();
                        }
                    }
                }
            }
        }
        if (newPartitions.size() == partitions.size())
            break;
        partitions = newPartitions;
    }

    cout << "Number of equivalence states partitions: " << partitions.size() << "\n\nPartitions are:\n";
    for (int i = 0; i < partitions.size(); i++)
    {
        cout << "Partition " << i + 1 << ": " << partitions[i];
    }
    cout << "\n";
    for (int i = 0; i < (13 * (alphabet.size() + 1)); i++)
        cout << "~";
    cout << "\n\n\n";

    for (int i = 0; i < (13 * (alphabet.size() + 1)) / 2 - 8; i++)
        cout << " ";

    cout << "TRANSITION TABLE\n\n\n";
    for (int i = 0; i < (13 * (alphabet.size() + 1)); i++)
        cout << "~";
    cout << "\n             "; //" Partition 1 ";
    for (auto symbol : alphabet)
    {
        cout << "      " << symbol << "      ";
    }
    cout << "\n";
    for (int i = 0; i < partitions.size(); i++)
    {
        cout << " Partition " << i + 1 << " ";
        for (auto symbol : alphabet)
        {
            if (stateInPartition[transitionTable[partitions[i][0]][symbol]])
                cout << " Partition " << stateInPartition[transitionTable[partitions[i][0]][symbol]] << " ";
            else
                cout << "      -      ";
        }
        cout << "\n";
    }
    for (int i = 0; i < (13 * (alphabet.size() + 1)); i++)
        cout << "~";
    cout << "\n\n\n";
    for (int i = 0; i < (13 * (alphabet.size() + 1)); i++)
        cout << "~";
    cout << "\n\n";
    return 0;
}
/*
    |---------------------------------------------------|
    |||   https://codeforces.com/profile/codechaser   |||
    |||   https://www.codechef.com/users/codechaser   |||
    |||        https://github.com/code-chaser         |||
    |---------------------------------------------------|
*/