#pragma once
#include"DishonestDice.h"

using namespace std;

template <typename T>
class GraphNode
{
private:
	T val;
	int number_of_top;

public:
	GraphNode() {};

	GraphNode(T val, int number_of_top)
	{
		this->val = val;
		this->number_of_top = number_of_top;
	}

	void SetNumberOfTop(int numtop)
	{
		this->number_of_top = numtop;
	}

	void SetValue(int numtop)
	{
		this->number_of_top = numtop;
	}

	T GetValue()const
	{
		return val;
	}

	int GetNumberOfTop() const
	{
		return number_of_top;
	}
};

template <typename T>
class GraphEdge
{
private:
	GraphNode<T> start;
	GraphNode<T> finish;
	T val;
public:
	GraphEdge() {};

	GraphEdge(T valtop1, int numtop1, T valtop2, int numtop2, T val)
	{
		this->start = GraphNode<T>(valtop1, numtop1);
		this->finish = GraphNode<T>(valtop2, numtop2);
		this->val = val;
	}

	void SetStart(GraphNode<T> s)
	{
		start = s;
	}

	void SetFinish(GraphNode<T> f)
	{
		finish = f;
	}

	void SetVal(T val)
	{
		this->val = val;
	}

	GraphNode<T> GetStart()const
	{
		return start;
	}

	GraphNode<T> GetFinish() const
	{
		return finish;
	}

	T GetValue()const
	{
		return val;
	}
};

template <typename T>
ostream& operator<<(ostream& s, GraphNode<T> n)
{
	s << n.GetNumberOfTop() << ": " << n.GetValue();
	return s;
}

template <typename T>
ostream& operator<<(ostream& s, GraphEdge<T> e)
{
	s << "Start: " << e.GetStart() << ". Finish: " << e.GetFinish() << ". Value: " << e.GetValue();
	return s;
}

template <typename T>
class Graph
{
private:
	bool directed;
	T zero_val;
	vector<GraphNode<T>> tops;
	vector<GraphEdge<T>> edges;

	bool CheckNumberOfTop(int numtop) const
	{
		return numtop < tops.size() && numtop >= 0;
	}

	vector<int> Tops_that_used() const
	{
		vector<int> tp(tops.size(), 0);
		for (int i = 0; i < edges.size(); i++)
		{
			tp[edges[i].GetStart().GetNumberOfTop()] = 1;
			tp[edges[i].GetFinish().GetNumberOfTop()] = 1;
		}
		return tp;
	}

	void Connected_tops(const vector<vector<T>> Matrix, vector<int>& tops, int index_of_top) const
	{
		tops[index_of_top] = 2;
		for (int i = 0; i < tops.size(); i++)
		{
			if (!(Matrix[index_of_top][i] == zero_val))
				if (tops[i] == 1)
					Connected_tops(Matrix, tops, i);
		}
	}

	int Min(int a, int b, int c) const
	{
		if (b == -1 || c == -1)
			return a;
		else
		{
			if (a > -1 && a < b + c)
				return a;
			else return b + c;
		}
	}

	void UpdateGraph(int numtop)
	{
		for (int i = numtop; i < tops.size(); i++)
			tops[i].SetNumberOfTop(i);
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].GetStart().GetNumberOfTop() == numtop)
			{
				edges.erase(edges.begin() + i);
				i--;
			}
			else if (edges[i].GetFinish().GetNumberOfTop() == numtop)
			{
				edges.erase(edges.begin() + i);
				i--;
			}
			else if (edges[i].GetStart().GetNumberOfTop() > numtop)
			{
				GraphNode<T> new_node(edges[i].GetStart().GetValue(), (edges[i].GetStart().GetNumberOfTop()-1));
				edges[i].SetStart(new_node);
			}
			else if (edges[i].GetFinish().GetNumberOfTop() > numtop)
			{
				GraphNode<T> new_node(edges[i].GetFinish().GetValue(), (edges[i].GetFinish().GetNumberOfTop()-1));
				edges[i].SetFinish(new_node);
			}
		}
	}
