#pragma once
#include <iostream>
#include <type_traits>

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
struct ListNode
{
    T data;
    ListNode* next;

    ListNode(const T n)
    {
        data = n;
        next = nullptr;
    }

    void insert(const T n)
    {
        ListNode* node = new ListNode(n);
        ListNode* curr = this;

		while (curr->next != nullptr)
        {
            curr = curr->next;
        }

        curr->next = node;
    }

    void print() const
    {
        ListNode* curr = this;

        while (curr != nullptr)
        {
            std::cout << curr->data << ' ';
            curr = curr->next;
        }

        std::cout << '\n';
    }

    void remove(const T n)
    {
        ListNode* curr = this;
        ListNode* prev = nullptr;

        while (curr != nullptr)
        {
            if (curr->data == n)
            {
                if (prev == nullptr)
                {
                    data = curr->next->data;
                    next = curr->next->next;
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

        data = prev->data;
        next = prev->next;
    }

    int length() const
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

    ListNode* nth(const size_t n)
    {
        ListNode* curr = this;
        size_t count = 0;

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
