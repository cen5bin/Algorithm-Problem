
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
	ListNode *getMid(ListNode *start) {
		ListNode *tmp1 = start;
		ListNode *tmp2 = start;
		while (tmp2 != NULL) {
			tmp2 = tmp2->next;
			if (tmp2) tmp2 = tmp2->next;
			if (tmp2 == NULL) break;
			tmp1 = tmp1->next;
		}
		return tmp1;
	}
	
	ListNode *merge(ListNode *p1, ListNode *p2) {
		ListNode tmp(0);
		ListNode *head = &tmp;
		ListNode *p = head;
		while (p1 && p2) {
			if (p1->val < p2->val) {
				p->next = p1;
				p1 = p1->next;
			}
			else {
				p->next = p2;
				p2 = p2->next;
			}
			p = p->next;
		}
		while (p1) {
			p->next = p1;
			p = p->next;
			p1 = p1->next;
		}
		while (p2) {
			p->next = p2;
			p = p->next;
			p2 = p2->next;
		}
		return head->next;
	}

    ListNode *sort(ListNode *start) {
		if (start->next == NULL) return start;
		ListNode *mid = getMid(start);
		ListNode *p = mid->next;
		mid->next = NULL;
		ListNode *tmp1 = sort(start);
		ListNode *tmp2 = sort(p);
		return merge(tmp1, tmp2);
    }
public:
    ListNode *sortList(ListNode *head) {
        if (head == NULL) return NULL;
        return sort(head);
        
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
