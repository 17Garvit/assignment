// Structures - 1
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>
#include<stdbool.h>

typedef struct {
    int roll_number;
    char name[50];
    int age;
    float gpa;
} Student;

Student* create_student_list(int n) {
    Student *studs = (Student*) malloc(n * sizeof(Student));
    return studs;
}

void add_student(Student *studs, int i, char *name, int age, float gpa,int roll_number) {
    studs[i].roll_number=roll_number;
    strcpy(studs[i].name, name);
    studs[i].age = age;
    studs[i].gpa = gpa;
}

void display_students(Student *students, int size) {
    if(size==0){
      printf("\nNo reords available\n:");
      return;
    }
    for (int i = 0; i < size; i++) {
        printf("Roll Number:%d,Name: %s, Age: %d, GPA: %.2f\n",students[i].roll_number, students[i].name, students[i].age, students[i].gpa);
    }
}

void free_student_list(Student *students) {
    free(students);
}

bool check_roll_number(Student *students,int size,int roll_number){
    for(int i=0;i<size;i++){
        if(students[i].roll_number==roll_number){
            return true;
        }
    }
    return false;
} 
int read_student_name(char name[50]){
    printf("Enter name:");
    if((fgets(name,50,stdin))==NULL){
        return 0;
    }
    
    char *newline=strchr(name,'\n');
    if(newline!=NULL){
        *newline='\0';
    }
    else{
    int ch=getchar();
        if(ch!='\n'&& ch!=EOF){
                while(ch!='\n'&&ch!=EOF){
                }
                printf("Name can only have 49 characters");
                return 0;
        }
        
    }
    if(strlen(name)==0){
        printf("Name cannot be empty\n");
        return 0;
    }
    return 1;
}
int compare_students(const void *x,const void *y){
    Student s1=*(const Student *)x;

    Student s2=*(const Student *)y;
        if(s1.gpa>s2.gpa){
            return -1;
        }
        if(s1.gpa<s2.gpa){
            return 1;
        }
        if(s1.roll_number<s2.roll_number){
            return -1;
        }
        if(s1.roll_number>s2.roll_number){
            return 1;
        }
        return 0;
}
void display_sorted_student(int size,Student *student){
    if(size==0){

        printf("No student records are available:\n");

        return;

    }
    Student *sorted_list = malloc(size*sizeof(Student));

    if(sorted_list==NULL){
        printf("Memory allocation failed:\n");

        return;

    }
    qsort(sorted_list,size,sizeof(Student),compare_students);

    display_students(sorted_list,size);

    free_student_list(sorted_list);
}

