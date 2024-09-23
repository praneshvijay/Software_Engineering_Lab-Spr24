#include "social.h"

// Global Variables

#define MAX_NODES 100
struct node* set_of_nodes[MAX_NODES];
int node_counter = 0;

link* createLink(int id, int type){
    link* newlink = (link*)malloc(sizeof(link));
    newlink->id = id;
    newlink->type = type;
    newlink->next = NULL;
    return newlink;
}   

void createsetofnodes(){
    for (int i = 0; i < 99; i++)
    {
        set_of_nodes[i] = NULL;
    }
    return;
}

void printindvdetails(int id){
    printf("ID: %d\n", set_of_nodes[id]->id);
    printf("Node Type: Individual\n");
    printf("Name: %s\n", set_of_nodes[id]->name);
    if(strcmp(set_of_nodes[id]->structure.indv.birthday, "") != 0) printf("Birthday: %s\n", set_of_nodes[id]->structure.indv.birthday);
    link* temp = set_of_nodes[id]->structure.indv.ownerofbusinesses;
    printf("Owners of Businesses: ");
    if(temp==NULL){
        printf("None ");
    }
    while(temp != NULL){
        printf("%s ", set_of_nodes[temp->id]->name);
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.indv.customersofbusinesses;
    printf("\nCustomers of Businesses: ");
    if(temp==NULL){
        printf("None ");
    }
    while(temp != NULL){
        printf("%s ", set_of_nodes[temp->id]->name);
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.indv.membersofgroups;
    printf("\nMembers of Groups: ");
    if(temp==NULL){
       printf("None ");
    }
    while(temp != NULL){
        printf("%s ", set_of_nodes[temp->id]->name);
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.indv.membersoforganisations;
    printf("\nMembers of Organisations: ");
    if(temp==NULL){
        printf("None ");
    }
    while(temp != NULL){
        printf("%s ", set_of_nodes[temp->id]->name);
        temp = temp->next;
    }
    printf("\nContent Posted: ");
    if(set_of_nodes[id]->posts == 0) printf("None");
    else{
        for(int i=0; i<set_of_nodes[id]->posts; i++){
            printf("%s ", set_of_nodes[id]->content[i]);
        }
    }
    printf("\nCreation Date: %s", ctime(&set_of_nodes[id]->creation_date));
    printf("\n");
    return;
}

void printbisdetails(int id){
    printf("ID: %d\n", set_of_nodes[id]->id);
    printf("Node Type: Business\n");
    printf("Name: %s\n", set_of_nodes[id]->name);
    printf("Location: (%lf, %lf)\n", set_of_nodes[id]->structure.bis.location.x, set_of_nodes[id]->structure.bis.location.y);
    link* temp = set_of_nodes[id]->structure.bis.owners;
    printf("Owners: ");
    if(temp==NULL){
        printf("None ");
    }
    while(temp != NULL){
        printf("%s ", set_of_nodes[temp->id]->name);
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.bis.customers;
    printf("\nCustomers: ");
    if(temp==NULL){
        printf("None ");
    }
    while(temp != NULL){
        printf("%s ", set_of_nodes[temp->id]->name);
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.bis.memberofgroups;
    printf("\nMember of Groups: ");
    if(temp==NULL){
        printf("None ");
    }
    while(temp != NULL){
        printf("%s ", set_of_nodes[temp->id]->name);
        temp = temp->next;
    }
    printf("\nContent Posted: ");
    if(set_of_nodes[id]->posts == 0) printf("None");
    else{
        for(int i=0; i<set_of_nodes[id]->posts; i++){
            printf("%s ", set_of_nodes[id]->content[i]);
        }
    }
    printf("\nCreation Date: %s", ctime(&set_of_nodes[id]->creation_date));
    printf("\n");
    return;
}

void printorgdetails(int id){
    printf("ID: %d\n", set_of_nodes[id]->id);
    printf("Node Type: Organisation\n");
    printf("Name: %s\n", set_of_nodes[id]->name);
    printf("Location: (%lf, %lf)\n", set_of_nodes[id]->structure.org.location.x, set_of_nodes[id]->structure.org.location.y);
    link* temp = set_of_nodes[id]->structure.org.members;
    printf("Members: ");
    if(temp==NULL){
        printf("None ");
    }
    while(temp != NULL){
        printf("%s ", set_of_nodes[temp->id]->name);
        temp = temp->next;
    }
    printf("\nContent Posted: ");
    if(set_of_nodes[id]->posts == 0) printf("None");
    else{
        for(int i=0; i<set_of_nodes[id]->posts; i++){
            printf("%s ", set_of_nodes[id]->content[i]);
        }
    }
    printf("\nCreation Date: %s", ctime(&set_of_nodes[id]->creation_date));
    printf("\n");
    return;
}

void printgrpdetails(int id){
    printf("ID: %d\n", set_of_nodes[id]->id);
    printf("Node Type: Group\n");
    printf("Name: %s\n", set_of_nodes[id]->name);
    link* temp = set_of_nodes[id]->structure.grp.members;
    printf("Members: ");
    if(temp==NULL){
        printf("None ");
    }
    while(temp != NULL){
        printf("%s ", set_of_nodes[temp->id]->name);
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.grp.businesses;
    printf("\nBusinesses: ");
    if(temp==NULL){
        printf("None ");
    }
    while(temp != NULL){
        printf("%s ", set_of_nodes[temp->id]->name);
        temp = temp->next;
    }
    printf("\nContent Posted: ");
    if(set_of_nodes[id]->posts == 0) printf("None");
    else{
        for(int i=0; i<set_of_nodes[id]->posts; i++){
            printf("%s ", set_of_nodes[id]->content[i]);
        }
    }
    printf("\nCreation Date: %s", ctime(&set_of_nodes[id]->creation_date));
    printf("\n");
    return;
}

void printnode(int id){
    printf("\n");
    if(set_of_nodes[id] == NULL){
        printf("Node does not exist\n");
        return;
    }
    if(set_of_nodes[id]->type == 1){
        printindvdetails(id);
    }
    else if(set_of_nodes[id]->type == 2){
        printbisdetails(id);
    }
    else if(set_of_nodes[id]->type == 3){
        printorgdetails(id);
    }
    else if(set_of_nodes[id]->type == 4){
        printgrpdetails(id);
    }
    return;
}

void printallnodes(){
    for (int i = 0; i < 99; i++)
    {
        if(set_of_nodes[i] != NULL){
            printnode(i);
        }
    }
    return;
}

void displayallindividuals(){
    for (int i = 0; i < 99; i++)
    {
        if(set_of_nodes[i] != NULL){
            if(set_of_nodes[i]->type == 1){
                printnode(i);
            }
        }
    }
    return;
}

void displayallbusinesses(){
    for (int i = 0; i < 99; i++)
    {
        if(set_of_nodes[i] != NULL){
            if(set_of_nodes[i]->type == 2){
                printnode(i);
            }
        }
    }
    return;
}

void displayallorganisations(){
    for (int i = 0; i < 99; i++)
    {
        if(set_of_nodes[i] != NULL){
            if(set_of_nodes[i]->type == 3){
                printnode(i);
            }
        }
    }
    return;
}

void displayallgroups(){
    for (int i = 0; i < 99; i++)
    {
        if(set_of_nodes[i] != NULL){
            if(set_of_nodes[i]->type == 4){
                printnode(i);
            }
        }
    }
    return;
}

void deleteindividual(int id){
    if(set_of_nodes[id] == NULL){
        printf("Node does not exist\n");
        return;
    }
    if(set_of_nodes[id]->type != 1){
        printf("Node is not an individual\n");
        return;
    }
    link* temp = set_of_nodes[id]->structure.indv.ownerofbusinesses;
    while(temp != NULL){
        link* temp2 = set_of_nodes[temp->id]->structure.bis.owners;
        if(temp2->id == id){
            set_of_nodes[temp->id]->structure.bis.owners = temp2->next;
            free(temp2);
        }
        else{
            while(temp2->next->id != id){
                temp2 = temp2->next;
            }
            link* temp3 = temp2->next;
            temp2->next = temp3->next;
            free(temp3);
        }
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.indv.customersofbusinesses;
    while(temp != NULL){
        link* temp2 = set_of_nodes[temp->id]->structure.bis.customers;
        if(temp2->id == id){
            set_of_nodes[temp->id]->structure.bis.customers = temp2->next;
            free(temp2);
        }
        else{
            while(temp2->next->id != id){
                temp2 = temp2->next;
            }
            link* temp3 = temp2->next;
            temp2->next = temp3->next;
            free(temp3);
        }
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.indv.membersofgroups;
    while(temp != NULL){
        link* temp2 = set_of_nodes[temp->id]->structure.grp.members;
        if(temp2->id == id){
            set_of_nodes[temp->id]->structure.grp.members = temp2->next;
            free(temp2);
        }
        else{
            while(temp2->next->id != id){
                temp2 = temp2->next;
            }
            link* temp3 = temp2->next;
            temp2->next = temp3->next;
            free(temp3);
        }
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.indv.membersoforganisations;
    while(temp != NULL){
        link* temp2 = set_of_nodes[temp->id]->structure.org.members;
        if(temp2->id == id){
            set_of_nodes[temp->id]->structure.org.members = temp2->next;
            free(temp2);
        }
        else{
            while(temp2->next->id != id){
                temp2 = temp2->next;
            }
            link* temp3 = temp2->next;
            temp2->next = temp3->next;
            free(temp3);
        }
        temp = temp->next;
    }
    free(set_of_nodes[id]);
    set_of_nodes[id] = NULL;
    return;
}

void deletegroup(int id){
    if(set_of_nodes[id] == NULL){
        printf("Node does not exist\n");
        return;
    }
    if(set_of_nodes[id]->type != 4){
        printf("Node is not a group\n");
        return;
    }
    link* temp = set_of_nodes[id]->structure.grp.members;
    while(temp != NULL){
        link* temp2 = set_of_nodes[temp->id]->structure.indv.membersofgroups;
        if(temp2->id == id){
            set_of_nodes[temp->id]->structure.indv.membersofgroups = temp2->next;
            free(temp2);
        }
        else{
            while(temp2->next->id != id){
                temp2 = temp2->next;
            }
            link* temp3 = temp2->next;
            temp2->next = temp3->next;
            free(temp3);
        }
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.grp.businesses;
    while(temp != NULL){
        link* temp2 = set_of_nodes[temp->id]->structure.bis.memberofgroups;
        if(temp2->id == id){
            set_of_nodes[temp->id]->structure.bis.memberofgroups = temp2->next;
            free(temp2);
        }
        else{
            while(temp2->next->id != id){
                temp2 = temp2->next;
            }
            link* temp3 = temp2->next;
            temp2->next = temp3->next;
            free(temp3);
        }
        temp = temp->next;
    }
    free(set_of_nodes[id]);
    set_of_nodes[id] = NULL;
    return;
}

void deletebusiness(int id){
    if(set_of_nodes[id] == NULL){
        printf("Node does not exist\n");
        return;
    }
    if(set_of_nodes[id]->type != 2){
        printf("Node is not a business\n");
        return;
    }
    link* temp = set_of_nodes[id]->structure.bis.owners;
    while(temp != NULL){
        link* temp2 = set_of_nodes[temp->id]->structure.indv.ownerofbusinesses;
        if(temp2->id == id){
            set_of_nodes[temp->id]->structure.indv.ownerofbusinesses = temp2->next;
            free(temp2);
        }
        else{
            while(temp2->next->id != id){
                temp2 = temp2->next;
            }
            link* temp3 = temp2->next;
            temp2->next = temp3->next;
            free(temp3);
        }
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.bis.customers;
    while(temp != NULL){
        link* temp2 = set_of_nodes[temp->id]->structure.indv.customersofbusinesses;
        if(temp2->id == id){
            set_of_nodes[temp->id]->structure.indv.customersofbusinesses = temp2->next;
            free(temp2);
        }
        else{
            while(temp2->next->id != id){
                temp2 = temp2->next;
            }
            link* temp3 = temp2->next;
            temp2->next = temp3->next;
            free(temp3);
        }
        temp = temp->next;
    }
    temp = set_of_nodes[id]->structure.bis.memberofgroups;
    while(temp != NULL){
        link* temp2 = set_of_nodes[temp->id]->structure.grp.businesses;
        if(temp2->id == id){
            set_of_nodes[temp->id]->structure.grp.businesses = temp2->next;
            free(temp2);
        }
        else{
            while(temp2->next->id != id){
                temp2 = temp2->next;
            }
            link* temp3 = temp2->next;
            temp2->next = temp3->next;
            free(temp3);
        }
        temp = temp->next;
    }
    free(set_of_nodes[id]);
    set_of_nodes[id] = NULL;
    return;
}

void deleteorganization(int id){
    if(set_of_nodes[id] == NULL){
        printf("Node does not exist\n");
        return;
    }
    if(set_of_nodes[id]->type != 3){
        printf("Node is not an organisation\n");
        return;
    }
    link* temp = set_of_nodes[id]->structure.org.members;
    while(temp != NULL){
        link* temp2 = set_of_nodes[temp->id]->structure.indv.membersoforganisations;
        if(temp2->id == id){
            set_of_nodes[temp->id]->structure.indv.membersoforganisations = temp2->next;
            free(temp2);
        }
        else{
            while(temp2->next->id != id){
                temp2 = temp2->next;
            }
            link* temp3 = temp2->next;
            temp2->next = temp3->next;
            free(temp3);
        }
        temp = temp->next;
    }
    free(set_of_nodes[id]);
    set_of_nodes[id] = NULL;
    return;
}

void deletenode(int id){
    if(set_of_nodes[id] == NULL){
        printf("Node does not exist\n");
        return;
    }
    if(set_of_nodes[id]->type == 1){
        deleteindividual(id);
    }
    else if(set_of_nodes[id]->type == 2){
        deletebusiness(id);
    }
    else if(set_of_nodes[id]->type == 3){
        deleteorganization(id);
    }
    else if(set_of_nodes[id]->type == 4){
        deletegroup(id);
    }
    return;
}

void searchbyname(){
    char name[50];
    bool namematch[99];
    for (int i = 0; i < 99; i++)
    {
        namematch[i]=false;
    }
    printf("Search: ");
    scanf(" %[^\n]s", name);
    for (int i = 0; i < 99; i++)
    {
        if(set_of_nodes[i] != NULL){
            //Check if name is a substring of the node name
            if(strstr(set_of_nodes[i]->name, name) != NULL){
                namematch[i]=true;
            }
        }
    }
    for (int i = 0; i < 99; i++)
    {
        if(namematch[i]){
            printnode(i);
        }
    }
    return;
}

void searchbytype(){
    int type;
    printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
    printf("Enter the type: ");
    scanf("%d", &type);
    for (int i = 0; i < 99; i++)
    {
        if(set_of_nodes[i] != NULL){
            if(set_of_nodes[i]->type == type){
                printnode(i);
            }
        }
    }
}

void searchbybday(){
    char bday[10];
    printf("Enter the birthday (dd-mm-yyyy): ");
    scanf(" %s", bday);
    for (int i = 0; i < 99; i++)
    {
        if(set_of_nodes[i] != NULL){
            if(strcmp(set_of_nodes[i]->structure.indv.birthday, bday) == 0){
                printnode(i);
            }
        }
    }
    return;
}

void searchmenu(){
    printf("\n1. Search by name\n2. Search by type\n3. Search by birthday\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    if(choice == 1){
        searchbyname();
    }
    else if(choice == 2){
        searchbytype();
    }
    else if(choice == 3){
        searchbybday();
    }
    else{
        printf("Invalid choice\n");
    }
    return;
}

void link_indv_to_grp(int id_of_indv, int id_of_grp){
    if(set_of_nodes[id_of_indv] == NULL){
        printf("Individual does not exist\n");
        return;
    }
    if(set_of_nodes[id_of_indv]->type != 1){
        printf("Node is not an individual\n");
        return;
    }
    link* newlink = createLink(id_of_grp, 4);
    if(set_of_nodes[id_of_indv]->structure.indv.membersofgroups == NULL){
        set_of_nodes[id_of_indv]->structure.indv.membersofgroups = newlink;
    }
    else{
        link* temp = set_of_nodes[id_of_indv]->structure.indv.membersofgroups;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newlink;
    }
    newlink = createLink(id_of_indv, 1);
    if(set_of_nodes[id_of_grp]->structure.grp.members == NULL){
        set_of_nodes[id_of_grp]->structure.grp.members = newlink;
    }
    else{
        link* temp = set_of_nodes[id_of_grp]->structure.grp.members;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newlink;
    }
    return;
}

void link_indv_as_customer_to_business(int id_of_indv, int id_of_business){
    if(set_of_nodes[id_of_indv] == NULL){
        printf("Individual does not exist\n");
        return;
    }
    if(set_of_nodes[id_of_indv]->type != 1){
        printf("Node is not an individual\n");
        return;
    }
    link* newlink = createLink(id_of_business, 2);
    if(set_of_nodes[id_of_indv]->structure.indv.customersofbusinesses == NULL){
        set_of_nodes[id_of_indv]->structure.indv.customersofbusinesses = newlink;
    }
    else{
        link* temp = set_of_nodes[id_of_indv]->structure.indv.customersofbusinesses;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newlink;
    }
    newlink = createLink(id_of_indv, 1);
    if(set_of_nodes[id_of_business]->structure.bis.customers == NULL){
        set_of_nodes[id_of_business]->structure.bis.customers = newlink;
    }
    else{
        link* temp = set_of_nodes[id_of_business]->structure.bis.customers;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newlink;
    }
    return;
}

void link_indv_as_owner_of_business(int id_of_indv, int id_of_business){
    if(set_of_nodes[id_of_indv] == NULL){
        printf("Individual does not exist\n");
        return;
    }
    if(set_of_nodes[id_of_indv]->type != 1){
        printf("Node is not an individual\n");
        return;
    }
    link* newlink = createLink(id_of_business, 2);
    if(set_of_nodes[id_of_indv]->structure.indv.ownerofbusinesses == NULL){
        set_of_nodes[id_of_indv]->structure.indv.ownerofbusinesses = newlink;
    }
    else{
        link* temp = set_of_nodes[id_of_indv]->structure.indv.ownerofbusinesses;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newlink;
    }
    newlink = createLink(id_of_indv, 1);
    if(set_of_nodes[id_of_business]->structure.bis.owners == NULL){
        set_of_nodes[id_of_business]->structure.bis.owners = newlink;
    }
    else{
        link* temp = set_of_nodes[id_of_business]->structure.bis.owners;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newlink;
    }
    return;
}

void link_indv_to_org(int id_of_indv, int id_of_org){
    if(set_of_nodes[id_of_indv] == NULL){
        printf("Individual does not exist\n");
        return;
    }
    if(set_of_nodes[id_of_indv]->type != 1){
        printf("Node is not an individual\n");
        return;
    }
    link* newlink = createLink(id_of_org, 3);
    if(set_of_nodes[id_of_indv]->structure.indv.membersoforganisations == NULL){
        set_of_nodes[id_of_indv]->structure.indv.membersoforganisations = newlink;
    }
    else{
        link* temp = set_of_nodes[id_of_indv]->structure.indv.membersoforganisations;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newlink;
    }
    newlink = createLink(id_of_indv, 1);
    if(set_of_nodes[id_of_org]->structure.org.members == NULL){
        set_of_nodes[id_of_org]->structure.org.members = newlink;
    }
    else{
        link* temp = set_of_nodes[id_of_org]->structure.org.members;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newlink;
    }
    return;
}

void link_business_to_group(int id_of_business, int id_of_group){
    if(set_of_nodes[id_of_business] == NULL){
        printf("Business does not exist\n");
        return;
    }
    if(set_of_nodes[id_of_business]->type != 2){
        printf("Node is not a business\n");
        return;
    }
    link* newlink = createLink(id_of_group, 4);
    if(set_of_nodes[id_of_business]->structure.bis.memberofgroups == NULL){
        set_of_nodes[id_of_business]->structure.bis.memberofgroups = newlink;
    }
    else{
        link* temp = set_of_nodes[id_of_business]->structure.bis.memberofgroups;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newlink;
    }
    newlink = createLink(id_of_business, 2);
    if(set_of_nodes[id_of_group]->structure.grp.businesses == NULL){
        set_of_nodes[id_of_group]->structure.grp.businesses = newlink;
    }
    else{
        link* temp = set_of_nodes[id_of_group]->structure.grp.businesses;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newlink;
    }
    return;
}

void createnodemenu(){
    printf("\n1. Individual\n2. Business\n3. Organisation\n4. Group\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    if(!(choice>0 && choice <5)){
        printf("Invalid Choice!! \n");
        return;
    }
    node* newNode = (struct node*)malloc(sizeof(struct node));
    node_counter++;
    newNode->id = node_counter;
    newNode->creation_date = time(NULL);
    printf("Enter the name: ");
    scanf(" %[^\n]s", newNode->name);
    newNode->type = choice;
    set_of_nodes[newNode->id] = newNode;
    newNode->posts = 0;
    for (int i = 0; i < 100; i++)
    {
        newNode->content[i] = NULL;
    }
    if(choice == 1){
        newNode->structure.indv.birthday[0] = '\0';
        char ch;
        printf("Do you want to enter the birthday? (Y/N): ");   
        scanf(" %c", &ch);
        if(ch == 'Y'){
            printf("Enter the birthday (dd-mm-yyyy): ");
            scanf(" %s", newNode->structure.indv.birthday);
        }   
        newNode->structure.indv.ownerofbusinesses = NULL;
        newNode->structure.indv.customersofbusinesses = NULL;
        newNode->structure.indv.membersofgroups = NULL;
        newNode->structure.indv.membersoforganisations = NULL;
        printf("Do you want to link this individual to a group? (Y/N): ");
        scanf(" %c", &ch);
        if(ch == 'Y'){
            printf("Available groups:\n");
            displayallgroups();
            printf("Enter the number of groups you want to link this individual to: ");
            int n;
            scanf("%d", &n);
            printf("Enter the ids of the groups: ");
            for (int i = 0; i < n; i++)
            {
                int id;
                scanf("%d", &id);
                link_indv_to_grp(newNode->id, id);
            }
        }
        printf("Do you want to link this individual to a business as a customer? (Y/N): ");
        scanf(" %c", &ch);
        if(ch == 'Y'){
            printf("Available businesses:\n");
            displayallbusinesses();
            printf("Enter the number of businesses you want to link this individual as a customer to: ");
            int n;
            scanf("%d", &n);
            printf("Enter the ids of the businesses: ");
            for (int i = 0; i < n; i++)
            {
                int id;
                scanf("%d", &id);
                link_indv_as_customer_to_business(newNode->id, id);
            }
        }

        printf("Do you want to link this individual to a business as an owner? (Y/N): ");
        scanf(" %c", &ch);
        if(ch == 'Y'){
            printf("Available businesses:\n");
            displayallbusinesses();
            printf("Enter the number of businesses you want to link this individual as an owner to: ");
            int n;
            scanf("%d", &n);
            printf("Enter the ids of the businesses: ");
            for (int i = 0; i < n; i++)
            {
                int id;
                scanf("%d", &id);
                link_indv_as_owner_of_business(newNode->id, id);
            }
        }

        printf("Do you want to link this individual to an organisation? (Y/N): ");
        scanf(" %c", &ch);
        if(ch == 'Y'){
            printf("Available organisations:\n");
            displayallorganisations();
            printf("Enter the number of organisations you want to link this individual to: ");
            int n;
            scanf("%d", &n);
            printf("Enter the ids of the organisations: ");
            for (int i = 0; i < n; i++)
            {
                int id;
                scanf("%d", &id);
                link_indv_to_org(newNode->id, id);
            }
        }
    }
    else if(choice == 2){
        newNode->structure.bis.owners = NULL;
        newNode->structure.bis.customers = NULL;
        printf("Enter the x coordinate of the location: ");
        scanf("%lf", &newNode->structure.bis.location.x);
        printf("Enter the y coordinate of the location: ");
        scanf("%lf", &newNode->structure.bis.location.y);
        printf("Do you want to link this business to a group? (Y/N): ");
        char ch;
        scanf(" %c", &ch);
        if(ch == 'Y'){
            printf("Available groups:\n");
            displayallgroups();
            printf("Enter the number of groups you want to link this business to: ");
            int n;
            scanf("%d", &n);
            printf("Enter the ids of the groups: ");
            for (int i = 0; i < n; i++)
            {
                int id;
                scanf("%d", &id);
                link_business_to_group(newNode->id, id);
            }
        }
        printf("Do you want to add owners to this business? (Y/N): ");
        scanf(" %c", &ch);
        if(ch == 'Y'){
            printf("Available individuals:\n");
            displayallindividuals();
            printf("Enter the number of owners you want to add to this business: ");
            int n;
            scanf("%d", &n);
            printf("Enter the ids of the owners: ");
            for (int i = 0; i < n; i++)
            {
                int id;
                scanf("%d", &id);
                link_indv_as_owner_of_business(id, newNode->id);
            }
        }
        printf("Do you want to add customers to this business? (Y/N): ");
        scanf(" %c", &ch);
        if(ch == 'Y'){
            printf("Available individuals:\n");
            displayallindividuals();
            printf("Enter the number of customers you want to add to this business: ");
            int n;
            scanf("%d", &n);
            printf("Enter the ids of the customers: ");
            for (int i = 0; i < n; i++)
            {
                int id;
                scanf("%d", &id);
                link_indv_as_customer_to_business(id, newNode->id);
            }
        }
    }
    else if(choice == 3){
        newNode->structure.org.members = NULL;
        printf("Enter the x coordinate of the location: ");
        scanf("%lf", &newNode->structure.org.location.x);
        printf("Enter the y coordinate of the location: ");
        scanf("%lf", &newNode->structure.org.location.y);
        printf("Do you want to add members to this organisation? (Y/N): ");
        char ch;
        scanf(" %c", &ch);
        if(ch == 'Y'){
            printf("Available individuals:\n");
            displayallindividuals();
            printf("Enter the number of members you want to add to this organisation: ");
            int n;
            scanf("%d", &n);
            printf("Enter the ids of the members: ");
            for (int i = 0; i < n; i++)
            {
                int id;
                scanf("%d", &id);
                link_indv_to_org(id, newNode->id);
            }
        }
    }
    else if(choice == 4){
        newNode->structure.grp.members = NULL;
        newNode->structure.grp.businesses = NULL;
        printf("Do you want to add members to this group? (Y/N): ");
        char ch;
        scanf(" %c", &ch);
        if(ch == 'Y'){
            printf("Available individuals:\n");
            displayallindividuals();
            printf("Enter the number of members you want to add to this group: ");
            int n;
            scanf("%d", &n);
            printf("Enter the ids of the members: ");
            for (int i = 0; i < n; i++)
            {
                int id;
                scanf("%d", &id);
                link_indv_to_grp(id, newNode->id);
            }
        }
        printf("Do you want to add businesses to the group? (Y/N): ");
        scanf(" %c", &ch);
        if(ch == 'Y'){
            printf("Available businesses:\n");
            displayallbusinesses();
            printf("Enter the number of businesses you want to add to the group: ");
            int n;
            scanf("%d", &n);
            printf("Enter the ids of the businesses: ");
            for (int i = 0; i < n; i++)
            {
                int id;
                scanf("%d", &id);
                link_business_to_group(id, newNode->id);
            }
        }
    }
    printf("\nNode created successfully with id %d\n", newNode->id);
    return;
}

void printlinkednodes(int id){
    if(set_of_nodes[id] == NULL){
        printf("Node does not exist\n");
        return;
    }

    if(set_of_nodes[id]->type == 1){
        link* temp = set_of_nodes[id]->structure.indv.ownerofbusinesses;
        while(temp != NULL){
            printnode(temp->id);
            temp = temp->next;
        }
        temp = set_of_nodes[id]->structure.indv.customersofbusinesses;
        while(temp != NULL){
            printnode(temp->id);
            temp = temp->next;
        }
        temp = set_of_nodes[id]->structure.indv.membersofgroups;
        while(temp != NULL){
            printnode(temp->id);
            temp = temp->next;
        }
        temp = set_of_nodes[id]->structure.indv.membersoforganisations;
        while(temp != NULL){
            printnode(temp->id);
            temp = temp->next;
        }
    }
    else if(set_of_nodes[id]->type == 2){
        link* temp = set_of_nodes[id]->structure.bis.owners;
        while(temp != NULL){
            printnode(temp->id);
            temp = temp->next;
        }
        temp = set_of_nodes[id]->structure.bis.customers;
        while(temp != NULL){
            printnode(temp->id);
            temp = temp->next;
        }
        temp = set_of_nodes[id]->structure.bis.memberofgroups;
        while(temp != NULL){
            printnode(temp->id);
            temp = temp->next;
        }
    }
    else if(set_of_nodes[id]->type == 3){
        link* temp = set_of_nodes[id]->structure.org.members;
        while(temp != NULL){
            printnode(temp->id);
            temp = temp->next;
        }
    }
    else if(set_of_nodes[id]->type == 4){
        link* temp = set_of_nodes[id]->structure.grp.members;
        while(temp != NULL){
            printnode(temp->id);
            temp = temp->next;
        }
        temp = set_of_nodes[id]->structure.grp.businesses;
        while(temp != NULL){
            printnode(temp->id);
            temp = temp->next;
        }
    }
    printf("\n");
    return;
}

void createandpostcontent(int id){
    //Check if the node exists
    if(set_of_nodes[id] == NULL){
        printf("Node does not exist\n");
        return;
    }
    printf("Enter the content to post: ");
    char content[100];
    scanf(" %[^\n]s", content);
    //Allocate memory for the content and add it to the node
    set_of_nodes[id]->content[set_of_nodes[id]->posts] = (char*)malloc(sizeof(char)*100);
    //Copy the content to the node's content array as the next post
    strcpy(set_of_nodes[id]->content[set_of_nodes[id]->posts], content);
    set_of_nodes[id]->posts++;
    printf("Content posted successfully\n");
    return;
}

void searchbycontent(){
    char content[100];
    bool contentpresent[MAX_NODES];
    //Initialize all nodes to false
    for(int i=0; i<MAX_NODES; i++) contentpresent[i] = false;
    printf("Search for content: ");
    scanf(" %[^\n]s", content);
    // Iterate through all nodes and print the node if the node contains the content as a substring
    for (int i = 0; i < 99; i++)
    {
        if(set_of_nodes[i] != NULL){
            if(set_of_nodes[i]->posts > 0){
                //Iterate through all posts of the node
                for (int j = 0; j < set_of_nodes[i]->posts; j++)
                {
                    //Check if the content is a substring of the post
                    if(strstr(set_of_nodes[i]->content[j], content) != NULL){
                        contentpresent[i] = true;
                        break;
                    }
                }
            }
        }
    }

    //Print all the nodes that contain the content as a substring
    for (int i = 0; i < 99; i++)
    {
        if(contentpresent[i]){
            printnode(i);
        }
    }
    return;
}

void displaycontentpostedbylinkedindividuals(int id){ 
    bool connected[MAX_NODES];
    for(int i=0; i<MAX_NODES; i++) connected[i] = false;
    //Check if the node exists
    if(set_of_nodes[id] == NULL){
        printf("Node does not exist\n");
        return;
    }
    //Check if the node is an individual
    if(set_of_nodes[id]->type!=1){
        printf("This ID is not an individual \n");
    }
    else{
        //Iterate through all the groups linked to the individual
        link *temp = set_of_nodes[id]->structure.indv.membersofgroups;
        while(temp != NULL){
            //Iterate through all the members of the group
            link* temp1 = set_of_nodes[temp->id]->structure.grp.members;
            while(temp1 != NULL){
                connected[temp1->id] = true;
                temp1 = temp1->next;
            }
            temp = temp->next;
        }

        //Iterate through all the organisations linked to the individual
        temp = set_of_nodes[id]->structure.indv.membersoforganisations;
        while(temp != NULL){
            //Iterate through all the members of the organisation
            link *temp2 = set_of_nodes[temp->id]->structure.org.members;
            while(temp2 != NULL){
                connected[temp2->id] = true;
                temp2 = temp2->next;
            }
            temp = temp->next;
        }

    }
    //Print all the content posted by the linked individuals
    for(int i=0; i<MAX_NODES; i++){
        if(i == id) continue;
        if(connected[i]){
            for(int j=0; j<set_of_nodes[i]->posts; j++){
                printf("%s ", set_of_nodes[i]->content[j]);
            }
            printf("\n");
        }
    }
    return;
}

/*
 * @brief Main function to execute the Social Network program.
 *
 * This function displays a menu-driven interface for users to interact with the Social Network.
 * Users can create/delete nodes, search nodes, print linked nodes, create and post content,
 * search content, and display content posted by linked individuals through common groups or organizations.
 */
int main(){
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("-------------------------------------------Welcome to the Social Network-----------------------------------------\n");
    
    int choice;
    do{
        printf("-----------------------------------------------------------------------------------------------------------------\n");
        printf("1. Create a node\n2. Delete a node\n3. Search for a node\n4. Print all 1-hop linked nodes to a given input node\n5. Create and post content by a node\n6. Search for content posted by any node\n7. Display all content posted by individuals linked to a given individual through a common group or organization. \n8. Print all nodes\n9. Exit\n");
        printf("-----------------------------------------------------------------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if(choice == 1){
            createnodemenu();
        }
        else if(choice == 2){
            printf("Enter the id of the node you want to delete: ");
            int id;
            scanf("%d", &id);
            deletenode(id);
        }
        else if(choice == 3){
            searchmenu();
        }
        else if(choice == 4){
            printf("Enter the id of the node: ");
            int id;
            scanf("%d", &id);
            printlinkednodes(id);
        }
        else if(choice == 5){
            printf("Enter the id of the node: ");
            int id;
            scanf("%d", &id);
            createandpostcontent(id);
        }
        else if(choice == 6){
            searchbycontent();
        }
        else if(choice == 7){
            printf("Enter the id of the node: ");
            int id;
            scanf("%d", &id);
            displaycontentpostedbylinkedindividuals(id);
        }
        else if(choice == 8){
            printallnodes();
        }
        else if(choice == 9){
            printf("Thank you for using the Social Network\n");
            break;
        }
        else{
            printf("Invalid choice\n");
        }
    }while(choice != 9);
    return 0;
}