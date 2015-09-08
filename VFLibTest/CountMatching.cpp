#include "argraph.h"
#include "argedit.h"
#include "match.h"
#include "vf2_sub_state.h"
#include "vf_sub_state.h"

#include <iostream>
#include <fstream>
#include <string>

//添加节点角色的属性
#include "Role.h"

using namespace std;

#define MAXNODES 60000

int matchingCnt = 0;//记录发现的匹配数

void getNodeEdge(ARGEdit &ed,string nodeName,string edgeName)
{
	/******************************获取节点************************************/
	//从文件读取节点，节点文件一行是节点ID+" "+该节点的角色ID
	ifstream nodeFile(nodeName);
	int nodeID, role;

	while (!nodeFile.eof())
	{
		nodeFile >> nodeID >> role;

		//cout << nodeID << " " << role << endl;
		ed.InsertNode(new Role(role));
	}

	nodeFile.close();

	/******************************获取边************************************/
	//从文件读取边，边文件一行是起始节点ID+" "+目标节点ID
	ifstream edgeFile(edgeName);
	int start,end;
	//cout << edgeName << endl;

	while (!edgeFile.eof())
	{
		edgeFile >> start >> end;
		//cout << start << " " << startRole << " " << end << " " << endRole << endl;

		//创建边
		ed.InsertEdge(start, end, NULL);
	}
	
	edgeFile.close();
}

void getData(ARGEdit &ed,int count)
{
	for (int i = 0; i < count; i++)
		ed.InsertNode(NULL);

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (i != j)
				ed.InsertEdge(i, j, NULL);
		}
	}
}

bool graph_visitor(int n, node_id ni1[], node_id ni2[], void *usr_data)
{
	/*************** VFLib文档中的示例代码,匹配对储存在ni1和ni2中 **************/
	//FILE *f = (FILE *)usr_data;
	////将统计到的匹配节点输出到文件中
	//fprintf(f,"n:%d",n); 
	//fprintf(f, "\n");
	//for (int i = 0; i < n; i++)
	//	fprintf(f,"(%hd,%hd)",ni1[i],ni2[i]);

	//fprintf(f,"\n");
	/*************** VFLib文档中的示例代码,匹配对储存在ni1和ni2中 **************/

	matchingCnt++; //我只需要得到匹配的数量
	cout << matchingCnt << endl;
	//返回false用于搜索下一个匹配
	return false;
}

int main()
{
	//创建模式图和数据图的ed
	ARGEdit pattern_ed,data_ed;

	getNodeEdge(pattern_ed,"patternNode.txt","patternEdge.txt");
	getNodeEdge(data_ed,"dataNode.txt","dataEdge.txt");

	//getData(pattern_ed,4);
	//getData(data_ed,5);
	ARGraph<Role, void> data_g(&data_ed);
	ARGraph<Role, void> pattern_g(&pattern_ed);

	//设置属性清除器
	data_g.SetNodeDestroyer(new RoleDestroyer());
	pattern_g.SetNodeDestroyer(new RoleDestroyer());

	//设置属性比较器
	data_g.SetNodeComparator(new RoleComparator());
	pattern_g.SetNodeComparator(new RoleComparator());

	//创建子图异构的初始状态
	VFSubState s0(&pattern_g, &data_g);

	//创建输出文件
	FILE *f = fopen("subIso.txt","w");

	match(&s0,graph_visitor,f);

	//fprintf(f, "n: %d", matchingCnt);//将找到的匹配数输出至文本

	cout << matchingCnt << endl;

	fclose(f);



	return 0;
}