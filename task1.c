#include <stdio.h>
#include <stdlib.h>
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

    //还要分配内存？(但明显，这里指针都退了一格)
    // struct student pStudent[numStudents];
    //怎么好像重复声明了
    //创建了没有？
    for (int i = 0;i < numStudents; i++){
        pStudents[i] = (struct student*)malloc(sizeof(struct student));
    }

    //内存分配完毕，定位文件头并写入结构体数组
    fseek(file, 0, SEEK_SET);

    // 逐行读取文件数据并将数据存储到结构体数组中
    while (fgets(buffer, sizeof(buffer), file) != NULL ) {
        sscanf(buffer, "%s %d %d", (*pStudent)[numStudents].name, & (*pStudent)[numStudents].stuNum, & (*pStudent)[numStudents].expGrade);
        numStudents++;
    }

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
//这是测试一下内存分配和输入搞得怎么样，用个print试一下———好像有问题：出现异常。Segmentation fault。
void printStudents(struct student* students, int numStudents) {
    printf("Student Information:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Student %d\n", i + 1);
        printf("Name: %s\n", students[i].name);
        printf("Student Number: %s\n", students[i].stuNum);
        printf("Examination Grade: %d\n", students[i].expGrade);
        printf("Half Grade: %d\n", students[i].halfGrade);
        printf("Grade: %d\n", students[i].Grade);
        printf("\n");
    }
}

int main() {
    int i;
    const char* filename = "test.txt"; // 更改为你的文件名
    struct student* students = NULL;
    int numStudents = ReadStudentInfo(filename, &students);
    
    if (numStudents == -1) {
        printf("Failed to open the file.\n");
        return -1;
    }

    printStudents(students, numStudents);

        //释放内存
    free(students);

    return 0;
}

/*
如何让gpt指出错误：

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