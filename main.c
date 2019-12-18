#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "structs.h"
#include "FileRelated.h"
#include "config.h"


int main() {
    int func,funct,loop_1=1,loop_2=1,change_1,i,print_order[100],choice;
    char change_2[20];
    float max,min,ave,top,btm;
    FILE *fp1,*fp2,*fp;
    char filename_1[10][200];
    char filename_2[10][200];
    for (int j = 0; j < 10; j++) {
        sprintf(filename_1[j],"%s%s",location,file_1[j]);
        printf("%s    ",filename_1[j]);
        sprintf(filename_2[j],"%s%s",location,file_2[j]);
    }

    welcome_1();//首页欢迎语

    while(loop_1){//控制循环
        printf("欢迎进入成绩录入系统！\n");
        printf("1.新建成绩存档\n");
        printf("2.修改成绩存档\n");
        printf("3.打开文件存档\n");
        printf("请选择功能并输入相应序号：");
        scanf("%d",&func);
        switch (func)
        {
            case 1://1.新建成绩存档
                for (i=0;i<10;i++)
                    if ((fp1 = fopen (filename_1[i],"rb")) == NULL)
                        break;
                fp1 = openfile_wb(filename_1[i]);//fp1是成绩数据
                fp2 = openfile_wb(filename_2[i]);//fp2是科目名数据
                scan_stu_sub_number();//输入学生和科目数目
                interval();
                scan_sub_name();//输入科目名
                for(i=0;i<students;i++)//输入成绩单
                {
                    interval();
                    scan_scores(i);
                }
                save_file_1(fp1);//保存文件 1
                fclose(fp1);
                save_file_2(fp2);//保存文件 2
                fclose(fp2);
                break;
            case 2://2.修改成绩存档
                printf("已经存在的成绩存档有：\n");
                for(i=0;i<10;i++)
                {
                    if((fp = fopen(filename_1[i],"rb")) == NULL)//循环控制显示所有文件名
                        break;
                    printf("%d.%s\n",i+1,filename_1[i]);
                    fclose(fp);
                }//寻找所有文件
                printf("请输入您要打开的成绩存档编号：");//选择文件打开
                scanf("%d",&choice);
                fp = openfile_rb(filename_1[choice-1]);//rb方式打开文件
                students = subjects = 0;
                read_file_1(fp);//读取成绩数据
                fclose(fp);
                fp = openfile_rb(filename_2[choice-1]);//rb方式打开文件
                read_file_2(fp);//读取科目名数据
                fclose(fp);
                if(students != 0 && subjects !=0 )
                    printf("文件打开成功！\n");
                interval();
                printf("1.修改学生信息。\n");
                printf("2.添加学生信息。\n");
                printf("请输入您要实现的功能：");
                scanf("%d",&func);
                interval();
                switch (func)
                {
                    case 1://1.修改学生信息。
                        title();
                        for(i=0;i<students;i++)
                            output_score(i);//输出成绩单
                        interval();
                        printf("请输入您要修改的学生编号：");//以下都为成绩修改
                        scanf("%d",&change_1);
                        printf("请输入您要修改的项目：");
                        scanf("%s",change_2);
                        change_information(change_1,change_2);//更改信息
                        fp = openfile_wb(filename_1[choice-1]);//打开文件
                        save_file_1(fp); //保存修改的成绩数据
                        fclose(fp);//关闭文件
                        break;
                    case 2://2.添加学生信息。
                        scan_scores(students);//输入新信息
                        students++;//计数
                        fp = openfile_wb(filename_1[choice-1]);//打开文件
                        save_file_1(fp); //保存修改的成绩数据
                        fclose(fp);//关闭文件
                        break;
                    default: printf("您的输入有误！\n");
                }
                break;
            case 3:
                printf("已经存在的成绩存档有：\n");
                for(i=0;i<10;i++)
                {
                    if((fp = fopen(filename_1[i],"rb")) == NULL)//循环控制显示所有文件名
                        break;
                    printf("%d.%s\n",i+1,filename_1[i]);
                    fclose(fp);
                }//3.打开文件存档
                printf("请输入您要打开的成绩存档编号：");//选择文件打开
                scanf("%d",&choice);
                interval();
                fp1 = openfile_rb(filename_1[choice-1]);//fp1 是成绩数据
                read_file_1(fp1);//读取成绩
                fclose(fp1);
                fp2 = openfile_rb(filename_2[choice-1]);//fp2是科目名数据
                read_file_2(fp2);//读取科目名
                fclose(fp2);
                if(students != 0 && subjects !=0 )
                    printf("文件打开成功！\n");
                loop_1=0;
                break;
            default: printf("您的输入有误！\n");
        }
    }
    while(loop_2)
    {//控制循环
        system("cls");
        printf("欢迎进入成绩查询系统！\n");//一级菜单选项
        printf("1.打印成绩单。\n");
        printf("2.查询个人成绩。\n");
        printf("3.根据科目查询。\n");
        printf("4.根据总分查询。\n");
        printf("5.根据平均分查询。\n");
        printf("6.退出。\n");
        printf("请选择功能并输入相应序号：");
        scanf("%d",&func);
        switch(func){
            case 1://1.打印成绩单。
                printf("欢迎进入成绩单打印系统！\n");
                printf("1.按照序号打印。\n");
                printf("2.按照科目打印。\n");
                printf("3.按照总分和平均分打印。\n");
                printf("4.按照学号打印。\n");
                printf("5.按照姓名打印。\n");
                printf("请选择功能并输入相应序号：");
                scanf("%d",&funct);
                interval();
                switch(funct)
                {
                    case 1:
                        reset_print_order(print_order);//复位打印顺序
                        title();//抬头
                        output_score_order(print_order);//按照print_order顺序打印所有成绩
                        break;
                    case 2:
                        i = search_subject();//i为输入的科目的序号
                        reset_print_order(print_order);//复位打印顺序
                        sort(i,print_order);//按照科目i更改打印顺序
                        printf("成绩按照 %6s 科目的成绩排序为：\n",subject_name[i]);
                        title();//抬头
                        output_score_order(print_order);//按照print_order顺序打印所有成绩
                        break;
                    case 3:
                        reset_print_order(print_order);//复位打印顺序
                        sort(-1,print_order);//按照总分更改打印顺序
                        printf("成绩按照总分或平均分排序为：\n");
                        title();//抬头
                        output_score_order(print_order);//按照print_order顺序打印所有成绩
                        break;
                    case 4:
                        reset_print_order(print_order);//复位打印顺序
                        sort(-2,print_order);//按照总分更改打印顺序
                        printf("成绩按照学号排序为：\n");
                        title();//抬头
                        output_score_order(print_order);//按照print_order顺序打印所有成绩
                        break;
                    case 5:
                        reset_print_order(print_order);//复位打印顺序
                        sort(-3,print_order);//按照姓名更改打印顺序
                        printf("成绩按照姓名排序为：\n");
                        title();//抬头
                        output_score_order(print_order);//按照print_order顺序打印所有成绩
                        break;
                    default: printf("您的输入有误！\n");
                }
                break;
            case 2:
                printf("欢迎进入个人成绩查询系统！\n");
                printf("1.按照学号查询。\n");
                printf("2.按照姓名查询。\n");
                printf("请选择功能并输入相应序号：");
                scanf("%d",&funct);
                switch(funct)
                {
                    case 1:
                        i = search_stu_no_name(1);//将所输入的学号对应的学生序号赋值给i
                        printf("对应学生的成绩为：\n");
                        title();//抬头
                        output_score(i);//打印同学i的全部成绩
                        break;
                    case 2:
                        i = search_stu_no_name(2);//将所输入的姓名对应的学生序号赋值给i
                        printf("对应学生的成绩为：\n");
                        title();//抬头
                        output_score(i);//打印同学i的全部成绩
                        break;
                    default: printf("您的输入有误！\n");
                }
                break;
            case 3:
                printf("欢迎进入科目查询系统！\n");
                printf("1.查询单科最高分。\n");
                printf("2.查询单科最低分。\n");
                printf("3.查询单科平均分。\n");
                printf("4.输入科目与成绩查询。\n");
                printf("请选择功能并输入相应序号：");
                scanf("%d",&funct);
                switch(funct)
                {
                    case 1:
                        i = search_subject();//i为输入的科目的序号
                        max = search_highest(i);//max为科目i的最高分
                        printf("科目 %6s 的最高分是%f\n",subject_name[i],max);
                        printf("对应人员：\n");
                        title();//抬头
                        output_certain(max,max,i);//打印科目i成绩为max的同学的成绩
                        break;
                    case 2:
                        i = search_subject();//i为输入的科目的序号
                        min = search_lowest(i);//min为科目i的最低分
                        printf("科目 %6s 的最低分是%f\n",subject_name[i],min);
                        printf("对应人员：\n");
                        title();//抬头
                        output_certain(min,min,i);//打印科目i成绩为min的同学的成绩
                        break;
                    case 3:
                        i = search_subject();//i为输入的科目的序号
                        ave = search_ave(i);//求科目i的均分
                        printf("科目 %6s 的平均分是%f\n",subject_name[i],ave);
                        break;
                    case 4:
                        i = search_subject();//i为输入的科目的序号
                        max = search_highest(i);//max为科目i的最高分
                        min = search_lowest(i);//min为科目i的最低分
                        printf("请输入不高于最高分%f的分数上限：",max);
                        scanf("%f",&top);//输入上限
                        printf("请输入不低于最低分%f的分数下限：",min);
                        scanf("%f",&btm);	//输入下限
                        interval();
                        printf("如下人员符合要求：\n");
                        title();//抬头
                        output_certain(btm,top,i);//打印科目i成绩大于等于btm切小于等于top的同学的成绩
                        break;
                    default: printf("您的输入有误！\n");
                }
                break;
            case 4:
                printf("欢迎进入总分查询系统！\n");
                printf("1.查询总分最高分。\n");
                printf("2.查询总分最低分。\n");
                printf("3.查询总分平均分。\n");
                printf("4.输入总分查询。\n");
                printf("请选择功能并输入相应序号：");
                scanf("%d",&funct);
                switch (funct)
                {
                    case 1:
                        max = search_highest(-1);//max为总分的最高分
                        printf("总分最高分是%f\n",max);
                        printf("对应人员：\n");
                        title();//抬头
                        output_certain(max,max,-1);//打印总分为max的同学的成绩
                        break;
                    case 2:
                        min = search_lowest(-1);//min为总分的最低分
                        printf("总分最低分是%f\n",max);
                        printf("对应人员：\n");
                        title();//抬头
                        output_certain(min,min,-1);//打印总分为min的同学的成绩
                        break;
                    case 3:
                        ave = search_ave(-1);//求总分的均分
                        interval();
                        printf("总分平均分是%f\n",ave);
                        break;
                    case 4:
                        max = search_highest(-1);//max为总分的最高分
                        min = search_lowest(-1);//min为总分的最低分
                        printf("请输入不高于总分%f的分数上限：",max);
                        scanf("%f",&top);//输入上限
                        printf("请输入不低于总分%f的分数下限：",min);
                        scanf("%f",&btm);	//输入下限
                        interval();
                        printf("如下人员符合要求：\n");
                        title();//抬头
                        output_certain(btm,top,-1);//打印总分大于等于btm切小于等于top的同学的成绩
                        break;
                    default: printf("您的输入有误！\n");
                }
                break;
            case 5:
                printf("欢迎进入均分查询系统！\n");
                printf("1.查询均分最高分。\n");
                printf("2.查询均分最低分。\n");
                printf("3.查询均分平均分。\n");
                printf("4.输入均分查询。\n");
                printf("请选择功能并输入相应序号：");
                scanf("%d",&funct);
                switch (funct)
                {
                    case 1:
                        max = search_highest(-2);//max为均分的最高分
                        printf("平均分最高分是%f\n",max);
                        printf("对应人员：\n");
                        title();//抬头
                        output_certain(max,max,-2);//打印均分为max的同学的成绩
                        break;
                    case 2:
                        min = search_lowest(-2);
                        printf("平均分最低分是%f\n",min);//min为均分的最低分
                        printf("对应人员：\n");
                        title();//抬头
                        output_certain(min,min,-2);//打印均分为min的同学的成绩
                        break;
                    case 3:
                        ave = search_ave(-2);//求均分的均分
                        interval();
                        printf("均分平均分是%f\n",ave);
                        break;
                    case 4:
                        max = search_highest(-2);//max为均分的最高分
                        min = search_lowest(-2);//min为均分的最低分
                        printf("请输入不高于平均分%f的分数上限：",max);
                        scanf("%f",&top);//输入上限
                        printf("请输入不低于平均分%f的分数下限：",min);
                        scanf("%f",&btm);//输入下限
                        interval();
                        printf("如下人员符合要求：\n");
                        title();//抬头
                        output_certain(btm,top,-2);//打印平均分于等于btm切小于等于top的同学的成绩
                        break;
                    default: printf("您的输入有误！\n");system("pause");
                }
                break;
            case 6:
                loop_2=0;//跳出循环
                printf("\n");
                printf("感谢您的使用！再见！\n");
                break;
            default: printf("您的输入有误！\n");system("pause");
        }
    }
    return 0;
}
