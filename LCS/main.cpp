#include<bits/stdc++.h>
using namespace std;

vector<char> X, Y;
vector<vector<char>> b;
vector<vector<int>> c;
string LCS;

/**
 * Calculates the length of the longest common subsequence (LCS) between two vectors of characters.
 *
 * @param X The first vector of characters.
 * @param Y The second vector of characters.
 */
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

/**
 * @brief Prints the Longest Common Subsequence (LCS) between two strings.
 *
 * @param i The index of the first string.
 * @param j The index of the second string.
 * @return The LCS between the two strings.
 */
string print_lcs(int i, int j)
{
  if (i == 0 || j == 0)
    return "";

  if (b[i][j] == 'D')
  {
    print_lcs(i - 1, j - 1);
    LCS = LCS + X[i - 1]; // Assuming X is globally accessible
  }
  else if (b[i][j] == 'U')
  {
    print_lcs(i - 1, j);
  }
  else
  {
    print_lcs(i, j - 1);
  }
  return LCS;
}

void debug()
{
  cout << c.size() << " " << c[0].size() << endl;
  for (int i = 0; i < c[i].size(); i++)
  {
    for(int j=0; j<c.size(); j++)
    {
      cout << c[i][j] << " ";
    }
    cout << endl;
  }

  for (int i = 1; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      cout << "i is " << i << " j is " << j <<" value is " <<c[i][j] <<endl;
    }
    cout << endl;
  }

  cout << "X size is : " << X.size() << endl;
  cout << "Y size is : " << Y.size() << endl;
  for (int i = 0; i < X.size(); i++)
  {
    cout << X[i] << " ";
  }
  cout << endl;
  for(int i=0; i<Y.size();i++)
  {
    cout << Y[i] << " ";
  }
  cout << endl;
}

int main(int argc, char const *argv[])
{
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <input file>" << endl;
    return 1;
  }

  ifstream ifs(argv[1]);
  if (!ifs.is_open())
  {
    cerr << "Error: could not open " << argv[1] << endl;
    return 1;
  }

  string x, y;
  ifs >> x >> y;
  for(char i : x)
  {
    X.push_back(i);
  }
  for(char i : y)
  {
    Y.push_back(i);
  }

  cout << "String X: " << x << endl;
  cout << "String Y: " << y << endl;
  lcs(X, Y);
  cout << "LCS: " << print_lcs(X.size(), Y.size()) << endl;
  // debug();

  return 0;

}