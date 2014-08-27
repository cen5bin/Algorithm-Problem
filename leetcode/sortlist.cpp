/*
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 **/
#include <cstdio>
#include <cstring>

  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
class Solution {
    inline void swap(int &a, int &b) {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }
    ListNode *sort(ListNode *start, ListNode *end) {
        ListNode *p = start;
        if (p->next == end) return p;
        if (p->val > p->next->val) swap(p->val, p->next->val);
        if (p->next->next == end) return p;
        if (p->next->next->val < p->next->val) swap(p->next->val, p->next->next->val);
        if (p->val > p->next->val) swap(p->val, p->next->val);
        ListNode *mid = p->next;
        p = p->next->next;
        while(p && p->next != end) {
            if (p->next->val < mid->val) {
                ListNode *tmp = p->next;
                p->next = tmp->next;
                tmp->next = start->next;
                start->next = tmp;
            }
			else
            p = p->next;
        }
        ListNode *tmp1 = sort(start, mid);
        ListNode *tmp2 = sort(mid->next, end);
        mid->next = tmp2;
        return start;
    }
public:
    ListNode *sortList(ListNode *head) {
        if (head == NULL) return NULL;
        return sort(head, NULL);
        
    }
};
int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		ListNode *head = new ListNode(0);
		ListNode *p = head;
		for (int i = 0; i < n; i++)
		{
			int x;
			scanf("%d", &x);
			p->val = x;
			if (i != n-1)
			p->next = new ListNode(0);
			p = p->next;
		}
		Solution solution;
		head = solution.sortList(head);
		p = head;
		while (p)
		{
			printf("%d ", p->val);
			ListNode *tmp = p;
			p = p->next;
			delete tmp;
		}
		puts("");
	}

	return 0;
}
