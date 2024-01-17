#include <iostream>
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_session.hpp"

//list
struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {       
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

//test
TEST_CASE("Checking_for_adding_and_receiving_items","[Checking_for_adding_and_receiving_items]"){

    List A_list;

    //проверка функции PushBack
    SECTION("Checking the PushBack"){
        CHECK(A_list.Empty() == true);
        A_list.PushBack(12);
        A_list.PushBack(13);
        CHECK(A_list.Size() == 2);
        CHECK(A_list.PopBack() == 13);
        A_list.PushBack(14);
        A_list.PushBack(15);
        CHECK(A_list.Size() == 3);
        CHECK(A_list.PopBack() == 15);
    }

    //проверка функции PushFront
    SECTION("Checking the PushFront"){
        CHECK(A_list.Empty() == true);
        A_list.PushFront(12);
        A_list.PushFront(13);
        CHECK(A_list.Size() == 2);
        CHECK(A_list.PopFront() == 13);
        A_list.PushFront(14);
        A_list.PushFront(15);
        CHECK(A_list.Size() == 3);
        CHECK(A_list.PopFront() == 15);
    }

    //проверка функции PopBack (Пустой список)
    SECTION("PopBack (Empty List)"){
        A_list.Clear();
        CHECK(A_list.Empty() == true);
        CHECK_THROWS(A_list.PopBack());
    }

    //проверка функции PopFront (Пустой список)
    SECTION("PopFront (Empty List)"){
        A_list.Clear();
        CHECK(A_list.Empty() == true);
        CHECK_THROWS(A_list.PopFront());
    }


}

//main
int main(int argc, char* argv[]){
     return Catch::Session().run(argc, argv);
}