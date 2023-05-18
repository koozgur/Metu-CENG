#include "browser.h"

Browser::Browser() {
    windows.append(Window());
}

void Browser::newWindow() {
    
    windows.prepend(Window());
    return;
}

void Browser::closeWindow() {
    
    if(windows.isEmpty())
        return;
    else{
        windows.removeNodeAtIndex(0);
        return;
    }
}

void Browser::switchToWindow(int index) {
    
    if(index < 0)
        return;
    windows.moveToIndex(index,0);
    return;
}

Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}

void Browser::moveTab(Window &from, Window &to) {
    
    to.newTab(from.getActiveTab());
    from.closeTab();
    return;
}

void Browser::mergeWindows(Window &window1, Window &window2) {
    
    while(!(window2.isEmpty())){
        window2.changeActiveTabTo(0);
        window1.newTab(window2.getActiveTab());
        window2.closeTab();
    }
    return;
}

void Browser::mergeAllWindows() {
    
    Node <Window> * first = windows.getFirstNode();
    Node <Window> * mover;
    if(first == NULL)
        return;
    if(first -> next == first)
        return;
    mover = first -> next;
    while(mover != first){
        mergeWindows(first -> data,mover -> data);
        mover = mover -> next;
    }
    return;
}

void Browser::closeAllWindows() {
    
    windows.removeAllNodes();
    return;
}


void Browser::closeEmptyWindows() {
    
    Node <Window> * mover = windows.getFirstNode();
    int counter = 0;
    int l_size = windows.getSize();
    Node <Window> * shadow;
    while(counter < l_size){
        shadow = mover -> next;
        if((mover -> data).isEmpty()){
            windows.removeNode(mover);
        }
        counter ++;
        if(counter < l_size)
            mover = shadow;
    }
    return;
}

void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}