public:
	Graph() {};

	Graph(bool type, int size, T zero_val) 
	{
		directed = type;
		this->zero_val = zero_val;
		vector<GraphNode<T>> new_graph;
		for (int i = 0; i < size; i++)
			new_graph.push_back(GraphNode<T>(zero_val, i));
		tops = new_graph;
	}

	void operator= (const Graph& g)
	{
		zero_val = g.zero_val;
		directed = g.directed;
		tops = g.tops;
		edges = g.edges;
	}

	void ChangeTop(T valtop, int numtop)
	{
		if (CheckNumberOfTop(numtop))
		{
			for (int i = 0; i < tops.size(); i++)
				if (tops[i].GetNumberOfTop() == numtop)
				{
					tops[i] = GraphNode<T>(valtop,numtop);
					break;
				}
		}
		else throw logic_error("Number of top out of range: " + to_string(numtop));
	}

	void NewTop(T val)
	{
		tops.push_back(GraphNode<T>(val, tops.size()));
	}

	void DelTop(int numtop)
	{
		if (CheckNumberOfTop(numtop))
		{
			for (int i = 0; i < tops.size(); i++)
			{
				if (tops[i].GetNumberOfTop() == numtop)
				{
					tops.erase(tops.begin() + i);
					break;
				}
			}
			UpdateGraph(numtop);
		}
		else throw logic_error("Number of top out of range: " + to_string(numtop));
	}
	
	void DelEdge(int start, int finish)
	{
		if (CheckNumberOfTop(start))
			if (CheckNumberOfTop(finish))
				for (int i = 0; i < edges.size(); i++)
				{
					if (!directed && edges[i].GetFinish().GetNumberOfTop() == start && edges[i].GetStart().GetNumberOfTop() == finish)
					{
						edges.erase(edges.begin() + i);
						i--;
					}
					else if (edges[i].GetStart().GetNumberOfTop() == start && edges[i].GetFinish().GetNumberOfTop() == finish)
					{
						edges.erase(edges.begin() + i);
						i--;
					}
				}
			else throw logic_error("Number of top out of range: " + to_string(finish));
		else throw logic_error("Number of top out of range: " + to_string(finish));
	}

	void AddEdge(int start, int finish, T val)
	{
		if(CheckNumberOfTop(start))
			if (CheckNumberOfTop(finish))
			{
				DelEdge(start, finish);
				if (!directed)
					edges.push_back(GraphEdge<T>(tops[finish].GetValue(), tops[finish].GetNumberOfTop(),
						tops[start].GetValue(), tops[start].GetNumberOfTop(), val));
				edges.push_back(GraphEdge<T>(tops[start].GetValue(), tops[start].GetNumberOfTop(),
					tops[finish].GetValue(), tops[finish].GetNumberOfTop(), val));
			}
			else throw logic_error("Number of top out of range: " + to_string(finish));
		else throw logic_error("Number of top out of range: " + to_string(finish));
	}

	vector<vector<T>> GraphMatrix() const
	{
		vector<vector<T>> result(tops.size(), vector<T>(tops.size(), zero_val));
		for (int i = 0; i < edges.size(); i++)
			result[edges[i].GetStart().GetNumberOfTop()][edges[i].GetFinish().GetNumberOfTop()] = edges[i].GetValue();
		return result;
	}
	
	void InfoAboutTops()const
	{
		for (int i = 0; i < tops.size();i++)
			cout << tops[i] << endl;
	}

	void PrintList()const
	{
		for (const auto& i : edges)
			cout << i << endl;
	}

	bool Check_Connected() const
	{
		bool Connected_graph = true;
		vector<int> topes = Tops_that_used();
		vector<vector<T>> table = GraphMatrix();
		if (directed)
		{
			for (int i = 0; i < tops.size(); i++)
				for (int j = 0; j < tops.size(); j++)
					if (!(table[i][j] == zero_val))
						table[j][i] = table[i][j];
		}
		int n = 0;
		while (!topes[n])
			n++;
		Connected_tops(table, topes, n);
		for (int i = 0; i < topes.size(); i++)
			if (topes[i] == 1)
				Connected_graph = false;
		return Connected_graph;
	}

	vector<vector<int>> Minimal_way_table() const
	{
		vector<vector<int>> table_distance (tops.size(), vector<int> (tops.size(), -1));
		for (int i = 0; i < edges.size(); i++)
			table_distance[edges[i].GetStart().GetNumberOfTop()][edges[i].GetFinish().GetNumberOfTop()] = 1;
		for (int i = 0; i < table_distance.size(); i++)
			table_distance[i][i] = 0;
		for (int k = 0; k < table_distance.size(); k++)
			for (int i = 0; i < table_distance.size(); i++)
				for (int j = 0; j < table_distance.size(); j++)
					table_distance[i][j] = Min(table_distance[i][j], table_distance[i][k], table_distance[k][j]);
		return table_distance;
	}

	int Minimal_way(int start_top, int finish_top) const
	{
		return Minimal_way_table()[start_top][finish_top];
	}
};

void inter();
void Demo();
void Benchmark();
void Menu();