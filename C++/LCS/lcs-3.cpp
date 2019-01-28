// 获取全部最长公共子序列 迭代版
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1024
typedef int **Matrix;

/************定义Stack***************/
#define MAX_STACK_SIZE 1024
typedef struct _Element
{
    int nlcslen;
    int nrow;
    int ncolumn;
} Element;
typedef struct _Stack
{
    int top;
    Element data[MAX_STACK_SIZE];
} Stack;

bool IsFull(Stack *ps)
{
    if (ps != NULL)
        return (ps->top == MAX_STACK_SIZE) ? true : false;
    return true;
}
bool IsEmpty(Stack *ps)
{
    if (ps != NULL)
        return (ps->top >= 0) ? false : true;
    return false;
}
bool Push(Stack *ps, Element *pein)
{
    if (ps != NULL && pein != NULL)
    {
        if (IsFull(ps))
            return false;
        ps->top++;
        ps->data[ps->top].nlcslen = pein->nlcslen;
        ps->data[ps->top].nrow = pein->nrow;
        ps->data[ps->top].ncolumn = pein->ncolumn;
        return true;
    }
    return false;
}
bool Pop(Stack *ps, Element *peout)
{
    if (ps != NULL && peout != NULL)
    {
        if (IsEmpty(ps))
            return false;
        peout->nlcslen = ps->data[ps->top].nlcslen;
        peout->ncolumn = ps->data[ps->top].ncolumn;
        peout->nrow = ps->data[ps->top].nrow;
        ps->top--;
        return true;
    }
    return false;
}
void InitialStack(Stack *ps)
{
    if (ps != NULL)
        ps->top = -1;
}
bool GetTop(Stack *ps, Element *peout)
{
    if (ps != NULL && peout != NULL)
    {
        if (ps->top >= 0)
        {
            peout->nlcslen = ps->data[ps->top].nlcslen;
            peout->ncolumn = ps->data[ps->top].ncolumn;
            peout->nrow = ps->data[ps->top].nrow;
            return true;
        }
    }
    return false;
}
Element CreateElement(int nlen, int nrow, int ncol)
{
    Element ele;
    ele.nlcslen = nlen;
    ele.ncolumn = ncol;
    ele.nrow = nrow;
    return ele;
}
/************end***************/

void GetLCSLen(char *str1, char *str2, Matrix pc, Matrix pb, int nrow, int ncolumn)
{
    int i, j;
    /************initial the edge***************/
    for (i = 0; i < nrow; i++)
    {
        pc[i][0] = 0;
        pb[i][0] = 0;
    }
    for (j = 0; j < ncolumn; j++)
    {
        pc[0][j] = 0;
        pb[0][j] = 0;
    }
    /************DP*****************************/
    for (i = 1; i < nrow; i++)
    {
        for (j = 1; j < ncolumn; j++)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                pc[i][j] = pc[i - 1][j - 1] + 1; //由左上节点转移而来
                pb[i][j] = 1;                    //标记为1
            }
            else if (pc[i - 1][j] > pc[i][j - 1])
            {
                pc[i][j] = pc[i - 1][j]; //由上节点转移而来
                pb[i][j] = 2;            //标记为2
            }
            else if (pc[i - 1][j] < pc[i][j - 1])
            {
                pc[i][j] = pc[i][j - 1]; //由左节点转移而来
                pb[i][j] = 3;            //标记为2
            }
            else
            {
                pc[i][j] = pc[i][j - 1]; //由左节点或上节点转移而来
                pb[i][j] = 4;            //标记为4
            }
        }
    }
}
void TraceBack(char *str1, Matrix pb, int nrow, int ncolumn)
{
    int ntemp;
    if (str1 == NULL || pb == NULL)
        return;
    if (nrow == 0 || ncolumn == 0)
        return;
    ntemp = pb[nrow - 1][ncolumn - 1];
    switch (ntemp)
    {
    case 1:
        printf("locate:(%d,%d),%4c\n", nrow - 1, ncolumn - 1, str1[nrow - 2]); //打印公共字符，这里下标是nrow-2，因为矩阵的坐标值(i,j)比字符串的实际下标大1
        TraceBack(str1, pb, nrow - 1, ncolumn - 1);                            //向左上角递归
        break;
    case 2:
        TraceBack(str1, pb, nrow - 1, ncolumn); //向上方向递归
        break;
    case 3:
        TraceBack(str1, pb, nrow, ncolumn - 1); //向左方向递归
        break;
    default:
        break;
    }
}
Matrix GreateMatrix(int nrow, int ncolumn)
{
    Matrix p;
    int i;
    p = (Matrix)malloc(nrow * sizeof(int *));
    if (p == NULL)
        return NULL;
    for (i = 0; i < nrow; i++)
    {
        p[i] = (int *)malloc(ncolumn * sizeof(int));
    }
    return p;
}
void DeleteMatrix(Matrix p, int nrow, int ncolumn)
{
    int n;
    if (p != NULL && nrow > 0 && ncolumn > 0)
    {
        for (n = 0; n < nrow; n++)
        {
            free(p[n]);
        }
        free(p);
    }
}

