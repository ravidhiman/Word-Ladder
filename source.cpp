//Input:  Dictionary = { POON, PLEE, SAME, POIE, PLEA, PLIE, POIN }
//	start = TOON
//	target = PLEA
//	Output : 7
//	Explanation : TOON - POON - POIN - POIE - PLIE - PLEE - PLEA

#include<iostream>
#include<unordered_set>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;

void makeGraph(unordered_map<string, vector<string>> &myGraph,const string& start, const unordered_set<string>& dict)
{
	string temp;
	vector<string> vec;
	for (int i = 0;i < start.length();i++)
	{
		temp = start;
		for (int j = 0;j < 26;j++)
		{
			if (temp[i] != char('A' + j))
			{
				temp[i] = 'A' + j;
				if (dict.find(temp) != dict.end())
				{
					vec.push_back(temp);
				}
			}
		}
	}
	myGraph[start] = vec;

	for (auto itr = dict.begin();itr != dict.end();itr++)
	{
		vec.clear();

		for (int i = 0;i < (*itr).length();i++)
		{
			temp = *itr;
			for (int j = 0;j < 26;j++)
			{
				if ((*itr)[i] != char('A' + j))
				{
					temp[i] = 'A' + j;
					if (dict.find(temp) != dict.end())
					{
						vec.push_back(temp);
					}
				}
			}
		}
		myGraph[*itr] = vec;
	}
}

int findShortestPath(const unordered_map<string, vector<string>> &myGraph, const string& start, const string& target)
{
	queue < pair<string, int>> q;
	unordered_set<string> visited;
	q.push(make_pair(start,1));
	visited.insert(start);
	int minPath = -1;
	while (!q.empty())
	{
		pair<string, int> p = q.front();
		q.pop();
		if (p.first == target)
		{
			minPath = p.second;
			break;
		}
		auto vec  = myGraph.find(p.first)->second;
		for (auto itr = vec.begin();itr != vec.end();itr++)
		{
			if (visited.find(*itr) == visited.end())
			{
				visited.insert(*itr);
				q.push(make_pair(*itr, p.second + 1));
			}
		}
	}
	return minPath;
}

int main()
{
	unordered_set<string> dict = { "POON", "PLEE", "SAME", "POIE", "PLEA", "PLIE", "POIN","SOON" };
	string start = "TOON";
	string target = "PLEA";

	unordered_map<string, vector<string>> myGraph;
	makeGraph(myGraph,start, dict);

	cout<< findShortestPath(myGraph, start, target);

	return 0;
}
