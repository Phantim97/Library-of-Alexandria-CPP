#pragma once
#include <iostream>
#include <type_traits>

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
class ListNode
{
public:
    T data;
    ListNode* next;

    ListNode(const int n)
    {
        this->data = n;
        this->next = nullptr;
    }

    void insert(const int n)
    {
        ListNode* node = new ListNode(n);
        ListNode* curr = this;

		while (curr->next != nullptr)
        {
            curr = curr->next;
        }

        curr->next = node;
    }

    void print()
    {
        ListNode* curr = this;
        while (curr != nullptr)
        {
            std::cout << curr->data << ' ';
            curr = curr->next;
        }
        std::cout << '\n';
    }

    void remove(const int n)
    {
        ListNode* curr = this;
        ListNode* prev = nullptr;
        while (curr != nullptr)
        {
            if (curr->data == n)
            {
                if (prev == nullptr)
                {
                    this->data = curr->next->data_;
                    this->next = curr->next->next;
                }
                else
                {
                    prev->next = curr->next;
                }
                delete curr;
                return;
            }

            prev = curr;
            curr = curr->next;
        }
    }

    void reverse()
    {
        ListNode* curr = this;
        ListNode* prev = nullptr;
        ListNode* next_node = nullptr;

        while (curr != nullptr)
        {
            next_node = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next_node;
        }

        this->data = prev->data;
        this->next = prev->next;
    }

    int length()
    {
        ListNode* curr = this;
        int count = 0;

        while (curr != nullptr)
        {
            count++;
            curr = curr->next;
        }

        return count;
    }

    ListNode* middle()
    {
        ListNode* slow = this;
        ListNode* fast = this;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* nth(const int n)
    {
        ListNode* curr = this;
        int count = 0;
        while (curr != nullptr)
        {
            if (count == n)
            {
                return curr;
            }
            count++;
            curr = curr->next;
        }
        return nullptr;
    }

    ListNode* merge(ListNode* l1, ListNode* l2)
    {
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->data < l2->data)
            {
                curr->next = l1;
                l1 = l1->next;
            }
            else
            {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        if (l1 != nullptr)
        {
            curr->next = l1;
        }
        if (l2 != nullptr)
        {
            curr->next = l2;
        }
        return dummy->next;
    }
};
