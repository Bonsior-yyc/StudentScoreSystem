//
// Created by 颜聿辰 on 2019/12/18.
//

#ifndef STUDENTSCORESYSTEM_STRUCTS_H
#define STUDENTSCORESYSTEM_STRUCTS_H

#include <stdio.h>

typedef  struct student				//创建学生成绩结构体
{
    int num;						//序号
    char no[100];					//学号
    char name[100];					//姓名
    float score[100];				//各科成绩
    float sum;						//总分
    float ave;						//平均分
}ss;

ss stud[100];						//学生信息数组
int students,subjects;				//学生数，科目数
char subject_name[20][100];			//科目名
#endif //STUDENTSCORESYSTEM_STRUCTS_H
