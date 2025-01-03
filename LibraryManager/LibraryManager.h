#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class BookManager
{
private:
	vector<Book> books;

public:
	void addBook(string title, string author);
	void displayAllBooks();
	void searchByTitle(string title);
	void searchByAuthor(string author);

};

class Book
{
public:
	string title;
	string author;

	Book(string title, string author);
};