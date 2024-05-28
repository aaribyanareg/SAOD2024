#include <iostream>
#include <numeric>
#include <stdexcept>
#include <initializer_list>

// Интерфейс ILinkedList
template <typename T>
struct ILinkedList {
    virtual void push_back(const T& data) = 0;
    virtual void push_front(const T& data) = 0;
    virtual void pop_back() = 0;
    virtual void pop_front() = 0;
    virtual T front() const = 0;
    virtual T back() const = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual ~ILinkedList() {}
};

// Реализация класса LList, наследующего ILinkedList
template <typename T>
class LList : public ILinkedList<T> {
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
    LList() {
        init();
    }

    LList(std::initializer_list<T> initList) {
        init();
        for (const T& value : initList) {
            push_back(value);
        }
    }

    LList(const LList& other) {
        init();
        for (Node* current = other.head->next; current != nullptr; current = current->next) {
            push_back(current->data);
        }
    }

    ~LList() {
        clear();
        delete head;
    }

    void push_back(const T& value) override {
        tail->next = new Node(value, nullptr);
        tail = tail->next;
        listSize++;
    }

    void push_front(const T& value) override {
        head->next = new Node(value, head->next);
        if (listSize == 0) {
            tail = head->next;
        }
        listSize++;
    }

    void pop_back() override {
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

    void pop_front() override {
        if (listSize == 0) return;

        Node* toDelete = head->next;
        head->next = head->next->next;
        delete toDelete;
        if (listSize == 1) {
            tail = head;
        }
        listSize--;
    }

    T front() const override {
        if (empty()) throw std::out_of_range("Список пуст");
        return head->next->data;
    }

    T back() const override {
        if (empty()) throw std::out_of_range("Список пуст");
        return tail->data;
    }

    size_t size() const override {
        return listSize;
    }

    bool empty() const override {
        return listSize == 0;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
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

// Интерфейс IDeque
template <typename T>
struct IDeque {
    virtual void push_front(const T& data) = 0;
    virtual void push_back(const T& data) = 0;
    virtual void pop_front() = 0;
    virtual void pop_back() = 0;
    virtual T front() const = 0;
    virtual T back() const = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual ~IDeque() {}
};

// Реализация класса Deque, наследующего LList и IDeque
template <typename T>
class Deque : public LList<T>, public IDeque<T> {
public:
    Deque() : LList<T>() {}

    void push_front(const T& data) override {
        LList<T>::push_front(data);
    }

    void push_back(const T& data) override {
        LList<T>::push_back(data);
    }

    void pop_front() override {
        LList<T>::pop_front();
    }

    void pop_back() override {
        LList<T>::pop_back();
    }

    T front() const override {
        return LList<T>::front();
    }

    T back() const override {
        return LList<T>::back();
    }

    size_t size() const override {
        return LList<T>::size();
    }

    bool empty() const override {
        return LList<T>::empty();
    }
};

// Интерфейс IStack
template <typename T>
struct IStack {
    virtual void push(const T& data) = 0;
    virtual void pop() = 0;
    virtual T top() const = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual ~IStack() {}
};

// Реализация класса Stack, наследующего LList и IStack
template <typename T>
class Stack : public LList<T>, public IStack<T> {
public:
    Stack() : LList<T>() {}

    void push(const T& data) override {
        LList<T>::push_front(data);
    }

    void pop() override {
        LList<T>::pop_front();
    }

    T top() const override {
        return LList<T>::front();
    }

    size_t size() const override {
        return LList<T>::size();
    }

    bool empty() const override {
        return LList<T>::empty();
    }
};

// Тестирование реализации стека
int main() {
    Stack<char> st;
    st.push('a');
    st.push('b');
    st.push('c');

    std::cout << st.size() << std::endl;

    auto s = st; // использование конструктора копирования из LList

    while (!st.empty()) {
        std::cout << st.top() << '\t';
        st.pop();
    }
    std::cout << std::endl;
    std::cout << st.size() << '\t' << s.size()
        << '\t' << s.top() << std::endl;

    return 0;
}
