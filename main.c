#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

struct application_type{
    char name[125];
    char family_name[125];
    char father_name[125];
    char passport[125];
    char place[125];
    int school_number;
    int specialty;
    int ball1, ball2, ball3, ball_school;
    int total_ball;
    struct application_type *next;
};
struct specialty{
    int places;
    char title[255];
    int id;
    struct specialty *next;

};
void show(struct specialty *head){
    struct specialty *Q;
    Q=head;
    while (Q!=NULL){
        printf ("id:   %d\n",Q->id);
        printf ("Title:   %s\n",Q->title);
        printf ("Places:   %d\n",Q->places);
        printf("---------------------------\n");
Q=Q->next;
    }

}

void show_app(struct application_type *head){
    struct application_type *Q;
    Q=head;
    while (Q!=NULL){
        printf ("name surname fathername:   %s  %s  %s\n",Q->name,Q->family_name,Q->father_name);
        printf ("passport number place of birth school number:   %s  %s  %d\n",Q->passport,Q->place,Q->school_number);
        printf ("specialty:   %d \n",Q->specialty);
        printf ("Ball1 ball2 ball3 ball_school | total_ball:   %d %d %d  %d | %d\n",Q->ball1,Q->ball2,Q->ball3,Q->ball_school,Q->total_ball);
        printf("---------------------------\n");
        Q=Q->next;
    }

}
struct application_type * del(struct application_type *head,struct application_type* prev) {
    if (head == NULL) {
        exit(-1);
    }
    struct application_type* elem = prev->next;
    if(elem->next!=NULL){
        prev->next=elem->next;
    }else{
        prev->next=NULL;
    }
    free(elem);
    return head;
}
/*//////////???????????????
void push(Node **head, int data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}*/

int from_str_to_double(char s[125]) {
    if (s[0] == '-') {
        printf("%s", "Should be positive! EVERETHING\n");
        return -1;
    }
    int i = 0, sum = 0;
    while (s[i] != '\0') {
        if (s[i] <= '9' && s[i] >= '0' && sum < INT_MAX / 100) {
            sum = sum * 10 + (s[i] - '0');
            i++;
        } else {
            printf("%s", "Should be NUMBER!\n");
            return -1;
        }
    }
    return sum;
}
struct specialty* load_specialties(FILE *fp, struct specialty *Specialty){
    int id = 1;
//char mas[255];
    char str[255];