void PrintStack(Stack *ps, char *str1, int len1)
{
    if (ps == NULL || str1 == NULL)
        return;
    int ntemp = ps->top;
    int index = -1;
    while ((index = ps->data[ntemp].nrow) <= len1)
    {
        ntemp--;
        printf("%2c", str1[index - 1]);
    }
    printf("\n");
}
void SearchE(Matrix pb, int curposx, int curposy, int *eposx, int *eposy, int ntype)
{
    switch (pb[curposx][curposy])
    {
    case 1:
        *eposx = curposx;
        *eposy = curposy;
        return;
    case 2:
        SearchE(pb, curposx - 1, curposy, eposx, eposy, ntype);
        break;
    case 3:
        SearchE(pb, curposx, curposy - 1, eposx, eposy, ntype);
        break;
    case 4:
        if (ntype == 0)
            SearchE(pb, curposx - 1, curposy, eposx, eposy, ntype); //搜索e1点，如过碰到分叉点，向上继续搜索
        else
            SearchE(pb, curposx, curposy - 1, eposx, eposy, ntype); //搜索e2点，如过碰到分叉点，向左继续搜索
        break;
    }
}
void TraceBack2(char *str1, Matrix pc, Matrix pb, int nrow, int ncolumn)
{
    if (str1 == NULL || pc == NULL || pb == NULL)
        return;

    Stack store, print;     //构造两个栈store，print
    Element storetop;       //store栈的栈顶节点
    Element element;        //临时变量
    Element virtualnode;    //虚拟节点
    int ntoplen;            //保存store栈顶节点的LCS长度
    int ex1, ey1, ex2, ey2; //矩形搜索的两个节点的坐标
    int i, j;

    InitialStack(&store); //初始化
    InitialStack(&print);
    virtualnode = CreateElement(pc[nrow - 1][ncolumn - 1] + 1, nrow, ncolumn);
    Push(&store, &virtualnode); //压入虚拟节点到store

    while (!IsEmpty(&store))
    {
        Pop(&store, &storetop);                          //从栈顶取出一个节点
        if (storetop.nrow == 1 || storetop.ncolumn == 1) //如果是边界节点
        {
            Push(&print, &storetop);
            PrintStack(&print, str1, nrow - 1); //打印print栈里面除虚拟节点之外的所有节点
            GetTop(&store, &element);
            ntoplen = element.nlcslen; //当前store的栈顶节点的LCS长度

            /**********弹出print栈中所有LCS长度小于等于ntoplen的节点**************/
            while (GetTop(&print, &element) && element.nlcslen <= ntoplen)
            {
                Pop(&print, &element);
            }
        }
        else
        {
            Push(&print, &storetop);
            SearchE(pb, storetop.nrow - 1, storetop.ncolumn - 1, &ex1, &ey1, 0);
            SearchE(pb, storetop.nrow - 1, storetop.ncolumn - 1, &ex2, &ey2, 1 /*also other value is ok*/);

            if (ex1 == ex2 && ey1 == ey2)
            {
                element = CreateElement(pc[ex1][ey1], ex1, ey1);
                Push(&store, &element); //压入store栈，回到步骤2
            }
            else
            {
                for (i = ey2; i <= ey1; i++)
                    for (j = ex1; j <= ex2; j++)
                    {
                        if (pb[i][j] == 1)
                        {
                            element = CreateElement(pc[i][j], i, j);
                            Push(&store, &element);
                        }
                    }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    char str1[MAX_LEN] = "ABCD";
    char str2[MAX_LEN] = "ACBD";
    // char str1[MAX_LEN] = "BADCDCBA";
    // char str2[MAX_LEN] = "ABCDCDAB";
    int str1len = strlen(str1);
    int str2len = strlen(str2);
    Matrix C = GreateMatrix(str1len + 1, str2len + 1); //因为边界元素的加入，矩阵行列币字符串长度多1
    Matrix B = GreateMatrix(str1len + 1, str2len + 1);

    printf("input string:\nstr1:%s\nstr2:%s\n", str1, str2);

    if (C == NULL || B == NULL)
        exit(1);
    printf("start to find the LCS.....\n");

    GetLCSLen(str1, str2, C, B, str1len + 1, str2len + 1);
    //TraceBack(str1, B, str1len+1, str2len+1);
    TraceBack2(str1, C, B, str1len + 1, str2len + 1);

    printf("\n**********over***********\n");

    /******test********/
    /*int i,j;
	for(i=0; i<str1len+1; i++)
	{
		for(j=0; j<str2len+1; j++)
		{
			printf("%4d(%d)",C[i][j], B[i][j]);
		}
		printf("\n");
	}*/
    /******end**********/

    DeleteMatrix(C, str1len + 1, str2len + 1);
    DeleteMatrix(B, str1len + 1, str2len + 1);
    system("pause");
    return 0;
}