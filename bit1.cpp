#include <bits/stdc++.h>
using namespace std;
struct trans
{
    string id;
    int weight;
    int fees;
    vector<string> par;
};
struct trans_mapped
{
    int id;
    int weight;
    int fees;
    vector<int> par;
};
int W = 4000000;
vector<vector<pair<int, vector<int>>>> dp(2, vector<pair<int, vector<int>>>(W + 1, {0, {}}));
// declaring Global Variables for taking input from given CSV file
vector<trans> store;
vector<trans_mapped> store_mapped;
string word, line;
//------------------------

// Creating function for taking input from
void csv_in()
{
    fstream fin;
    fin.open("mempool.csv", ios::in);

    getline(fin, line);
    cout << line << endl;

    while (getline(fin, line))
    {
        stringstream lineStream(line);
        string id1;
        int fee1, weight1;
        getline(lineStream, word, ',');
        id1 = (word);
        getline(lineStream, word, ',');
        fee1 = (stoi(word));
        getline(lineStream, word, ',');
        weight1 = (stoi(word));
        vector<string> temp;
        while (getline(lineStream, word, ';'))
        {
            temp.push_back(word);
        }
        store.push_back({id1, weight1, fee1, temp});
    }
}

pair<int, vector<int>> KnapSack(vector<trans_mapped> store)
{

    // memset(dp, 0, sizeof(dp));
    int i = 0;
    int n = store.size();
    while (i < n)
    {
        int j = 0;
        if (i % 2 != 0)
        {
            while (++j <= W) // check for each value
            {
                if (store[i].weight <= j) // include element
                {
                    if (store[i].fees + dp[0][j - store[i].weight].first > dp[0][j].first)
                    {
                        dp[1][j].first = store[i].fees + dp[0][j - store[i].weight].first;
                        dp[1][j].second = dp[0][j - store[i].weight].second;
                        dp[1][j].second.push_back(store[i].id);
                    }
                    else
                    {
                        dp[1][j] = dp[0][j];
                    }
                }
                else // exclude element
                {
                    dp[1][j] = dp[0][j];
                }
            }
        }

        else
        {
            while (++j <= W)
            {
                if (store[i].weight <= j)
                {
                    if (store[i].fees + dp[1][j - store[i].weight].first > dp[1][j].first)
                    {
                        dp[0][j].first = store[i].fees + dp[1][j - store[i].weight].first;
                        dp[0][j].second = dp[1][j - store[i].weight].second;
                        dp[0][j].second.push_back(store[i].id);
                    }
                    else
                    {
                        dp[0][j] = dp[1][j];
                    }
                }
                else
                {
                    dp[0][j] = dp[1][j];
                }
            }
        }
        i++;
    }
    return (n % 2 != 0) ? dp[0][W] : dp[1][W];
}

void rec(vector<trans_mapped> &store, unordered_set<int> &s, vector<int> &final, vector<int> &run, int i, int w, int f, int &mx, long long &it)
{
    if (it >= 10000000000)
    {
        return;
    }
    // it++;
    if (i == store.size() || 4000000 - w < 440)
    {
        if (mx < f)
        {
            mx = f;
            final = run;
        }
        it++;
        return;
    }
    if (w + store[i].weight <= 4000000 && s.find(store[i].id) == s.end())
    {
        int flag = 1;
        for (int i1 = 0; i1 < store[i].par.size(); i1++)
        {
            if (s.find(store[i].par[i1]) == s.end())
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            run.push_back(store[i].id);
            s.insert(store[i].id);
            rec(store, s, final, run, i + 1, w + store[i].weight, f + store[i].fees, mx, it);
            s.erase(store[i].id);
            run.pop_back();
        }
    }
    if (it >= 10000000000)
    {
        return;
    }
    rec(store, s, final, run, i + 1, w, f, mx, it);
}

int main()
{
    csv_in();
    ofstream out_file;
    out_file.open("output3.txt");
    vector<trans> final;
    unordered_set<string> s1;
    for (int i = 0; i < store.size(); i++) // Arranging such that parents occur before children
    {
        for (int j = 0; j < store.size(); j++)
        {
            if (s1.find(store[j].id) != s1.end())
            {
                continue;
            }
            int flag = 1;
            for (int k = 0; k < store[j].par.size(); k++)
            {
                if (s1.find(store[j].par[k]) == s1.end())
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                final.push_back(store[j]);
                s1.insert(store[j].id);
            }
        }
        if (s1.size() == store.size())
        {
            break;
        }
    }

    unordered_map<string, int> mapping_id; // mapping string to integers, to increase processing speed
    unordered_map<int, string> reverse_id; // reverse mapping to retrieve id
    for (int i = 0; i < store.size(); i++)
    {
        mapping_id[store[i].id] = i;
        reverse_id[i] = store[i].id;
    }
    for (int i = 0; i < store.size(); i++)
    {
        int id1 = mapping_id[store[i].id];
        int f1 = store[i].fees;
        int w1 = store[i].weight;
        vector<int> temp;
        for (int k = 0; k < store[i].par.size(); k++)
        {
            temp.push_back(mapping_id[store[i].par[k]]);
        }
        store_mapped.push_back({id1, w1, f1, temp});
    }
    //freeing up memory , hopefully
    store.clear();
    s1.clear();
    //-------

    // pair<int, vector<int>> f = KnapSack(store_mapped);
    // cout << f.first << endl;
    // for (auto i : f.second)
    // {
    //     cout << i << endl;
    // }
    int sum = 0;
    // vector<vector<int>> par_recursive(store_mapped.size());
    // for (int i = 0; i < store_mapped.size(); i++)
    // {
    //     // sum = max(sum, int(store_mapped[i].par.size()));
    //     unordered_set<int> s;
    //     for (int j = 0; j < store_mapped[i].par.size(); j++)
    //     {
    //         s.insert(store_mapped[i].par[j]);
    //         for (int k = 0; k < store_mapped[store_mapped[i].par[j]].par.size(); k++)
    //         {
    //             s.insert(store_mapped[store_mapped[i].par[j]].par[k]);
    //         }
    //     }
    //     for (auto j : s)
    //     {
    //         par_recursive[i].push_back(j);
    //     }
    // }
    double min_weight = 0;

    vector<int> f;
    int mx = 0;
    long long it = 0;
    int w = 0;
    unordered_set<int> s_int;
    vector<int> run;
    for (int i = 0; i < store_mapped.size(); i++)
    {
        if (double(store_mapped[i].fees) / double(store_mapped[i].weight) > 1.01107)
        {
            int flag = 1;
            for (int j = 0; j < store_mapped[i].par.size(); j++)
            {
                if (s_int.find(store_mapped[i].par[j]) == s_int.end())
                {
                    flag = 0;
                    break;
                }
            }
            if(flag && w + store_mapped[i].weight <= 4000000){
                s_int.insert(store_mapped[i].id);
                f.push_back(store_mapped[i].id);
                mx += store_mapped[i].fees;
                w+= store_mapped[i].weight;
            }
        }
    }
    rec(store_mapped, s_int, f, run, 0, w, mx, mx, it);
    for(int i = 0;i<f.size();i++){
        out_file<<reverse_id[f[i]]<<endl;
    }
    cout << mx << endl;

    return 0;
}
