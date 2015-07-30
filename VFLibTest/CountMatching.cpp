#include "argraph.h"
#include "argedit.h"
#include "match.h"
#include "vf2_sub_state.h"

#include <fstream>

#define MAXNODES 200

int matchingCnt = 0;//记录发现的匹配数

void getNodeEdge(ARGEdit &ed,int count)
{
	int i, j;
	for (int i = 0; i < count; i++)
		ed.InsertNode(NULL);

	for (i = 0; i < count; i++)
		for (j = 0; j < count; j++)
			if (i != j)
				ed.InsertEdge(i, j, NULL);
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

	//返回false用于搜索下一个匹配
	return false;
}

int main()
{
	//创建模式图和数据图的ed
	ARGEdit pattern_ed,data_ed;

	getNodeEdge(pattern_ed, 3);
	getNodeEdge(data_ed,4);

	Graph pattern_g(&pattern_ed),data_g(&data_ed);

	//创建子图异构的初始状态
	VF2SubState s0(&pattern_g, &data_g);

	//创建输出文件
	FILE *f = fopen("subIso.txt","w");

	match(&s0,graph_visitor,f);

	fprintf(f, "n: %d", matchingCnt);//将找到的匹配数输出至文本

	fclose(f);

	return 0;
}