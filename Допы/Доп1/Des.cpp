#include <iostream>
#include <numeric>
#include <stdexcept>
#include <initializer_list>

template<typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value, Node* nextNode = nullptr)
            : data(value), next(nextNode) {}
    };

    Node* head;
    Node* tail;
    size_t listSize;

    void init() {
        head = new Node(T());
        tail = head;
        listSize = 0;
    }

public:
    SinglyLinkedList() {
        init();
    }

    SinglyLinkedList(std::initializer_list<T> initList) {
        init();
        for (const T& value : initList) {
            push_back(value);
        }
    }

    ~SinglyLinkedList() {
        clear();
        delete head;
    }

    void push_back(const T& value) {
        tail->next = new Node(value, nullptr);
        tail = tail->next;
        listSize++;
    }

    void push_front(const T& value) {
        head->next = new Node(value, head->next);
        if (listSize == 0) {
            tail = head->next;
        }
        listSize++;
    }

    void insert(size_t idx, const T& value) {
        if (idx > listSize) throw std::out_of_range("Индекс вне диапазона");

        Node* current = head;
        for (size_t i = 0; i < idx; ++i) {
            current = current->next;
        }
        current->next = new Node(value, current->next);
        if (current->next->next == nullptr) {
            tail = current->next;
        }
        listSize++;
    }

    void pop_back() {
        if (listSize == 0) return;

        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
        listSize--;
    }

    void pop_front() {
        if (listSize == 0) return;

        Node* toDelete = head->next;
        head->next = head->next->next;
        delete toDelete;
        if (listSize == 1) {
            tail = head;
        }
        listSize--;
    }

    void remove_at(size_t idx) {
        if (idx >= listSize) throw std::out_of_range("Индекс вне диапазона");

        Node* current = head;
        for (size_t i = 0; i < idx; ++i) {
            current = current->next;
        }
        Node* toDelete = current->next;
        current->next = current->next->next;
        if (current->next == nullptr) {
            tail = current;
        }
        delete toDelete;
        listSize--;
    }

    T& operator[](size_t idx) {
        if (idx >= listSize) throw std::out_of_range("Индекс вне диапазона");

        Node* current = head->next;
        for (size_t i = 0; i < idx; ++i) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](size_t idx) const {
        if (idx >= listSize) throw std::out_of_range("Индекс вне диапазона");

        Node* current = head->next;
        for (size_t i = 0; i < idx; ++i) {
            current = current->next;
        }
        return current->data;
    }

    size_t size() const {
        return listSize;
    }

    bool empty() const {
        return listSize == 0;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    T front() const {
        if (empty()) throw std::out_of_range("Список пуст");
        return head->next->data;
    }

    T back() const {
        if (empty()) throw std::out_of_range("Список пуст");
        return tail->data;
    }

    class ListIterator {
    private:
        Node* currentNode;

    public:
        ListIterator(Node* node) : currentNode(node) {}

        T& operator*() {
            return currentNode->data;
        }

        ListIterator& operator++() {
            currentNode = currentNode->next;
            return *this;
        }

        bool operator!=(const ListIterator& other) const {
            return currentNode != other.currentNode;
        }
    };

    ListIterator begin() {
        return ListIterator(head->next);
    }

    ListIterator end() {
        return ListIterator(nullptr);
    }
};

// Тестирование реализации
int main() {
    SinglyLinkedList<int> l = { 3, 5, 2, 7, 8 };
    int s = 0;
    for (auto& i : l) s += i * 10;
    auto lambda = [](int a, int b) { return a + b * 10; };
    std::cout << s << '\t' << std::accumulate(l.begin(), l.end(), 0, lambda) << '\n';

    return 0;
}
