#include "TradingSystem.h"
#include <iostream>
#include <limits>
using namespace std;
int readInt(const string& prompt) { int x; while (true) { cout << prompt; if (cin >> x) return x; cout << "Invalid input. Enter a number.\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); } }
CircularOrderNode* readCircularOrder() {
    auto* o = new CircularOrderNode{}; o->orderID = readInt("Enter Order ID: ");
    cout << "Enter Investor Name: "; getline(cin >> ws, o->investorName);
    cout << "Enter Stock Symbol: "; cin >> o->stockSymbol;
    cout << "Enter Order Type (Buy/Sell): "; cin >> o->orderType;
    if (o->orderType != "Buy" && o->orderType != "Sell" && o->orderType != "buy" && o->orderType != "sell") { cout << "Invalid order type; order not added.\n"; delete o; return nullptr; }
    o->quantity = readInt("Enter Quantity: "); if (o->quantity <= 0) { cout << "Quantity must be positive.\n"; delete o; return nullptr; }
    o->priority = readInt("Enter Priority (1=Urgent, 2=Regular, 3=Low): "); if (o->priority < 1 || o->priority > 3) { cout << "Invalid priority.\n"; delete o; return nullptr; }
    o->next = nullptr; return o;
}
int main() {
    PriorityQueue orders; OrderList orderList; CircularOrderList rotatingOrders; int choice, nextOrderID = 1;
    do {
        cout << "\n===== Stock Trading Simulator =====\n"
             << "1. Add Stock Order (original)\n2. Process Highest Priority Order (original)\n3. Display Priority Queue (original)\n4. Check Queue Status (original)\n"
             << "5. Display Linked List Orders\n6. Insert Order at Head\n7. Remove Order from Head\n8. Insert Order at Index\n9. Remove Order at Index\n10. Swap Orders\n11. Sort Orders by ID\n12. Reverse Order List\n13. Check Linked List Status\n14. Exit (original menu)\n"
             << "\n--- Lab 6: Circular Trading Watchlist ---\n15. Display Circular Watchlist\n16. Insert Order at Pivot's Next (Head)\n17. Remove Order at Pivot's Next (Head)\n18. Insert Order at Index\n19. Remove Order at Index\n20. Swap Circular Orders\n21. Sort Circular Orders by ID\n22. Reverse Circular Watchlist\n23. Move to Next Order (Circular Rotation)\n24. Check Circular Watchlist Status\n25. Exit Program\n";
        choice = readInt("Enter your choice: ");
        switch (choice) {
        case 1: {
            OrderNode* o = new OrderNode{}; o->orderID = nextOrderID++; cout << "Enter Investor Name: "; getline(cin >> ws, o->investorName); cout << "Enter Stock Symbol: "; cin >> o->stockSymbol; cout << "Enter Order Type (Buy/Sell): "; cin >> o->orderType;
            if (o->orderType != "Buy" && o->orderType != "Sell" && o->orderType != "buy" && o->orderType != "sell") { cout << "Invalid order type.\n"; delete o; break; }
            o->quantity = readInt("Enter Quantity: "); if (o->quantity <= 0) { cout << "Quantity must be positive.\n"; delete o; break; }
            o->priority = readInt("Enter Priority (1=Urgent, 2=Regular, 3=Low): "); if (o->priority < 1 || o->priority > 3) { cout << "Invalid priority.\n"; delete o; break; }
            orders.Add(o); orderList.InsertAt(CreateOrder(*o), orderList.Size());
            rotatingOrders.InsertAt(new CircularOrderNode{o->orderID,o->investorName,o->stockSymbol,o->orderType,o->quantity,o->priority,nullptr}, rotatingOrders.Size());
            cout << "Order added to original priority queue, Lab 5 list, and circular watchlist.\n"; break;
        }
        case 2: { OrderNode* o = orders.Remove(); if (!o) cout << "No orders available to process.\n"; else { cout << "Processed Order ID: " << o->orderID << "\nInvestor: " << o->investorName << "\nStock: " << o->stockSymbol << "\nType: " << o->orderType << "\nQuantity: " << o->quantity << "\nPriority: " << o->priority << '\n'; delete o; } break; }
        case 3: orders.PrintQueue(); break;
        case 4: cout << (orders.IsEmpty() ? "Priority queue is empty.\n" : "Priority queue is not empty.\n"); break;
        case 5: orderList.Print(); break;
        case 6: { OrderListNode* o = new OrderListNode{}; o->orderID=readInt("Enter Order ID: "); cout << "Enter Investor Name: "; getline(cin>>ws,o->investorName); cout << "Enter Stock Symbol: "; cin>>o->stockSymbol; cout << "Enter Order Type: "; cin>>o->orderType; o->quantity=readInt("Enter Quantity: "); o->priority=readInt("Enter Priority (1-3): "); orderList.Insert(o); cout << "Order inserted at head.\n"; break; }
        case 7: { OrderListNode* o=orderList.Remove(); if(!o)cout<<"Linked list is empty.\n";else{cout<<"Removed Order ID: "<<o->orderID<<'\n';delete o;} break; }
        case 8: { OrderListNode* o=new OrderListNode{};o->orderID=readInt("Enter Order ID: ");cout<<"Enter Investor Name: ";getline(cin>>ws,o->investorName);cout<<"Enter Stock Symbol: ";cin>>o->stockSymbol;cout<<"Enter Order Type: ";cin>>o->orderType;o->quantity=readInt("Enter Quantity: ");o->priority=readInt("Enter Priority (1-3): ");int i=readInt("Enter index (0 to "+to_string(orderList.Size())+"): ");orderList.InsertAt(o,i);cout<<"Order inserted.\n";break; }
        case 9: { int i=readInt("Enter index to remove: ");OrderListNode*o=orderList.RemoveAt(i);if(!o)cout<<"Invalid index or list empty.\n";else{cout<<"Removed Order ID: "<<o->orderID<<'\n';delete o;}break; }
        case 10: { int a=readInt("Enter first index: "),b=readInt("Enter second index: ");cout<<(orderList.Swap(a,b)?"Orders swapped.\n":"Invalid index.\n");break; }
        case 11: orderList.Sort(); cout<<"Orders sorted by Order ID.\n"; break;
        case 12: orderList.Reverse(); cout<<"Order list reversed.\n"; break;
        case 13: cout<<(orderList.IsEmpty()?"Linked list is empty.\n":"Linked list is not empty.\n");cout<<"Total linked-list orders: "<<orderList.Size()<<'\n';break;
        case 14: cout << "Original menu exit selected. Choose 25 to close the program.\n"; break;
        case 15: rotatingOrders.Print(); break;
        case 16: { auto* o=readCircularOrder(); if(o){rotatingOrders.Insert(o);cout<<"Order inserted at pivot's next node.\n";}break; }
        case 17: { auto* o=rotatingOrders.Remove();if(!o)cout<<"Circular watchlist is empty.\n";else{cout<<"Removed circular order #"<<o->orderID<<" ("<<o->stockSymbol<<")\n";delete o;}break; }
        case 18: { auto* o=readCircularOrder();if(o){int i=readInt("Enter index (0 to "+to_string(rotatingOrders.Size())+"): ");rotatingOrders.InsertAt(o,i);cout<<"Order inserted into circular watchlist.\n";}break; }
        case 19: { int i=readInt("Enter index to remove: ");auto*o=rotatingOrders.RemoveAt(i);if(!o)cout<<"Circular watchlist is empty.\n";else{cout<<"Removed order #"<<o->orderID<<'\n';delete o;}break; }
        case 20: { int a=readInt("Enter first index: "),b=readInt("Enter second index: ");cout<<(rotatingOrders.Swap(a,b)?"Circular orders swapped.\n":"Circular watchlist is empty.\n");break; }
        case 21: rotatingOrders.Sort();cout<<"Circular orders sorted by ID.\n";break;
        case 22: rotatingOrders.Reverse();cout<<"Circular watchlist reversed.\n";break;
        case 23: if(rotatingOrders.MoveNext())rotatingOrders.PrintCurrent();else cout<<"Circular watchlist is empty.\n";break;
        case 24: cout<<(rotatingOrders.IsEmpty()?"Circular watchlist is empty.\n":"Circular watchlist is not empty.\n");cout<<"Total circular orders: "<<rotatingOrders.Size()<<"\nLast node links back to first: "<<(rotatingOrders.IsEmpty()?"N/A":"YES")<<'\n';break;
        case 25: cout<<"Exiting Stock Trading Simulator.\n";break;
        default: cout<<"Invalid choice. Select 1-25.\n";
        }
    } while (choice != 25);
    return 0;
}
