#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
    
    if(tabs.isEmpty())
        return Tab();
    else{
        return (tabs.getNodeAtIndex(activeTab)) -> data;
    }
}

bool Window::isEmpty() const {
    
    if(tabs.isEmpty())
        return 1;
    else{
        return 0;
    }
}

void Window::newTab(const Tab &tab) {
    
    tabs.insertAtIndex(tab,activeTab + 1);
    activeTab++;
    return;
}

void Window::closeTab() {
    
    if(activeTab == tabs.getSize() - 1){
        tabs.removeNodeAtIndex(activeTab);
        activeTab--;
    }
    else{
        tabs.removeNodeAtIndex(activeTab);
    }
    if(tabs.isEmpty())
        activeTab = -1;
    return;
}

void Window::moveActiveTabTo(int index) {
    
    if(index < 0)
        return;
    if(activeTab < 0) /* window is empty*/
        return;
    if(index >= tabs.getSize()){
        tabs.moveToIndex(activeTab,tabs.getSize()-1);
        activeTab = tabs.getSize() - 1;
    }
    else{
        tabs.moveToIndex(activeTab,index);
        activeTab = index;
    }
    return;
}

void Window::changeActiveTabTo(int index) {
    
    if(index >= tabs.getSize()){
        return;
    }
    else if(index < 0){
        return;
    }
    else{
        activeTab = index;
        return;
    }
}

void Window::addTab(Node<Tab> &tab) {
    
    if(tabs.isEmpty()){
        tabs.append(tab.data);
        activeTab = 0;
    }
    else{
        tabs.append(tab.data);
    }
    return;
}

void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}
