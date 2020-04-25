#include <iostream>
#include <algorithm> // ordering function sort ()
#include <map>
#include <queue>
using namespace std;
 
 typedef pair <char, string> PAIR; // + vector map to model
 
 int cmp (const PAIR & x, const PAIR & y) // make custom sort () sort by which way
{
    return x.second.size() < y.second.size();
}
 
int main()
{
    int num;
    cin >> num;
    char *c = new char[num];
    int *f = new int[num];
         map <char, int> myMap; // for data storage node and weights, and constitute a map
         // use high priority queue
    priority_queue<int, vector<int>, greater<int> >pq;
 
         for (int i = 0; i <num; i ++) // number of occurrences and the input node (weight)
    {
        cin >> c[i] >> f[i];
        myMap[c[i]] = f[i];
                 pq.push (f [i]); // the weight is pressed into the priority queue
    }
         // Calculate the value of WPL
    int myWpl = 0;
    while(!pq.empty())
    {
        int myTop = pq.top();
        pq.pop();
        if(!pq.empty())
        {
            int myTop2 = pq.top();
            pq.pop();
            pq.push(myTop + myTop2);
            int m = myTop + myTop2;
            myWpl += m;
        }
    }
    cout << myWpl;
         // input test data
         int checkNum; // test group the number of data
    cin >> checkNum;
    for(int i=0; i<checkNum; i++)
    {
        int wpl = 0;
        char ch;
        string s;
                 // vector + PAIR imitate the map, so that it can be sorted
        vector<PAIR> checkVec;
        for(int j=0; j<num; j++)
        {
            cin >> ch >> s;
                         checkVec.push_back (make_pair (ch, s)); // add to the test data and encoding the vector
            wpl += s.size() * myMap[ch];
        }
                 sort (checkVec.begin (), checkVec.end (), cmp); // Sort according to code length
        if(wpl != myWpl)
        {
            cout << "No" << endl;
            continue;
        }
        else
        {
                         bool flag = true; // indicates a condition has been met: wpl minimum (wpl == myWpl)
 
                         // The second condition: prefix code can not be a prefix of the other coded: substr ()
            for(int i=0; i<num; i++)
            {
                string tmp = checkVec[i].second;
                for(int j=i+1; j<num; j++)
                {
                    if(checkVec[j].second.substr(0,tmp.size())==tmp)
                        flag = false;
                }
            }
            if(flag == true)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
    }
    return 0;
}