#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
    // TODO
    return (tabs.getNodeAtIndex(activeTab))->data;
}

bool Window::isEmpty() const {
    // TODO
    if(tabs.getFirstNode()) return false;
    else return true;
}

void Window::newTab(const Tab &tab) {
    // TODO
    tabs.append(tab);
    activeTab=tabs.getSize()-1;
    
}

void Window::closeTab() {
    // TODO
    tabs.removeNodeAtIndex(activeTab);
    if(tabs.getSize()==0) activeTab=-1;
}

void Window::moveActiveTabTo(int index) {
    // TODO
    
    tabs.moveToIndex(activeTab,index);
    if(index>= tabs.getSize()) activeTab=tabs.getSize()-1;
    else activeTab=index;
}

void Window::changeActiveTabTo(int index) {
    // TODO
    if(index<tabs.getSize() && index>=0) activeTab=index;

}

void Window::addTab(Node<Tab> &tab) {
    // TODO
    tabs.append(tab.data);
    if(tabs.getSize()==1) activeTab=0;
}

void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}
