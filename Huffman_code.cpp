#include <bits/stdc++.h>
using namespace std;
// define the maximum n and m of input Specification
#define MAXN 64
#define MAXM 1001

/*
 * -------------------------------- Main idea about our algorithm --------------------------------
 * first of all, we should check that if their submission cost more than cost by huffman's algorithm
 * As it mentions that The optimal solution is not necessarily generated by Huffman algorithm. So just cost-equal is enough.
 * secondly, we should check that no code is a prefix of another.
 * we can sort the code by string length and then check for prefix step by step.
 * the time complexity I think is m*(n + nlog(n) + n^2*max(length(code))^2)
*/

map<char, int> char_freq;                          // store the charecter and map its frequency.
priority_queue<int, vector<int>, greater<int>> pq; // priority queue to use huffman's algorithm.

// compare function to sort the string in m students' input in ascending order by size.
bool cmp(pair<char, string> x, pair<char, string> y)
{
    return x.second.size() < y.second.size();
}
// calculate the cost by huffman's algorithm by simulating the priority queue
// and we can add it to cost level by level.
int Huffman_cost()
{
    int cost = 0;
    while (!pq.empty())
    {
        int tl = pq.top();
        pq.pop();
        if (pq.empty())
            break;
        int tr = pq.top();
        pq.pop();
        cost += tl + tr;
        pq.push(tl + tr);
    }
    return cost;
}

int main()
{
    int n, m;        // store the input n and m.
    bool flag[MAXM]; // store if the student's submission is correct.
    int cost = 0;    // store the cost by real huffman cost.
    cin >> n;
    // deal with n character and map them.
    for (int i = 0; i < n; i++)
    {
        int t;
        char c;
        cin >> c >> t;
        char_freq.insert(pair<char, int>(c, t));
        pq.push(t);
    }
    cost = Huffman_cost();
    // initialize the flag of m students' submission as true.
    cin >> m;
    // check the submissions' correctness.
    for (int i = 0; i < m; i++)
    {
        flag[i] = true;
        vector<pair<char, string>> t;
        int temp_cost = 0;
        for (int j = 0; j < n; j++)
        {
            char c;
            string s;
            cin >> c >> s;
            t.push_back(pair<char, string>(c, s));
            // calculate the cost of this submission.
            temp_cost += char_freq[c] * s.size();
        }
        if (temp_cost > cost)
        {
            flag[i] = false;
            continue;
        }
        // sort the length of (code)string in ascending order.
        sort(t.begin(), t.end(), cmp);
        // check if some code is a prefix of another. temp is false if we find a prefix and break.
        bool temp = true;
        for (int j = 0; j < t.size(); j++)
        {
            for (int k = j + 1; k < t.size(); k++)
            {
                // check if some code is a prefix of another.
                if (t[k].second.substr(0, t[j].second.size()) == t[j].second)
                    temp = flag[i] = false;
                if (!temp)
                    break;
            }
            if (!temp)
                break;
        }
    }
    // output the check result.
    for (int i = 0; i < m; i++)
    {
        if (flag[i])
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}