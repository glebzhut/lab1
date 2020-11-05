#include"Graph.h"

void Benchmark()
{
	cout << "Wait some time. Program is calculation a time of work." << endl;
	vector<time_t> TimeAutogenerationDice;
	vector<time_t> TimeGetStatisticsDices;
	for (int n = 50; n < 250; n += 50)
	{
		map<int, double> ch;
		vector<DishonestDice> dices;
		time_t start = clock();
		for (int i = 0; i < n; i++)
		{
			DishonestDice d;
			d.AutoGenerate();
			dices.push_back(d);
		}
		time_t finish = clock();
		TimeAutogenerationDice.push_back(finish - start);
		start = clock();
		ch = GetStatistic(dices);
		finish = clock();
		TimeGetStatisticsDices.push_back(finish - start);
	}

	vector<time_t> TimeAutogenerateGraphEdges;
	vector<time_t> TimeAutogenerateGraphTops;
	vector<time_t> TimeGraphCheckConectedEdges;
	vector<time_t> TimeGraphCheckConectedTops;
	vector<time_t> TimeGraphMinimalWayTableEdges;
	vector<time_t> TimeGraphMinimalWayTableTops;

	bool connect;
	vector<vector<int>> table;
	for (int n = 50; n < 250; n += 50)
	{
		Graph<int> g(0, n, 0);
		time_t start = clock();
		for (int i = 0; i < n; i++)
			g.ChangeTop(rand(), i);
		time_t finish = clock();
		TimeAutogenerateGraphTops.push_back(finish - start);
		for (int i = 0; i < 50; i++)
			g.AddEdge(rand() % n, rand() % n, rand());
		start = clock();
		connect = g.Check_Connected();
		finish = clock();
		TimeGraphCheckConectedTops.push_back(finish - start);
		start = clock();
		table = g.Minimal_way_table();
		finish = clock();
		TimeGraphMinimalWayTableTops.push_back(finish - start);
	}

	for (int n = 500; n < 2500; n += 500)
	{
		Graph<int> g(0, 50, 0);
		for (int i = 0; i < 20; i++)
			g.AddEdge(rand() % 20, rand() % 20, rand());
		time_t start = clock();
		for (int i = 0; i < n; i++)
			g.AddEdge(rand() % 20, rand() % 20, rand());
		time_t finish = clock();
		TimeAutogenerateGraphEdges.push_back(finish - start);
		connect = g.Check_Connected();
		finish = clock();
		TimeGraphCheckConectedEdges.push_back(finish - start);
		start = clock();
		table = g.Minimal_way_table();
		finish = clock();
		TimeGraphMinimalWayTableEdges.push_back(finish - start);
	}


	cout << "Statistic for Dihonest Dices:" << endl;
	cout << setw(20) << "Number of elements" << setw(10) << 50 << setw(10) << 100 << setw(10) << 150 << setw(10) << 200 << endl;
	cout << setw(20) << "AutoGeneration" << setw(10) << TimeAutogenerationDice[0] << setw(10) << TimeAutogenerationDice[1]
		<< setw(10) << TimeAutogenerationDice[2] << setw(10) << TimeAutogenerationDice[3] << endl;
	cout << setw(20) << "Getting stats" << setw(10) << TimeGetStatisticsDices[0] << setw(10) << TimeGetStatisticsDices[1]
		<< setw(10) << TimeGetStatisticsDices[2] << setw(10) << TimeGetStatisticsDices[3] << endl;
	system("pause");
	cout << endl;

	cout << "This is statistic for Graph and different number of tops(50 edges)." << endl;
	cout << setw(20) << "Number of tops" << setw(10) << 50 << setw(10) << 100 << setw(10) << 150 << setw(10) << 200 << endl;
	cout << setw(20) << "AutoGeneration" << setw(10) << TimeAutogenerateGraphTops[0] << setw(10) << TimeAutogenerateGraphTops[1]
		<< setw(10) << TimeAutogenerateGraphTops[2] << setw(10) << TimeAutogenerateGraphTops[3] << endl;
	cout << setw(20) << "Check connected" << setw(10) << TimeGraphCheckConectedTops[0] << setw(10) << TimeGraphCheckConectedTops[1]
		<< setw(10) << TimeGraphCheckConectedTops[2] << setw(10) << TimeGraphCheckConectedTops[3] << endl;
	cout << setw(20) << "Minimal way table" << setw(10) << TimeGraphMinimalWayTableTops[0] << setw(10) << TimeGraphMinimalWayTableTops[1]
		<< setw(10) << TimeGraphMinimalWayTableTops[2] << setw(10) << TimeGraphMinimalWayTableTops[3] << endl;

	system("pause");
	cout << endl;

	cout << "This is statistic for Graph and different number of edges(50 tops)." << endl;
	cout << setw(20) << "Number of edges" << setw(10) << 500 << setw(10) << 1000 << setw(10) << 1500 << setw(10) << 2000 << endl;
	cout << setw(20) << "AutoGeneration" << setw(10) << TimeAutogenerateGraphEdges[0] << setw(10) << TimeAutogenerateGraphEdges[1]
		<< setw(10) << TimeAutogenerateGraphEdges[2] << setw(10) << TimeAutogenerateGraphEdges[3] << endl;
	cout << setw(20) << "Check connected" << setw(10) << TimeGraphCheckConectedTops[0] << setw(10) << TimeGraphCheckConectedTops[1]
		<< setw(10) << TimeGraphCheckConectedEdges[2] << setw(10) << TimeGraphCheckConectedEdges[3] << endl;
	cout << setw(20) << "Minimal way table" << setw(10) << TimeGraphMinimalWayTableEdges[0] << setw(10) << TimeGraphMinimalWayTableEdges[1]
		<< setw(10) << TimeGraphMinimalWayTableEdges[2] << setw(10) << TimeGraphMinimalWayTableEdges[3] << endl;
	system("pause");
	cout << endl;

}