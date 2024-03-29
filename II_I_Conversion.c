#include <stdio.h>
#include <string.h>
#include <math.h>

/**
 * 需求——进制转换
 *
 * 转化时，最直接的思路就是先将该数转化为十进制数据，
 * 然后再由十进制转化成要求的进制数，最终的结果用栈结构存储（先进后出），
 * 这样最终显示给用户的是正常的数据。
 *
 * input——
 *
 * ds——(string)数组
 * solve——转换为十进制
 *
 * output——
 *
 *
 * **/

int top = -1;//top变量时刻表示栈顶元素所在位置

void push(char *a, char elem) {
    a[++top] = elem;
}

void pop(char *a) {
    if (top == -1) {
        return;
    }
    //输出时要按照正确的格式显示给用户
    if (a[top] >= 10) {
        printf("%c", a[top] + 55);
    } else {
        printf("%d", a[top]);
    }
    top--;
}

//将各进制数转换成十进制数  //数据  (原)进制位数-int
int scaleFun(char *data, int system) {
    int k = (int) strlen(data) - 1;
    int system_10_data = 0;
    int i;
    for (i = k; i >= 0; i--) {
        int temp;
        //罗马转数字
        if (data[i] >= 48 && data[i] <= 57) {
            temp = data[i] - 48;
        } else {
            //数字直接用
            temp = data[i] - 55;
        }
        system_10_data += temp * pow(system, k - i);
    }
    return system_10_data;
}

int main() {
    char data[100];

    printf("进制转换器，请输入原数据的进制（2-36）:");
    int system;
    scanf("%d", &system);
    getchar();
    printf("请输入要转换的数据：");
    scanf("%s", data);
    getchar();
    int system_10_data = scaleFun(data, system);


    printf("请输入转换后的数据的进制：");
    int newSystem;
    scanf("%d", &newSystem);

    getchar();
    while (system_10_data / newSystem) {
        push(data, system_10_data % newSystem);
        system_10_data /= newSystem;
    }
    push(data, system_10_data % newSystem);

    printf("转换后的结果为：\n");
    while (top != -1) {
        pop(data);
    }
}