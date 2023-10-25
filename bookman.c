#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_AUTHOR 50

typedef struct Book {
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int year;
    struct Book *next;
} Book;

// Function
Book* create_book(const char *title, const char *author, int year);
void add_book(Book **head, Book *book);
void delete_book(Book **head, const char *title);
void list_books(Book *head);
void save_books(Book *head, const char *filename);
void free_books(Book **head);
void menu(Book **head);

int main() {
    Book *head = NULL;
    menu(&head);
    free_books(&head);
    return 0;
}

Book* create_book(const char *title, const char *author, int year) {
    Book *new_book = (Book *) malloc(sizeof(Book));
    if (!new_book) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    strncpy(new_book->title, title, MAX_TITLE);
    strncpy(new_book->author, author, MAX_AUTHOR);
    new_book->year = year;
    new_book->next = NULL;
    return new_book;
}

void add_book(Book **head, Book *book) {
    if (!(*head)) {
        *head = book;
    } else {
        Book *temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = book;
    }
}

void delete_book(Book **head, const char *title) {
    if (!(*head)) return;

    Book *current = *head, *prev = NULL;
    while (current && strcmp(current->title, title) != 0) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        printf("Book not found.\n");
        return;
    }

    if (prev) {
        prev->next = current->next;
    } else {
        *head = current->next;
    }
    free(current);
}

void list_books(Book *head) {
    Book *temp = head;
    while (temp) {
        printf("Title: %s\nAuthor: %s\nYear: %d\n\n", temp->title, temp->author, temp->year);
        temp = temp->next;
    }
}

void save_books(Book *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    Book *temp = head;
    while (temp) {
        fprintf(file, "%s\t%s\t%d\n", temp->title, temp->author, temp->year);
        temp = temp->next;
    }

    fclose(file);
}

void free_books(Book **head) {
    while (*head) {
        Book *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void menu(Book **head) {
    int choice, year;
    char title[MAX_TITLE], author[MAX_AUTHOR], filename[MAX_TITLE + 4];

    do {
        printf("1. Add Book\n2. Delete Book\n3. List Books\n4. Save to File\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter title: ");
                fgets(title, MAX_TITLE, stdin);
                title[strcspn(title, "\n")] = 0;
                printf("Enter author: ");
                fgets(author, MAX_AUTHOR, stdin);
                author[strcspn(author, "\n")] = 0;
                printf("Enter year: ");
                scanf("%d", &year);
                add_book(head, create_book(title, author, year));
                break;

            case 2:
                printf("Enter title of the book to delete: ");
                fgets(title, MAX_TITLE, stdin);
                title[strcspn(title, "\n")] = 0;
                delete_book(head, title);
                break;

            case 3:
                list_books(*head);
                break;

            case 4:
                printf("Enter filename (without extension): ");
                fgets(filename, MAX_TITLE, stdin);
                filename[strcspn(filename, "\n")] = 0;
                strcat(filename, ".txt");
                save_books(*head, filename);
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 5);
}
