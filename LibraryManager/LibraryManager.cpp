#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {}
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가
    void addBook(const string& title, const string& author) {
        books.emplace_back(title, author);
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }
        cout << "현재 도서 목록:" << endl;
        for (const auto& book : books) {
            cout << "- " << book.title << " by " << book.author << endl;
        }
    }

    // 책 제목으로 검색
    Book* findBookByTitle(const string& title) {
        for (auto& book : books) {
            if (book.title == title) {
                return &book;
            }
        }
        return nullptr;
    }

    // 책 작가로 검색
    Book* findBookByAuthor(const string& author) {
        for (auto& book : books) {
            if (book.author == author) {
                return &book;
            }
        }
        return nullptr;
    }
};

class BorrowManager {
private:
    unordered_map<string, int> stock; // 책 제목 -> 재고 수량

public:
    // 책 재고 초기화
    void initializeStock(Book& book, int quantity = 3) {
        stock[book.title] = quantity;
        cout << "'" << book.title << "' 책 재고가 초기화되었습니다. (재고: " << quantity << ")" << endl;
    }

    // 책 대여
    void borrowBook(const string& title) {
        if (stock.find(title) != stock.end() && stock[title] > 0) {
            stock[title]--;
            cout << "'" << title << "' 책을 대여하였습니다. 남은 재고: " << stock[title] << endl;
        }
        else {
            cout << "'" << title << "' 책은 현재 대여가 불가능합니다." << endl;
        }
    }

    // 책 반납
    void returnBook(const string& title) {
        if (stock.find(title) != stock.end()) {
            stock[title]++;
            cout << "'" << title << "' 책을 반납하였습니다. 현재 재고: " << stock[title] << endl;
        }
        else {
            cout << "'" << title << "' 책이 존재하지 않습니다." << endl;
        }
    }

    // 모든 책의 재고 출력
    void displayStock() const {
        if (stock.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }
        cout << "현재 책 재고:" << endl;
        for (const auto& entry : stock) {
            cout << "- " << entry.first << " (재고: " << entry.second << ")" << endl;
        }
    }
};

int main() {
    BookManager bookManager;
    BorrowManager borrowManager;

    // 책 추가
    bookManager.addBook("The Great Gatsby", "F. Scott Fitzgerald");
    bookManager.addBook("1984", "George Orwell");

    // 책 초기화
    for (auto& book : { bookManager.findBookByTitle("The Great Gatsby"), bookManager.findBookByTitle("1984") }) {
        if (book) {
            borrowManager.initializeStock(*book);
        }
    }

    // 메뉴
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 목록 출력" << endl;
        cout << "2. 책 대여" << endl;
        cout << "3. 책 반납" << endl;
        cout << "4. 책 재고 출력" << endl;
        cout << "5. 종료" << endl;
        cout << "선택: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            bookManager.displayAllBooks();
        }
        else if (choice == 2) {
            string title;
            cout << "대여할 책 제목: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.borrowBook(title);
        }
        else if (choice == 3) {
            string title;
            cout << "반납할 책 제목: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.returnBook(title);
        }
        else if (choice == 4) {
            borrowManager.displayStock();
        }
        else if (choice == 5) {
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0;
}