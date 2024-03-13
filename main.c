#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void menu();

typedef struct{
    char name[35];
    char address[50];
    char father_name[35];
    char mother_name[30];
    char tel_number[15];
    char gender[8];
    char mail[100];
}Contact;

Contact contact_list[101];

void exit_prog()
{
    printf("\t\t\t\t Application finished");
    exit(0);
}

//FILE *out_file = fopen("contact_list_out", "w"); // write only

void read()
{
    FILE *fp;
    fp = fopen("f.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    char current_line[1001];
    while(fgets(current_line, 100, fp))
    {
        printf("%s", current_line);
    }
    fclose(fp);
}


void addcont()
{
    Contact new_contact;
    printf("Enter name: ");
    scanf("%34s", new_contact.name);
    printf("Enter address: ");
    scanf("%49s", new_contact.address);
    printf("Enter father's name: ");
    scanf("%34s", new_contact.father_name);
    printf("Enter mother's name: ");
    scanf("%29s", new_contact.mother_name);
    printf("Enter telephone number: ");
    scanf("%14s", new_contact.tel_number);
    printf("Enter gender: ");
    scanf("%7s", new_contact.gender);
    printf("Enter email address: ");
    scanf("%99s", new_contact.mail);

    FILE *fp = fopen("f.txt", "a");

    fprintf(fp, "%s %s %s %s %s %s %s \n", new_contact.name, new_contact.address,
            new_contact.father_name, new_contact.mother_name, new_contact.tel_number,
            new_contact.gender, new_contact.mail);
    fclose(fp);
    menu();
}
void searchcont()
{
    char number[15];
    printf("Enter the telephone number of the contact: ");
    scanf("%s", number);

    FILE *fp = fopen("f.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    Contact contact;
    int i = 0, found = 0;
    while(fscanf(fp, "%34s %49s %34s %29s %14s %7s %99s", contact.name, contact.address,
                 contact.father_name, contact.mother_name, contact.tel_number,
                 contact.gender, contact.mail) == 7)
    {
        if(strcmp(contact.tel_number, number) == 0)
        {
            printf("Contact found:\n");
            printf("Name: %s\n", contact.name);
            printf("Address: %s\n", contact.address);
            printf("Father's name: %s\n", contact.father_name);
            printf("Mother's name: %s\n", contact.mother_name);
            printf("Telephone number: %s\n", contact.tel_number);
            printf("Gender: %s\n", contact.gender);
            printf("Email address: %s\n\n", contact.mail);
            found = 1;
            break;
        }
        i++;
    }

    if(!found)
    {
        printf("Contact not found\n");
    }

    fclose(fp);
    menu();
}
void delete_contact() {
    char tel_number[15];
    printf("Enter the telephone number of the contact you want to delete: ");
    scanf("%14s", tel_number);

    FILE *fp = fopen("f.txt", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL) {
        printf("Error creating temporary file\n");
        fclose(fp);
        return;
    }

    Contact contact;
    int deleted = 0;
    while(fscanf(fp, "%34s %49s %34s %29s %14s %7s %99s", contact.name, contact.address,
                 contact.father_name, contact.mother_name, contact.tel_number,
                 contact.gender, contact.mail) == 7)
    {
        if(strcmp(contact.tel_number, tel_number) == 0) {
            deleted = 1;
        } else {
            fprintf(temp, "%s %s %s %s %s %s %s\n", contact.name, contact.address,
                    contact.father_name, contact.mother_name, contact.tel_number,
                    contact.gender, contact.mail);
        }
    }
    fclose(fp);
    fclose(temp);

    if(!deleted) {
        printf("Contact not found\n");
        remove("temp.txt");
    } else {
        remove("f.txt");
        rename("temp.txt", "f.txt");
        printf("Contact deleted successfully\n");
    }

    menu();
}

void contlist()
{
    FILE *fp = fopen("f.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    Contact contact;
    int i = 0;
    while(fscanf(fp, "%34s %49s %34s %29s %14s %7s %99s", contact.name, contact.address,
                 contact.father_name, contact.mother_name, contact.tel_number,
                 contact.gender, contact.mail) == 7)
    {
        printf("Contact %d:\n", i+1);
        printf("Name: %s\n", contact.name);
        printf("Address: %s\n", contact.address);
        printf("Father's name: %s\n", contact.father_name);
        printf("Mother's name: %s\n", contact.mother_name);
        printf("Telephone number: %s\n", contact.tel_number);
        printf("Gender: %s\n", contact.gender);
        printf("Email address: %s\n\n", contact.mail);
        i++;
    }
    fclose(fp);
    menu();
}
void modifycont()
{
    char tel_number[15];
    printf("Enter the telephone of the contact to be modified: ");
    scanf("%14s", tel_number);

    FILE *fp = fopen("f.txt", "r");
    FILE *fp_temp = fopen("f_temp.txt", "w"); // temporary file

    if(fp == NULL || fp_temp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    Contact contact;
    int found = 0;
    while(fscanf(fp, "%34s %49s %34s %29s %14s %7s %99s", contact.name, contact.address,
                 contact.father_name, contact.mother_name, contact.tel_number,
                 contact.gender, contact.mail) == 7)
    {
        if(strcmp(contact.tel_number, tel_number) == 0)
        {
            found = 1;
            printf("Contact found:\n");
            printf("Name: %s\n", contact.name);
            printf("Address: %s\n", contact.address);
            printf("Father's name: %s\n", contact.father_name);
            printf("Mother's name: %s\n", contact.mother_name);
            printf("Telephone number: %s\n", contact.tel_number);
            printf("Gender: %s\n", contact.gender);
            printf("Email address: %s\n", contact.mail);

            // modify the contact
            printf("\nEnter the new details:\n");
            printf("Enter address: ");
            scanf("%49s", contact.address);
            printf("Enter father's name: ");
            scanf("%34s", contact.father_name);
            printf("Enter mother's name: ");
            scanf("%29s", contact.mother_name);
            printf("Enter telephone number: ");
            scanf("%14s", contact.tel_number);
            printf("Enter gender: ");
            scanf("%7s", contact.gender);
            printf("Enter email address: ");
            scanf("%99s", contact.mail);
        }

        // write the contact to the temporary file
        fprintf(fp_temp, "%s %s %s %s %s %s %s\n ", contact.name, contact.address,
                contact.father_name, contact.mother_name, contact.tel_number,
                contact.gender, contact.mail);
    }

    fclose(fp);
    fclose(fp_temp);

    // delete the old file and rename the temporary file to the original name
    remove("f.txt");
    rename("f_temp.txt", "f.txt");

    if(!found)
    {
        printf("Contact not found\n");
    }
    else
    {
        printf("Contact modified successfully\n");
    }
    menu();
}


void menu() {
    printf("\t\t\t WELCOME TO PHONEBOOK");
    printf("\n\n\t\t\t\t  MENU\t\t\n\n");
    printf("\t1.Add New Contact   \t2.Contact List   \t3.Search Contact  \n\t4.Modify Contact \t5.Delete Contact \t6.Exit\n\n");
    printf("\t\t\t\t Enter 1 to 6 in order to use the application\n");
    switch(getch()) {
        case '1':
            addcont();
            break;
        case '2':
            contlist();
            break;
        case '3':
            searchcont();
            break;
        case '4':
            modifycont();
            break;
        case '5':
            delete_contact();
            break;
        case '6':
            exit_prog();
            break;
        default:
            menu();
    }
}

void start(){
    menu();
}

int main()
{
    system("color 01");
    start();
    //read();
    return 0;
}