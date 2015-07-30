#include "argraph.h"
#include "argedit.h"
#include "match.h"
#include "vf2_sub_state.h"

#include <fstream>

#define MAXNODES 200

int matchingCnt = 0;//��¼���ֵ�ƥ����

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
	/*************** VFLib�ĵ��е�ʾ������,ƥ��Դ�����ni1��ni2�� **************/
	//FILE *f = (FILE *)usr_data;
	////��ͳ�Ƶ���ƥ��ڵ�������ļ���
	//fprintf(f,"n:%d",n); 
	//fprintf(f, "\n");
	//for (int i = 0; i < n; i++)
	//	fprintf(f,"(%hd,%hd)",ni1[i],ni2[i]);

	//fprintf(f,"\n");
	/*************** VFLib�ĵ��е�ʾ������,ƥ��Դ�����ni1��ni2�� **************/

	matchingCnt++; //��ֻ��Ҫ�õ�ƥ�������

	//����false����������һ��ƥ��
	return false;
}

int main()
{
	//����ģʽͼ������ͼ��ed
	ARGEdit pattern_ed,data_ed;

	getNodeEdge(pattern_ed, 3);
	getNodeEdge(data_ed,4);

	Graph pattern_g(&pattern_ed),data_g(&data_ed);

	//������ͼ�칹�ĳ�ʼ״̬
	VF2SubState s0(&pattern_g, &data_g);

	//��������ļ�
	FILE *f = fopen("subIso.txt","w");

	match(&s0,graph_visitor,f);

	fprintf(f, "n: %d", matchingCnt);//���ҵ���ƥ����������ı�

	fclose(f);

	return 0;
}