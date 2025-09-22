#include <stdio.h>
#include<stdlib.h>
struct Book {
    char title[50];
    char author[50];
    int id;
} s;
void addBook();
void updateBook();
void deleteBook();
void searchBook();
void displayBook();

int main() {
    int choice;
    while (1) {
        printf("*****MAIN MENU*******\n");
        printf("1. Add Books\n");
        printf("2.Update books\n");
        printf("3. Delete Book\n");
        printf("4. Search Book\n");
        printf("5. View Book List\n");
        printf("6. Exit\n");
        printf("Enter your choice from 1-6: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                updateBook();
                break;
            case 3:
            	deleteBook();
            	break;  	
            case 4:
                searchBook();
                break;
            case 5:
                displayBook();
                break;
            case 6:
                printf("Exiting...\n");\
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void addBook() {
    FILE *fp;
    int op;
    fp = fopen("Record.txt", "a"); // Open file in append mode
    if (fp == NULL) {
        printf("Unable to open file!\n");
        return;
    }
    
    do {
        printf("Enter book ID: ");
        scanf("%d", &s.id);
        printf("Enter book title: ");
        scanf("%s", s.title);
        printf("Enter author name: ");
        scanf("%s", s.author);
        fprintf(fp, "%d\t%s\t%s\n", s.id, s.title, s.author); // Append new book
        printf("Press 1 to continue adding books, any other key to stop: ");
        scanf("%d", &op);
    } while (op == 1);
    
    printf("Book added successfully!\n");
    fclose(fp);
}
void updateBook() {
    FILE *fp, *temp;
    struct s ;
    int id, found = 0;

    fp = fopen("Record.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("File is not created !\n");
        return;
    }

    printf("Enter the Book ID to update: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %s\n", &s.id, s.title, s.author) != EOF) 
	{
        if (s.id == id) {
            found = 1;
            printf("Enter new title: ");
            scanf(" %s", s.title);
            printf("Enter new author: ");
            scanf(" %s", s.author);
        }
        fprintf(temp, "%d \"%s\" \"%s\n", s.id, s.title, s.author);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("Record.txt");
        rename("temp.txt", "Record.txt");
        printf("Book record updated successfully!\n");
    } else {
        remove("temp.txt");
        printf("Book with ID %d not found.\n", id);
    }
}

void deleteBook() {
    FILE *fp = fopen("Record.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Unable to open file!\n");
        return;
    }
    
    int id;
    int found = 0;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d\t%s\t%s\n", &s.id, s.title, s.author) != EOF) {
        if (s.id == id) {
            found = 1;
            printf("Book with ID %d deleted successfully!\n", id);
        } else {
            fprintf(temp, "%d\t%s\t%s\n", s.id, s.title, s.author);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!found) {
        printf("No such book with the entered ID found.\n");
    } else {
        remove("Record.txt");
        rename("temp.dat", "Record.dat");
    }
}

void searchBook() {
    FILE *fp = fopen("Record.txt", "r");
    if (fp == NULL) {
        printf("Unable to open file!\n");
        return;
    }

    int idd;
    printf("Enter book ID to search: ");
    scanf("%d", &idd);

    int found = 0;
    while (fscanf(fp, "%d\t%s\t%s\n", &s.id, s.title, s.author) != EOF) {
        if (s.id == idd) {
            printf("Book found:\nID: %d\nTitle: %s\nAuthor: %s\n", s.id, s.title, s.author);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No book found with the entered ID.\n");
    }

    fclose(fp);
}

void displayBook() {
    FILE *fp = fopen("Record.txt", "r");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }

    printf("\n********Library Record********\n");
    while (fscanf(fp, "%d\t%s\t%s\n", &s.id, s.title, s.author) != EOF) {
        printf("Book ID: %d\n", s.id);
        printf("Book Title: %s\n", s.title);
        printf("Book Author: %s\n", s.author);
    }

    fclose(fp);
}