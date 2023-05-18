#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
    // TODO
    if(tabs.isEmpty())
        return Tab();
    else{
        return (tabs.getNodeAtIndex(activeTab)) -> data;
    }
}

bool Window::isEmpty() const {
    // TODO
    if(tabs.isEmpty())
        return 1;
    else{
        return 0;
    }
}

void Window::newTab(const Tab &tab) {
    // TODO
    tabs.insertAtIndex(tab,activeTab + 1);
    activeTab++;
    return;
}

void Window::closeTab() {
    // TODO
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
    // TODO
    if(index < 0)
        return;
    if(activeTab < 0) /* window boş*/
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
    // TODO
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
    // TODO
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