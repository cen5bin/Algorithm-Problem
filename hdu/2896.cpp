#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;


const int kind = 128;  //字母数量
const int MAX_SIZE = 50010; //节点最大数
const int KEYWORD_MAX_LEN = 210; //单词最大长度
const int INPUT_MAX_LEN = 10010; //输入的字符串的最大长度


struct node
{
     node *fail;
     node *next[kind];
     int count;
     int flag;
     void init()
     {
     	flag = 0;
        fail = NULL;
        memset(next, 0, sizeof(next));
        count = 0;
     }
}*q[MAX_SIZE], pool[MAX_SIZE], *root; //该数组用于构建fail指针时的广搜队列

int pos; //池子中当前的下标

char keyword[KEYWORD_MAX_LEN];
char s[INPUT_MAX_LEN];
int head, tail;

int flag;

void insert(char *s, node *root)
{
     node *p = root;
     int i = 0;
     while (s[i])
     {
          int index = s[i] - 'a';
          if (p->next[index] == NULL)
          {
               p->next[index] = &pool[pos++];
               p->next[index]->init();
          }
          p = p->next[index];
          i++;
     }
     p->count = flag;
     // printf("%d\n", flag);
}

void build_ac_automation(node *root)
{    
     head = tail = 0;
     root->fail = NULL;
     q[tail++] = root;
     while (head != tail)
     {
          node *tmp = q[head++];
          for (int i = 0; i < kind; i++)
          if (tmp->next[i] != NULL)
          {
               if (tmp == root) tmp->next[i]->fail = root;
               else
               {
                    node *p = tmp->fail;
                    while (p != NULL)
                    {
                         if (p->next[i] != NULL)
                         {
                              tmp->next[i]->fail = p->next[i];
                              break;
                         }
                         p = p->fail;
                    }
                    if (p == NULL)
                         tmp->next[i]->fail = root;
               }
               q[tail++] = tmp->next[i];
          }
     }
}

std::vector<int> v;

int query(char *s, node *root)
{
     node *p = root;
     int ret = 0;
     int i = 0;
     while (s[i])
     {
          int index = s[i] - 'a';
          while (p->next[index] == NULL && p != root) p = p->fail;
          p = p->next[index];
          if (p == NULL) p = root;
          if (p != root)
          {
               node *tmp = p;
               while (tmp != root && tmp->flag != flag)
               {
               	// printf("asdsda\n"
	               	if (tmp->count)
	               	{
	               		v.push_back(tmp->count);
	                    ret += tmp->count;
	                    tmp->flag = flag;
	                }
                    tmp = tmp->fail;
               }
          }
          i++;
     }
     return ret;
}


int main()
{
	int n, m;
	scanf("%d", &n);
	root = &pool[0];
	root->init();
	pos = 1;
	for (flag = 1; flag <=n; flag++)
	{
		char s0[210];
		scanf("%s", s0);
		insert(s0, root);
	}
	build_ac_automation(root);
	scanf("%d", &m);
	int tol = 0;
	for (flag = 1; flag <= m; flag++)
	{
		scanf("%s", s);
		query(s, root);
		// printf("%d\n", ret);
		int size = v.size();
		if (size == 0) continue;
		printf("web %d:", flag);
		sort(v.begin(), v.end());
		for (int i = 0; i < size; i++)
			printf(" %d", v[i]);
		puts("");
		tol++;
		v.clear();
	}
	printf("total: %d\n", tol);


	return 0;
}