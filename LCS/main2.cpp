#include <bits/stdc++.h>
using namespace std;

vector<char> X, Y;
vector<vector<char>> b;
vector<vector<int>> c;

void lcs(vector<char> X, vector<char> Y)
{
  int m = X.size();
  int n = Y.size();
  c.resize(m + 1, vector<int>(n + 1));
  b.resize(m + 1, vector<char>(n + 1));

  for (int i = 0; i <= m; i++)
    c[i][0] = 0;
  for (int j = 0; j <= n; j++)
    c[0][j] = 0;

  for (int i = 1; i <= m; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      if (X[i - 1] == Y[j - 1])
      {
        c[i][j] = c[i - 1][j - 1] + 1;
        b[i][j] = 'D'; // Diagonal
      }
      else if (c[i - 1][j] >= c[i][j - 1])
      {
        c[i][j] = c[i - 1][j];
        b[i][j] = 'U'; // Up
      }
      else
      {
        c[i][j] = c[i][j - 1];
        b[i][j] = 'L'; // Left
      }
    }
  }
}

void print_lcs(int i, int j)
{
  if (i == 0 || j == 0)
    return;

  if (b[i][j] == 'D')
  {
    print_lcs(i - 1, j - 1);
    cout << X[i - 1]; // Assuming X is globally accessible
  }
  else if (b[i][j] == 'U')
  {
    print_lcs(i - 1, j);
  }
  else
  {
    print_lcs(i, j - 1);
  }
}

int main()
{
  string x, y;
  cin >> x >> y; // Directly reading strings from stdin for simplicity
  for (char i : x)
  {
    X.push_back(i);
  }
  for (char i : y)
  {
    Y.push_back(i);
  }

  lcs(X, Y);
  print_lcs(X.size(), Y.size());
  cout << endl; // For a newline after printing the LCS

  return 0;
}
