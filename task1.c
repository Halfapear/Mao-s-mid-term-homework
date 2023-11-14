#include <stdio.h>
#include <stdlib.h>
//3. 编写函数从文件读入所有学生信息
//表示学生信息的结构
struct student {
    char name[100];
    char stuNum[50];
    int expGrade;
    int halfGrade;
    int Grade ;
};

//编写函数读入学生信息
//指针小白：filename是指向谁的 pStudent是指向谁的 接下来又指向谁
int ReadStudentInfo(const char* filename,struct student**pStudent){
    //打开文件及报错
    FILE *file;
    file = fopen("test.txt","r");
    if (file == NULL){
        return -1;
    }

    //从头到尾扫描。获取人数（因为一行一个人） ps：我还没用过呢
    //现在 人数 还在numStudents所指向的地址里（还没确认）
    //不过。。真的需要指针吗————我把指针删了
    int numStudents = 0;
    char buffer[256];
    while (fgets(buffer,sizeof(buffer),file)!= NULL){
        (numStudents)++;
    }


    //分配内存 根据人数动态分配给struct student*
    //QAQ怎么分配啊，指针玩不明白了
    //ps：没有验证分配失败（所以会不会失败）
    struct student ** pStudents = (struct student **)malloc (numStudents * sizeof(struct student*));
    //当使用malloc分配内存时，返回的是一个指向分配内存起始位置的指针
    //注意，这里pStudents已经创建了

    //还要分配内存？(但明显，这里指针都退了一格)
    // struct student pStudent[numStudents];
    //怎么好像重复声明了
    //创建了没有？
    for (int i = 0;i < numStudents; i++){
        pStudents[i] = (struct student*)malloc(sizeof(struct student));
    }
    //指针基础：p[i]=*(p+i)=a[?+i]
    //em静态内存分配和动态内存分配真有意思

    //内存分配完毕，定位文件头并写入结构体数组
    fseek(file, 0, SEEK_SET);

    // 逐行读取文件数据并将数据存储到结构体数组中
    while (fgets(buffer, sizeof(buffer), file) != NULL ) {
        sscanf(buffer, "%s %d %d", (*pStudent)[numStudents].name, & (*pStudent)[numStudents].stuNum, & (*pStudent)[numStudents].expGrade);
        numStudents++;
    }
    //(*pStudent)也可以写作pStudent->

    // //释放内存
    // for ( i=0 ;i < numStudents; i++ ){
    //     free(pStudents[i]);
    // }
    // //等一等，这里先别释放

    //关闭文件
    fclose(file);

    //这个是附加
    return numStudents;
}
//---------------------------------------------------------------------------------------------------

//4. 编写统计函数
//两个任务：1是算出一个学生的总成绩并扔回到结构体中；2是算出一个班的平均成绩
float Count (struct student pStu[],int num){
    float advGrades;
    int allsum = 0,advgrades=0;
    for (int i = 0; i < num; i++){
        pStu[i].Grade += pStu[i].expGrade + pStu[i].halfGrade;
        allsum += pStu[i].Grade;
    }
    advgrades = allsum / num;
    //等一等 还要保留一位小数
    return advgrades;
}

//5. 编写成绩整理函数

//6. 编写输出函数
void printfunc(){
    //自己写
}

//7. 编写 main 函数实现：
int main(){
    int i , numStudents;
    numStudents =ReadStudentInfo(const char* filename,struct student**pStudent);
    //还没填
    //嗯？输入在函数里。。那我怎么声明

    //释放内存
    for ( i=0 ;i < numStudents; i++ ){
        free(pStudents[i]);
    }
}

/*
如何让gpt指出错误(模板)：

是我哪里有错列出来这一段，然后给改进
比如,你指出（用你一般用的code黑框表示）      
//释放内存
free(pStudents);
应改为
//释放内存
free(students);
而不是把整个代码全部重新打一遍
有错你就列出这一段然后给出这一段的正确代码
*/