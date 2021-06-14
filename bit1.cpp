#include <bits/stdc++.h>
using namespace std;
// declaring Global Variables for taking input from given CSV file
vector<string> id;
vector<int> weight;
vector<int> fee;
vector<vector<string>> par;
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

        getline(lineStream, word, ',');
        id.push_back(word);
        getline(lineStream, word, ',');
        fee.push_back(stoi(word));
        getline(lineStream, word, ',');
        weight.push_back(stoi(word));
        vector<string> temp;
        while (getline(lineStream, word, ';'))
        {
            temp.push_back(word);
        }
        par.push_back(temp);
    }
}
int main()
{
    
    csv_in();
    for (int i = 0; i < id.size(); i++)
    {
        cout << id[i] << " " << fee[i] << " " << weight[i] << " ";
        for (int j = 0; j < par[i].size(); j++)
        {
            cout << par[i][j] << " ";
        }
        cout << endl;
    }
}