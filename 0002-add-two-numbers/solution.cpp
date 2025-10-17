#include "solution.h"

ListNode *addTwoNumbersHelper(ListNode *l1, ListNode *l2, ListNode *l3)
{
   if (l1 == nullptr && l2 == nullptr)
   {
      return nullptr;
   }

   else if (l1 == nullptr && l2 != nullptr)
   {
      int sum = l3->val + l2->val;
      if (sum / 10 != 0)
      {
         ListNode *l4 = new ListNode(1);
         l3->next = l4;
         l3->val = sum % 10;
         return addTwoNumbersHelper(l1, l2->next, l3->next);
      }
      else
      {
         if (l2->next == nullptr)
         {
            l3->next = nullptr;
            l3->val = sum;
            return addTwoNumbersHelper(l1, l2->next, l3->next);
         }
         ListNode *l4 = new ListNode();
         l3->next = l4;
         l3->val = sum;
         return addTwoNumbersHelper(l1, l2->next, l3->next);
         ;
      }
   }

   else if (l1 != nullptr && l2 == nullptr)
   {
      int sum = l3->val + l1->val;
      if (sum / 10 != 0)
      {
         ListNode *l4 = new ListNode(1);
         l3->next = l4;
         l3->val = sum % 10;
         return addTwoNumbersHelper(l1->next, l2, l3->next);
      }
      else
      {
         if (l1->next == nullptr)
         {
            l3->next = nullptr;
            l3->val = sum;
            return addTwoNumbersHelper(l1->next, l2, l3->next);
         }
         ListNode *l4 = new ListNode();
         l3->next = l4;
         l3->val = sum;
         return addTwoNumbersHelper(l1->next, l2, l3->next);
      }
   }
   else
   {
      int sum = l3->val + l1->val + l2->val;
      if (sum / 10 != 0)
      {
         ListNode *l4 = new ListNode(1);
         l3->next = l4;
         l3->val = sum % 10;
         return addTwoNumbersHelper(l1->next, l2->next, l3->next);
      }
      else
      {
         if (l1->next == nullptr && l2->next == nullptr)
         {
            l3->next = nullptr;
            l3->val = sum;
            return addTwoNumbersHelper(l1->next, l2->next, l3->next);
         }
         ListNode *l4 = new ListNode();
         l3->next = l4;
         l3->val = sum;
         return addTwoNumbersHelper(l1->next, l2->next, l3->next);
      }
   }
}

ListNode *Solution::addTwoNumbers(ListNode *l1, ListNode *l2)
{
   ListNode *l3 = new ListNode();
   addTwoNumbersHelper(l1, l2, l3);
   return l3;
}