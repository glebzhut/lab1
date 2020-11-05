#include "Graph.h"

void Menu()
{
	string types[4]
	{
		"Interactive dialog mode;",
		"Demonstrative mode;",
		"Benchmark;",
		"Exit."
	};
	int position = 0;
	bool end = false;

	while (!end)
	{
		system("cls");
		cout << "    Choose the mode:" << endl;
		for (int i = 0; i < 4; i++)
		{
			if (i == position)
				cout << "->  " << types[i] << endl;
			else cout << "    " << types[i] << endl;
		}

		char key;
		key = _getch();
		if ((int)key != 13)
		{
			if ((int)key == -32)
			{
				key = _getch();
				if ((int)key == 72)
				{
					if (position > 0)
						position--;
					else position = 3;
				}

				if ((int)key == 80)
				{
					if (position < 3)
						position++;
					else position = 0;
				}
			}
		}
		else
		{
			system("cls");
			switch (position)
			{
			case 0:
				inter();
				break;
			case 1:
				Demo();
				break;
			case 2:
				Benchmark();
				break;
			case 3:
				end = true;
				break;
			}
		}
	}
}
