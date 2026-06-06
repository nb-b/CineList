#pragma once
#include <afxstr.h>

struct Film {
    CString kode;
    CString judul;
    CString genre;
    int tahun;
    double rating;
    CString sutradara;
};

struct MovieNode {
    Film data;
    MovieNode* next;
};

class MovieLinkedList {
public:
    MovieNode* head;

    MovieLinkedList();
    ~MovieLinkedList();

    void AddMovie(Film newFilm);
    bool EditMovie(CString targetKode, Film updatedFilm);
    bool DeleteMovie(CString targetKode);
    MovieNode* SearchMovie(CString keyword, bool byTitle);
    void SortByYear();
    void ClearAll();
};