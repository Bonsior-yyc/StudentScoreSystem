//
// Created by 颜聿辰 on 2019/12/18.
//

#ifndef STUDENTSCORESYSTEM_FILERELATED_H
#define STUDENTSCORESYSTEM_FILERELATED_H

#include <stdio.h>
#include <stdlib.h>




char file_1[10][200]={"/data/score1.dat","/data/score2.dat","/data/score3.dat","/data/score4.dat","/data/score5.dat","/data/score6.dat","/data/score7.dat","/data/score8.dat","/data/score9.dat","/data/score10.dat"} ;//成绩文件备选名
char file_2[10][200]={"/data/text1.dat","/data/text2.dat","/data/text3.dat","/data/text4.dat","/data/text5.dat","/data/text6.dat","/data/text7.dat","/data/text8.dat","/data/text9.dat","/data/text10.dat"} ;//科目名称文件备选名
FILE* openfile_wb(char filename[])	//以wb方式打开filename的文件
{
    FILE* fp;
    if((fp = fopen(filename,"wb"))==NULL)
    {
        printf("文件建立失败！\n");
        exit(0);
    }
    return fp;
}

FILE* openfile_rb(char filename[])	//以rb方式打开filename的文件
{
    FILE* fp;
    if((fp = fopen(filename,"rb"))==NULL)
    {
        printf("文件打开失败！\n");
        exit(0);
    }
    return fp;
}

void save_file_1(FILE *fp1)	//数据保存1（保存成绩）
{
    int i;
    for(i=0;i<students;i++)
        if(fwrite(&stud[i],sizeof(ss),1,fp1) != 1)//二进制写入数据
            printf("数据写入失败！\n");
}

void save_file_2(FILE *fp2)//数据保存2  （保存科目名）
{
    int i;
    for(i=0;i<subjects;i++)
        if(fwrite(subject_name[i],sizeof(char [100]),1,fp2) != 1)//二进制写入数据
            printf("数据写入失败！\n");
}
void read_file_1(FILE *fp1)//读取数据1 （读取成绩）
{
    int i;
    students = 0;
    for(i=0;i<100;i++)
    {
        if(fread(&stud[i],sizeof(ss),1,fp1) != 1)//读取成绩
            break;
        students++;
    }
}

void read_file_2(FILE *fp2)//读取数据2 （读取科目名）
{
    int i;
    subjects = 0;
    for(i=0;i<100;i++)
    {
        if(fread(subject_name[i],sizeof(char [100]),1,fp2) != 1)//读取科目名
            break;
        subjects++;
    }
}


#endif //STUDENTSCORESYSTEM_FILERELATED_H
