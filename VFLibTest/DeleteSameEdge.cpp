//#include <iostream>
//#include <vector>
//#include <map>
//#include <string>
//#include <fstream>
//
//using namespace std;
//
//int main()
//{
//	map<string, int> m;
//
//	ifstream infile("sf0103_Edge.txt");
//	ofstream outfile("NoDoubleEdge.txt");
//
//	string s = "";
//	while (!infile.eof())
//	{
//		getline(infile,s);
//		m[s] = 1;
//	}
//
//	map<string, int>::iterator iter;
//	for (iter = m.begin(); iter != m.end();iter++)
//	{
//		outfile << iter->first << endl;
//	}
//
//
//	infile.close();
//	outfile.close();
//
//	return 0;
//}