int main() {
    int memory_block;
    int size=0;
    int choice;
    
    printf("Enter the initial capacity of student:");
    if((scanf("%d",&memory_block))!=1){
        printf("Invalid input:\n");
        return 1;
    }
    getchar();
    if(memory_block<1){
        printf("Invalid input");
        return 1;
    }
    Student *student_list=create_student_list(memory_block);
    if(student_list==NULL){
        printf("Memory allocation failed:\n");
    }
    while(1){
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. GPA Summary\n");
        printf("7. Display Sorted Students\n");
        printf("8. Exit\n");
        printf("Enter your choice:");
        if((scanf("%d",&choice))!=1){
            printf("Invalid input:\n");
            break;
        }
        getchar();
       
        
        switch(choice){
            case 1:{
                int roll_number;
                int age;
                float gpa;
                char name[50];

                printf("\nEnter roll number: ");

                if (scanf("%d", &roll_number) != 1) {
                    printf("Invalid roll number.\n");
                    break;
                }
                getchar();
                
                if(roll_number<=0){
                    printf("Roll no must be Positive:\n");
                    break;
                }
                if(check_roll_number(student_list,size,roll_number)){
                    printf("duplicate roll no:\n");
                    break;
                }
                if (!read_student_name(name)) {
                    break;
                }

                printf("Enter age: ");

                if (scanf("%d", &age) != 1) {
                    printf("Invalid age.\n");
                    break;
                }

                getchar();

                if (age < 16 || age > 100) {
                    printf("Age must be between 16 and 100.\n");
                    break;
                }

                printf("Enter GPA: ");

                if (scanf("%f", &gpa) != 1) {
                    printf("Invalid GPA.\n");
                    break;
                }

                getchar();

                if (!isfinite(gpa) || gpa < 0 || gpa > 4) {
                    printf("GPA must be between 0 and 4.\n");
                    break;
                }
                if(size==memory_block){
                    int new_memory_block=memory_block*2;
                    Student *temp=realloc(student_list,new_memory_block*sizeof(Student));

                    if(temp==NULL){
                        printf("Memory allocation failed:\n");
                        break;
                }
                student_list=temp;
                memory_block=new_memory_block;
                printf("Allocation is successfull:\n");
                }

            add_student(student_list, size, name,age, gpa, roll_number); 
            
                size++;

                printf("Student added successfully!\n");

                break;
            
            }
            case 2:

                display_students(student_list, size);

                break;
            
            case 3: {

            int roll_number;
            int index = -1;

                printf("Enter roll number to search: ");

                    if (scanf("%d", &roll_number) != 1) {
                        printf("Invalid input.\n");
                             break;
                }

                getchar();

                for (int i = 0; i < size; i++) {

                    if (student_list[i].roll_number == roll_number) {
                        index = i;
                        break;
                    }
                }

                if (index == -1) {
                    printf("Student not found.\n");
                }

                else {

                    printf("\nStudent found!\n");

                    printf("Roll Number: %d\n",student_list[index].roll_number);
                           
                    printf("Name: %s\n",student_list[index].name);
                           
                    printf("Age: %d\n",student_list[index].age);
                           
                    printf("GPA: %.2f\n",student_list[index].gpa);
                           
                }

                break;
            }
            case 4: {

                int roll_number;
                int index = -1;
                int age;
                float gpa;
                char name[50];

                printf("Enter roll number to update: ");

                if (scanf("%d", &roll_number) != 1) {
                    printf("Invalid input.\n");
                    break;
                }

                getchar();

                for (int i = 0; i < size; i++) {

                    if (student_list[i].roll_number == roll_number) {
                        index = i;
                        break;
                    }
                }

                if (index == -1) {
                    printf("Student not found.\n");
                    break;
                }

                if (!read_student_name(name)) {
                    break;
                }

                printf("Enter new age: ");

                if (scanf("%d", &age) != 1) {
                    printf("Invalid age.\n");
                    break;
                }

                getchar();

                if (age < 16 || age > 100) {
                    printf("Invalid age.\n");
                    break;
                }

                printf("Enter new GPA: ");

                if (scanf("%f", &gpa) != 1) {
                    printf("Invalid GPA.\n");
                    break;
                }

                getchar();

                if (!isfinite(gpa) || gpa < 0 || gpa > 4) {
                    printf("Invalid GPA.\n");
                    break;
                }

                strcpy(student_list[index].name, name);

                student_list[index].age = age;

                student_list[index].gpa = gpa;

                printf("Student updated successfully!\n");

                break;
            }
            case 5: {

                int roll_number;
                int index = -1;

                printf("Enter roll number to delete: ");

                if (scanf("%d", &roll_number) != 1) {
                    printf("Invalid input.\n");
                    break;
                }

                getchar();

                for (int i = 0; i < size; i++) {

                    if (student_list[i].roll_number == roll_number) {
                        index = i;
                        break;
                    }
                }

                if (index == -1) {
                    printf("Student not found.\n");
                    break;
                }

                for (int i = index; i < size - 1; i++) {
                    student_list[i] = student_list[i + 1];
                }

                size--;

                printf("Student deleted successfully!\n");

                break;
            }

            case 6: {

                if (size == 0) {
                    printf("No records available for GPA analysis.\n");
                    break;
                }

                int highest = 0;
                int lowest = 0;

                float total = 0;

                for (int i = 0; i < size; i++) {

                    total = total + student_list[i].gpa;

                    if (student_list[i].gpa > student_list[highest].gpa) {
                        highest = i;
                    }

                    if (student_list[i].gpa < student_list[lowest].gpa) {
                        lowest = i;
                    }
                }

                printf("\nHighest GPA Student: %s (%.2f)\n",
                       student_list[highest].name,
                       student_list[highest].gpa);

                printf("Lowest GPA Student: %s (%.2f)\n",
                       student_list[lowest].name,
                       student_list[lowest].gpa);

                printf("Average GPA: %.2f\n", total / size);

                break;
            }

            case 7:

                display_sorted_student(size, student_list);

                break;

            case 8:

                free_student_list(student_list);

                printf("Memory released successfully.\n");

                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
 free_student_list(student_list);

    return 0;
}


                








       
