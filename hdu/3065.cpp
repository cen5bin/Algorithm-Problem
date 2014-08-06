#include <cstdio>
#include <cstring>

const int kind = 128;  //字母数量
const int MAX_SIZE = 500010; //节点最大数
const int KEYWORD_MAX_LEN = 55; //单词最大长度
const int INPUT_MAX_LEN = 2000010; //输入的字符串的最大长度


struct node
{
     node *fail;
     node *next[kind];
     int count;
     void init()
     {
          fail = NULL;
          memset(next, 0, sizeof(next));
          count = 0;
     }
}*q[MAX_SIZE], pool[MAX_SIZE], *root; //该数组用于构建fail指针时的广搜队列

int pos; //池子中当前的下标

char keyword[KEYWORD_MAX_LEN];
char s[INPUT_MAX_LEN];
int head, tail;


void insert(char *s, node *root, int index)
{
     node *p = root;
     int i = 0;
     while (s[i])
     {
          int index = s[i];
          if (p->next[index] == NULL)
          {
               p->next[index] = &pool[pos++];
               p->next[index]->init();
          }
          p = p->next[index];
          i++;
     }
     p->count = index;
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

int ans[1010];

int query(char *s, node *root)
{
     node *p = root;
     int ret = 0;
     int i = 0;
     while (s[i])
     {
          int index = s[i];
          while (p->next[index] == NULL && p != root) p = p->fail;
          p = p->next[index];
          if (p == NULL) p = root;
          if (p != root)
          {
               node *tmp = p;
               while (tmp != root && tmp->count != -1)
               {
                    if (tmp->count > 0)
                         ans[tmp->count-1]++;
                    //ret += tmp->count;
                    //tmp->count = -1;
                    tmp = tmp->fail;
               }
          }
          i++;
     }
     return ret;
}

char ss[1010][55];
int main()
{

     int n;
     while (scanf("%d", &n) == 1)
     {
          root = &pool[0];
          root->init();
          pos = 1;
          for (int i = 0; i < n; i++)
          {
               scanf("%s", ss[i]);
               insert(ss[i], root, i + 1);
          }
          build_ac_automation(root);
          scanf("%s", s);
          memset(ans, 0, sizeof(ans));
          query(s, root);
          for (int i = 0; i < n; i++)
          if (ans[i])
               printf("%s: %d\n", ss[i], ans[i]);
     }
     return 0;
}