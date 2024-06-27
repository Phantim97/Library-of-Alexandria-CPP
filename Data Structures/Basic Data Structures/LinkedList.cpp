#include <iostream>
#include <type_traits>

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
class ListNode
{
public:
    T data;
    ListNode* next;

    ListNode(int data)
    {
        this->data = data;
        this->next = nullptr;
    }

    void insert(int data)
    {
        ListNode* node = new ListNode(data);
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

    void remove(int data)
    {
        ListNode* curr = this;
        ListNode* prev = nullptr;
        while (curr != nullptr)
        {
            if (curr->data == data)
            {
                if (prev == nullptr)
                {
                    this->data = curr->next->data;
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

    ListNode* nth(int n)
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
