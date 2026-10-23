#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

static void pvH(Node* cur, Node*& sm, Node*& lg, int pv)
{
    if (cur == NULL) {
        sm = NULL;
        lg = NULL;
        return;
    }
    Node* rest = cur->next;
    pvH(rest, sm, lg, pv);
 
    if (cur->val <= pv) {
        cur->next = sm;
        sm = cur;
    }
    else {
        cur->next = lg;
        lg = cur;
    }
}
 
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
    pvH(head, smaller, larger, pivot);
    head = NULL;   
}