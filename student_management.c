#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    char department[50];
};

void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Department: ");
    scanf(" %[^\n]", s.department);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nID: %d", s.id);
        printf("\nName: %s", s.name);
        printf("\nAge: %d", s.age);
        printf("\nDepartment: %s\n", s.department);
    }

    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen("students.dat", "rb+");
    struct Student s;
    int id, found = 0;

    printf("\nEnter Student ID to Update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            found = 1;

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Department: ");
            scanf(" %[^\n]", s.department);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("\nRecord Updated Successfully!\n");
            break;
        }
    }

    if (!found)
        printf("\nStudent ID Not Found!\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    struct Student s;
    int id, found = 0;

    printf("\nEnter Student ID to Delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nRecord Deleted Successfully!\n");
    else
        printf("\nStudent ID Not Found!\n");
}

int main() {
    int choice;

    do {
        printf("\n============================");
        printf("\n Student Management System");
        printf("\n============================");
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Update Student");
        printf("\n4. Delete Student");
        printf("\n5. Exit");
        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                printf("\nThank You!\n");
                break;
            default:
                printf("\nInvalid Choice!\n");
        }

    } while (choice != 5);

    return 0;
}