    while (!feof(fp)){
        fgets(str, sizeof(str),fp);
        char sep [5]=":";
        char strange[12]={'\0'};
        char *istr;
        if(strcmp(str,"[\n") == 0){
            //printf ("===============================qwerty\n");
            while (strcmp(str,"]\n") != 0){
                fgets(str, sizeof(str),fp);
                if(strcmp(str,"]\n") == 0){
                    break;
                }
                istr = strtok (str,sep);
                istr = strtok (NULL,sep);
                //printf ("%s",istr);
                strncpy(strange,istr,2);
                struct specialty *temp = malloc(sizeof(struct specialty));
                temp->places = from_str_to_double(strange);
                temp->id=id;
                id++;
                //printf("$$$$%d",temp->id);
                //puts(temp->id);

//        istr = strtok (NULL,sep);
//        istr = strtok (str,sep);
//        printf("+++%s\n",str);

                //printf ("****%s\n",str);
                strcpy(temp->title, str);
                temp->next = NULL;
                if (Specialty == NULL){
                    Specialty = temp;
                } else{
                    temp->next = Specialty;
                    Specialty = temp;
                }
                //puts(Specialty->title);
            }
            //return 0;
        }
    }
    return Specialty;
}
int main() {

int amount_applications_by_specialty[35] = {0};
struct application_type *ABITURIENTS = malloc(sizeof(struct application_type));
ABITURIENTS = NULL;

struct specialty *Specialty = malloc(sizeof(struct specialty));
Specialty = NULL;

    FILE *fp;
    FILE *fp1;
    fp = fopen("/Users/victoriasviridchik/CLionProjects/2sem_lab6/faculties", "r");
    fp1 = fopen("/Users/victoriasviridchik/CLionProjects/2sem_lab6/application_data", "w");
    if (!(fp != NULL && fp1 != NULL))
    {
        printf("It looks like there are some problems \n");
        return 0;
    }
    Specialty = load_specialties(fp,Specialty);

//    double data[10], flag_for_discounts = 0, flag_of_order = 0;
//    fscanf(fp, "%lf %lf %lf", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7], &data[8], &data[9]);
    fclose (fp);

    char command[125];
    while (1) {
        printf("%s", "\nEnter command(enrollment, quit,create_application,destroy_application,show_faculties,show_the_busket) \n ");
        scanf("%s", command);
        if (strcmp(command, "quit") == 0){
            puts("Thank you! Goodbye");
            break;
        } else if (strcmp(command, "create_application") == 0) {
            struct application_type *application = malloc(sizeof(struct application_type));

            char s[125];
            puts("Desirible Specialty , Choose id number from the list:\n");
            //show(Specialty);

            if(!Specialty){
                printf("There is no specialties!");
                continue;
            }else{
                show(Specialty);
            }
            scanf("%s", s);
            int id_app = from_str_to_double(s);

            if(id_app<1 || id_app >35){
                printf("Be carefull! There is no such specialty or invalid data.Start please again");
                continue;
            }

            application->specialty = id_app;
            amount_applications_by_specialty[id_app]+=1;
            puts("Enter name");
            scanf(" %s", application->name);
            puts("Enter familyname");
            scanf(" %s", application->family_name);
            puts("Enter fathername");
            scanf(" %s", application->father_name);

            puts("Enter grade for the first subject");
            scanf("%s", s);
            int tmp =0;
            tmp = from_str_to_double(s);
            if (tmp <= 0)
            {
                fclose (fp1);
                printf ("Wrong data\n");
                continue;
            } else{
                application->ball1 = tmp;
            }

            puts("Enter grade for the second subject");
            scanf("%s", s);

            tmp = from_str_to_double(s);
            if (tmp <= 0)
            {
                fclose (fp1);
                printf ("Wrong data\n");
                continue;
            } else{
                application->ball2 = tmp;
            }

            puts("Enter grade for the third subject");
            scanf("%s", s);
            tmp = from_str_to_double(s);
            if (tmp <= 0)
            {
                fclose (fp1);
                printf ("Wrong data\n");
                continue;
            } else{
                application->ball3 = tmp;
            }

            puts("Enter grade for the school grade");
            scanf("%s", s);
            tmp = from_str_to_double(s);
            if (tmp <= 0)
            {
                fclose (fp1);
                printf ("Wrong data\n");
                continue;
            } else{
                application->ball_school = tmp;
            }

            puts("Enter passport data");
            scanf("%s", s);
            strcpy(application->passport,s);
//            application.passport = s;

            puts("Enter place data");
            scanf("%s", s);
            strcpy(application->passport,s);

//            application.passport = s;

            puts("Enter school number");
            scanf("%s", s);
            tmp = from_str_to_double(s);
            if (tmp <= 0)
            {
                fclose (fp1);
                printf ("Wrong data\n");
                continue;
            } else{
                application->school_number = tmp;
            }

            application->total_ball = 0;
            application->total_ball = application->ball1+application->ball2+application->ball3+application->ball_school;
            printf("%s  %s  %s  %d  %d  %d  %d  %s  %s  %d  %d", application->name, application->family_name,application->father_name,application->ball1,application->ball2,application->ball3,application->ball_school,application->passport,application->place,application->school_number,application->total_ball);
//            application = NULL;
            if (ABITURIENTS == NULL){
                ABITURIENTS = application;
            } else{
                application->next = ABITURIENTS;
                ABITURIENTS = application;
            }



        } else if (strcmp(command, "back_to_old_data") == 0) {
        } else if (strcmp(command, "destroy_application") == 0) {

if(ABITURIENTS==NULL){
    puts("There is no applications");
    continue;
}

            struct application_type *data_temp = malloc(sizeof(struct application_type));
            struct application_type *prev = malloc(sizeof(struct application_type));
data_temp = ABITURIENTS;
prev = ABITURIENTS;
            char name_temp[255];
            char family_name_temp[255];

            puts("Enter name");
            scanf(" %s", name_temp);
            puts("Enter familyname");
            scanf(" %s", family_name_temp);
            int is_found = 0;
while (data_temp!=NULL){
    if(strcmp(data_temp->name,name_temp) == 0 && strcmp(data_temp->family_name, family_name_temp)==0 ){
is_found = 1;
if(ABITURIENTS->next==NULL){
ABITURIENTS=NULL;
} else{
    ABITURIENTS = del(ABITURIENTS,prev);
}
    }
    prev=data_temp;
    data_temp = data_temp->next;
}

     if(is_found==0){
         printf("There is no application with the given name and the given  aurname");
     }



            //printf(" %s", name_temp);


        }else if(strcmp(command, "save") == 0){

            //FILE *fp1;

            fp1 = fopen("/Users/victoriasviridchik/CLionProjects/2sem_lab6/application_data", "w");
            if (fp1 == NULL)
            {
                printf("It looks like there are some problems \n");
                return 0;
            }
//            printf("asdfg");
//            struct application_type *tmp = malloc(sizeof(struct application_type));

            if(!ABITURIENTS){
                printf("There is no data to save!");
                continue;
            }
            struct application_type *temp = ABITURIENTS;

//            temp = ABITURIENTS;
            while (temp!=NULL){

//                ABITURIENTS = ABITURIENTS->next;
                fprintf(fp1, "Name : %s  ", temp->name);
                fprintf(fp1, "Surname : %s  ", temp->family_name);
                fprintf(fp1, "Fathername : %s  ", temp->father_name);
                fprintf(fp1, "ball1 : %d  ", temp->ball1);
                fprintf(fp1, "ball2 : %d  ", temp->ball2);
                fprintf(fp1, "ball3 : %d  ", temp->ball3);
                fprintf(fp1, "school grade : %d  ", temp->ball_school);
                fprintf(fp1, "passport : %s  ", temp->father_name);
                fprintf(fp1, "place : %s  ", temp->father_name);
                fprintf(fp1, "school number : %d  ", temp->school_number);
                fprintf(fp1,"\n");
                temp = temp->next;
            }
            fclose(fp1);

        }else if(strcmp(command, "help") == 0){
            //printf("Create application, view result");
            FILE *fp3;
            //fp = fopen("/Users/victoriasviridchik/CLionProjects/2sem_lab6/faculties", "r");
            fp3 = fopen("/Users/victoriasviridchik/CLionProjects/2sem_lab6/backup", "w");
            fp1 = fopen("/Users/victoriasviridchik/CLionProjects/2sem_lab6/application_data", "r");

            if (fp3 == NULL || fp1 == NULL)
            {
                printf("It looks like there are some problems \n");
                return 0;
            }

show(Specialty);
show_app(ABITURIENTS);
int ii =0;

/*for (ii = 0; ii<35; ii++){
    printf("id:%d  amount:%d",ii,amount_applications_by_specialty[ii]);
    printf("\n");
}*/

            char str1[255];
while (!feof(fp1)){

    fgets(str1, sizeof(str1),fp1);
    printf("%s\n",str1);
    fprintf(fp3, "Name : %s  ", str1);

}
            fclose(fp3);
        }

    }
    return 0;
}