//
// Created by 颜聿辰 on 2019/12/18.
//

#ifndef STUDENTSCORESYSTEM_FUNCTIONS_H
#define STUDENTSCORESYSTEM_FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "FileRelated.h"
void welcome_1()			//首页欢迎语
{
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                      ================================\n");
    printf("                     |                                |\n");
    printf("                     |    欢迎来到学生成绩管理系统       |\n");
    printf("                     |                                |\n");
    printf("                      ================================\n");
    printf("\n");
    printf("\n");
    printf("\n");
}

void interval()     		//分隔线函数
{
    printf("====================================================================\n");
}

void title()//成绩单抬头
{
    int j;
    printf("序号   学        号   姓    名   ");
    for(j=0;j<subjects;j++)//分别打印科目名
        printf("%-8s   ",subject_name[j]);
    printf("总  分   均  分\n");//抬头
}

void output_score(int i)	//输出成绩条
{
    int j;
    printf("%-4.0d   %-12s   %-8s   ",stud[i].num,stud[i].no,stud[i].name);	//输出成绩
    for(j=0;j<subjects;j++)
        printf("%-8.2f   ",stud[i].score[j]);
    printf("%-6.2f   %-6.2f\n",stud[i].sum,stud[i].ave);
}

void output_score_order(int *a)//按照order打印全体成绩
{
    int i,j;
    for (i=0;i<students;i++)
    {
        j = *(a+i);
        output_score(j);
    }
}


void scan_stu_sub_number()		//输入学生和科目总数
{
    printf("请输入学生人数：\n");			//学生人数
    printf("students=");
    scanf("%d",&students);
    printf("请输入科目总数：\n");		//科目总数
    printf("subjects=");
    scanf("%d",&subjects);
}

void scan_sub_name()		//输入科目名
{
    int i;
    printf("请分别输入4个汉字以内的课程的名称：\n");
    for(i=0;i<subjects;i++)//分别输入
    {
        printf("请输入第%d个科目的名称:",i+1);
        scanf("%s",subject_name[i]);
    }
}

void scan_scores(int i)		//输入成绩条
{
    int j;
    printf("学生编号：%d\n",stud[i].num=i+1);
    printf("请输入第%d位学生的4字以内的姓名：",stud[i].num);//输入姓名
    scanf("%s",stud[i].name);//录入姓名
    printf("请输入第%d位学生  %s  的12位以内学号：",stud[i].num,stud[i].name);//输入学号
    scanf("%s",stud[i].no);
    stud[i].sum = stud[i].ave = 0;
    for(j=0;j<subjects;j++)//录入每门成绩
    {
        printf("请输入第%d位学生  %s  的第%d个科目  %s  的成绩：",stud[i].num,stud[i].name,j+1,subject_name[j]);
        scanf("%f",&stud[i].score[j]);
        stud[i].sum = stud[i].sum + stud[i].score[j];
    }
    stud[i].ave = stud[i].sum / subjects;
}



void change_information(int change_1,char change_2[])//以change_2方式修改对change_1的信息
{
    int i,j;
    char change_3[100];
    float change_4;
    if(strcmp(change_2,"学号") == 0)//修改学号信息
    {
        printf("请输入修改后的学号：");
        scanf("%s",change_3);
        strcpy(stud[change_1-1].no,change_3);
    }
    if(strcmp(change_2,"姓名") == 0)//修改姓名信息
    {
        printf("请输入修改后的姓名：");
        scanf("%s",change_3);
        strcpy (stud[change_1-1].name,change_3);
    }
    for(i=0;i<subjects;i++)//修改成绩信息
        if(strcmp(subject_name[i],change_2) == 0)
        {
            printf("请输入修改后的 %8s 成绩：",subject_name[i]);
            scanf("%f",&change_4);
            stud[change_1-1].score[i] = change_4;
            stud[change_1-1].ave = stud[change_1-1].sum = 0;
            for(j=0;j<subjects;j++)
                stud[change_1-1].sum = stud[change_1-1].sum + stud[change_1-1].score[j];
            stud[change_1-1].ave = stud[change_1-1].sum / subjects;
            break;
        }
}

int search_subject()//按照科目名称返回科目序号
{
    int i;
    char sub_name[100];
    while (1)
    {
        printf("请输入您要查询的科目的名称：");
        scanf("%s",sub_name);
        interval();
        for(i=0;i<20;i++)
            if(strcmp(subject_name[i],sub_name)==0)//对比科目名称
                return i;//返回科目序号
        if(i==20)
        {
            printf("您的输入有误！\n");
            interval();
        }
    }

}

void reset_print_order(int a[])//复原输出顺序  a[i]是打印顺序
{
    int i;
    for(i=0;i<100;i++)
        a[i] = i;
}

