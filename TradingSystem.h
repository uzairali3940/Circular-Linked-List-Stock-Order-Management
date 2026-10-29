#ifndef TRADING_SYSTEM_H
#define TRADING_SYSTEM_H
#include <string>

// Existing priority queue retained.
struct OrderNode { int orderID; std::string investorName; std::string stockSymbol; std::string orderType; int quantity; int priority; OrderNode* next; };
class PriorityQueue {
private: OrderNode* front; OrderNode* rear; int count;
public: PriorityQueue(); void Add(OrderNode* order); OrderNode* Remove(); bool IsEmpty() const; bool IsNotEmpty() const; void PrintQueue() const; ~PriorityQueue();
};

// Existing general-purpose singly linked list retained for the original Lab 5 features.
struct OrderListNode { int orderID; std::string investorName; std::string stockSymbol; std::string orderType; int quantity; int priority; OrderListNode* next; };
class OrderList {
private: OrderListNode* head; int count; OrderListNode* GetNodeAt(int index) const; void Clear();
public: OrderList(); OrderList(const OrderList& other); OrderList& operator=(const OrderList& other); ~OrderList();
    void Insert(OrderListNode* order); OrderListNode* Remove(); void InsertAt(OrderListNode* order, int index); OrderListNode* RemoveAt(int index);
    bool Swap(int first, int second); void Sort(); void Reverse(); void Print() const; bool IsEmpty() const; bool IsNotEmpty() const; int Size() const;
};
OrderListNode* CreateOrder(const OrderNode& order);

// Lab 6 individual-project addition: circular order rotation for a live trading watchlist.
// The last order points back to the first; pivot is the tail node.
struct CircularOrderNode { int orderID; std::string investorName; std::string stockSymbol; std::string orderType; int quantity; int priority; CircularOrderNode* next; };
class CircularOrderList {
private:
    CircularOrderNode* pivot; CircularOrderNode* current; int count;
    CircularOrderNode* GetNodeAt(int index) const; int NormalizeIndex(int index) const;
    void Clear(); void SwapData(CircularOrderNode* a, CircularOrderNode* b);
public:
    CircularOrderList(); CircularOrderList(const CircularOrderList& other); CircularOrderList& operator=(const CircularOrderList& other); ~CircularOrderList();
    void Insert(CircularOrderNode* order); CircularOrderNode* Remove();
    void InsertAt(CircularOrderNode* order, int index); CircularOrderNode* RemoveAt(int index);
    bool Swap(int first, int second); void Sort(); void Reverse(); void Print() const;
    bool IsEmpty() const; bool IsNotEmpty() const; int Size() const;
    bool MoveNext(); void PrintCurrent() const;
};
#endif
