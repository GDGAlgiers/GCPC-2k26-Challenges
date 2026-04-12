#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string rna;
    cin >> rna;

    vector<string> markers = {"ACGUAUGC", "AUGCGUAG", "UGCUAGCU"};
    for (const auto &m : markers)
    {
        if (rna.find(m) != string::npos)
        {
            cout << "True" << endl;
            return 0;
        }
    }
    cout << "False" << endl;
    return 0;
}
