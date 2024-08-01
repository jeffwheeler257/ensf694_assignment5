/*
 *  graph.cpp.cpp
 *  ENSF 694 Lab 5 - Exercise C
 *  Created by Mahmood Moussavi
 *  Completed by Jeff Wheeler
 *  Submission date: August 2, 2024
 */

#include "graph.h"

PriorityQueue::PriorityQueue() : front(nullptr) {}

bool PriorityQueue::isEmpty() const {
    return front == nullptr;
}

void PriorityQueue::enqueue(Vertex* v) {
    ListNode* newNode = new ListNode(v);
    if (isEmpty() || v->dist < front->element->dist) {
        newNode->next = front;
        front = newNode;
    } else {
        ListNode* current = front;
        while (current->next != nullptr && current->next->element->dist <= v->dist) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

Vertex* PriorityQueue::dequeue() {
    if (isEmpty()) {
        cerr << "PriorityQueue is empty." << endl;
        exit(0);
    }
    Vertex* frontItem = front->element;
    ListNode* old = front;
    front = front->next;
    delete old;
    return frontItem;
}


void Graph::printGraph() {
    Vertex* v = head;
    while (v) {
        for (Edge* e = v->adj; e; e = e->next) {
            Vertex* w = e->des;
            cout << v->name << " -> " << w->name << "  " << e->cost << "   " << (w->dist == INFINITY ? "inf" : to_string(w->dist)) << endl;
        }
        v = v->next;
    }
}

Vertex* Graph::getVertex(const char vname) {
    Vertex* ptr = head;
    Vertex* newv;
    if (ptr == nullptr) {
        newv = new Vertex(vname);
        head = newv;
        tail = newv;
        numVertices++;
        return newv;
    }
    while (ptr) {
        if (ptr->name == vname)
            return ptr;
        ptr = ptr->next;
    }
    newv = new Vertex(vname);
    tail->next = newv;
    tail = newv;
    numVertices++;
    return newv;
}

void Graph::addEdge(const char sn, const char dn, double c) {
    Vertex* v = getVertex(sn);
    Vertex* w = getVertex(dn);
    Edge* newEdge = new Edge(w, c);
    newEdge->next = v->adj;
    v->adj = newEdge;
    (v->numEdges)++;
    // point 1
}

void Graph::clearAll() {
    Vertex* ptr = head;
    while (ptr) {
        ptr->reset();
        ptr = ptr->next;
    }
}

void Graph::dijkstra(const char start) {
    Vertex* s = getVertex(start);
    
    Vertex* traverse = head;
    while (traverse != nullptr){
        traverse->reset();
        traverse = traverse->next;
    }
    
    PriorityQueue q;
    q.enqueue(s);
    s->dist = 0;
    double new_dist;
    while(!q.isEmpty()){
        Vertex* v = q.dequeue();
        for (Edge* edge = v->adj; edge != nullptr; edge = edge->next){
            Vertex* w = edge->des;
            new_dist = v->dist + edge->cost;
            if (new_dist < w->dist){
                w->dist = new_dist;
                w->prev = v;
                q.enqueue(w);
            }
        }
    }


}

void Graph::unweighted(const char start) {
    Vertex* s = getVertex(start);
    
    Vertex* traverse = head;
    while (traverse != nullptr){
        traverse->reset();
        traverse = traverse->next;
    }

    PriorityQueue q;
    q.enqueue(s);
    s->dist = 0;
    while(!q.isEmpty()){
        Vertex* v = q.dequeue();
        for (Edge* edge = v->adj; edge != nullptr; edge = edge->next){
            Vertex* w = edge->des;
            if (w->dist == INFINITY){
                w->dist = v->dist + 1;
                w->prev = v;
                q.enqueue(w);
            }
        }
    }
}

void Graph::readFromFile(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Could not open file: " << filename << endl;
        exit(1);
    }

    char sn, dn;
    double cost;
    while (infile >> sn >> dn >> cost) {
        addEdge(sn, dn, cost);
    }

    infile.close();
}

void Graph::printPath(Vertex* dest) {
    if (dest->prev != nullptr) {
        printPath(dest->prev);
        cout << " " << dest->name;
    } else {
        cout << dest->name;
    }
}

void Graph::printAllShortestPaths(const char start, bool weighted) {
    if (weighted) {
        dijkstra(start);
    } else {
        unweighted(start);
    }
    setiosflags(ios::fixed);
    setprecision(2);
    Vertex* v = head;
    while (v) {
        if (v->name == start) {
            cout << start << " -> " << v->name << "     0   " << start << endl;
        } else {
            
            cout << start << " -> " << v->name << "     " << (v->dist == INFINITY ? "inf" : to_string((int)v->dist)) << "   ";
            if (v->dist == INFINITY) {
                cout << "No path" << endl;
            } else {
                printPath(v);
                cout << endl;
            }
        }
        v = v->next;
    }
}
