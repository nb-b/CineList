#include "pch.h"
#include "Film.h"
#include <utility>

MovieLinkedList::MovieLinkedList() {
    head = nullptr;
}

MovieLinkedList::~MovieLinkedList() {
    ClearAll();
}

void MovieLinkedList::ClearAll() {
    MovieNode* current = head;
    while (current != nullptr) {
        MovieNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

void MovieLinkedList::AddMovie(Film newFilm) {
    MovieNode* newNode = new MovieNode();
    newNode->data = newFilm;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        MovieNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

bool MovieLinkedList::EditMovie(CString targetKode, Film updatedFilm) {
    MovieNode* temp = head;
    while (temp != nullptr) {
        if (temp->data.kode == targetKode) {
            temp->data = updatedFilm;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool MovieLinkedList::DeleteMovie(CString targetKode) {
    if (head == nullptr) return false;

    if (head->data.kode == targetKode) {
        MovieNode* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    MovieNode* curr = head;
    while (curr->next != nullptr && curr->next->data.kode != targetKode) {
        curr = curr->next;
    }

    if (curr->next != nullptr) {
        MovieNode* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
        return true;
    }

    return false;
}

MovieNode* MovieLinkedList::SearchMovie(CString keyword, bool byTitle) {
    MovieNode* temp = head;
    CString lowerKeyword = keyword;
    lowerKeyword.MakeLower();

    while (temp != nullptr) {
        CString target = byTitle ? temp->data.judul : temp->data.genre;
        target.MakeLower();

        if (target.Find(lowerKeyword) != -1) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void MovieLinkedList::SortByYear() {
    if (head == nullptr || head->next == nullptr) return;

    bool swapped;
    MovieNode* ptr1;
    MovieNode* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data.tahun < ptr1->next->data.tahun) {
                std::swap(ptr1->data, ptr1->next->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}