void sort(int i,int a[])// 按照科目排序，按照i方式，更改打印顺序a[]
{
    int j,k,temp;
    if (i>=0)//i>=0时，按照科目序号i更改打印顺序
        for(k=0;k<students-1;k++)
            for(j=0;j<students-1-k;j++)//冒泡排序
                if(stud[a[j]].score[i] < stud[a[j+1]].score[i])
                {
                    temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;
                }
    if (i==-1)//i==-1时，按照总分更改打印顺序
        for(k=0;k<students-1;k++)
            for(j=0;j<students-1-k;j++)//冒泡排序
                if(stud[a[j]].sum< stud[a[j+1]].sum)
                {
                    temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;
                }
    if (i==-2)//i==-2时，按照学号更改打印顺序
        for(k=0;k<students-1;k++)
            for(j=0;j<students-1-k;j++)//冒泡排序
                if(strcmp(stud[a[j]].no,stud[a[j+1]].no) > 0)
                {
                    temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;
                }
    if (i==-3)//i==-3时，按照姓名更改打印顺序
        for(k=0;k<students-1;k++)
            for(j=0;j<students-1-k;j++)//冒泡排序
                if(strcmp(stud[a[j]].name,stud[a[j+1]].name) > 0)
                {
                    temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;
                }
}

int search_stu_no_name(int k)//按照学号或姓名查询 ，返回个人的序号
{
    int i,j;
    char stu_n[100];
    while(1)//循环
    {
        if (k==1)//k==1时，按照学号查询
            printf("请输入您要查询的个人的学号：");
        if (k==2)//k==2时，按照姓名查询
            printf("请输入您要查询的个人的姓名：");
        scanf("%s",stu_n);
        interval();
        if (k==1)
            for(i=0;i<students;i++)
                if(strcmp(stud[i].no,stu_n)==0)
                    return i;//返回个人序号
        if (k==2)
            for(i=0;i<students;i++)
                if(strcmp(stud[i].name,stu_n)==0)
                    return i;//返回个人序号
        if(i==students)
        {
            printf("您的输入有误！\n");
            interval();
        }
    }
}

float search_highest(int i)//寻找i方式的最大值
{
    int j;
    float max=0;
    if (i==-1)//i==1，寻找总分最大值
        for(j=0;j<students;j++)
            if(stud[j].sum > max)
                max = stud[j].sum;
    if (i==-2)//i==-2，寻找均分最大值
        for(j=0;j<students;j++)
            if(stud[j].ave > max)
                max = stud[j].ave;
    if (i>=0) //i>=0，寻找科目i的最大值
        for(j=0;j<students;j++)
            if(stud[j].score[i] > max)
                max = stud[j].score[i];
    return max;
}

float search_lowest(int i)//寻找i方式的最小值
{
    int j;
    float min=99999;
    if (i==-1)//i==1，寻找总分最小值
        for(j=0;j<students;j++)
            if(stud[j].sum < min)
                min = stud[j].sum;
    if (i==-2)//i==-2，寻找均分最小值
        for(j=0;j<students;j++)
            if(stud[j].ave < min)
                min = stud[j].ave;
    if(i>=0)//i>=0，寻找科目i的最小值
        for(j=0;j<students;j++)
            if(stud[j].score[i] < min)
                min = stud[j].score[i];
    return min;
}

void output_certain(float a,float c,int i)//以i方式输出指定区域内a-c之间的学生成绩
{
    int j;
    if (i==-1)//i==-1，按总分输出
        for(j=0;j<students;j++)
            if(stud[j].sum >= a  &&  stud[j].sum <= c)//满足条件的学生全部输出
                output_score(j);
    if (i==-2)// i==-2，按平均分输出
        for(j=0;j<students;j++)
            if(stud[j].ave >= a  &&  stud[j].ave <= c)//满足条件的学生全部输出
                output_score(j);
    if (i>=0)// i==-3，按照科目i输出
        for(j=0;j<students;j++)
            if(stud[j].score[i] >= a  &&  stud[j].score[i] <= c)//满足条件的学生全部输出
                output_score(j);
}

float search_ave(int i)//以i方式计算平均分
{
    int j;
    float ave,sum=0;
    if (i==-1)//i==-1，按总分计算
        for(j=0;j<students;j++)
            sum = sum + stud[j].sum;
    if (i==-2)// i==-2，按平均分计算
        for(j=0;j<students;j++)
            sum = sum + stud[j].ave;
    if (i>=0)// i==-3，按照科目i计算
        for(j=0;j<students;j++)
            sum = sum + stud[j].score[i];
    ave = sum / (students * 1.0);
    return ave;
}

#endif //STUDENTSCORESYSTEM_FUNCTIONS_H
