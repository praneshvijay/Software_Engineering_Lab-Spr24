/*
    Name: Pranesh Vijay
    Roll No: 22CS10013
    Assignment 1
    Social Network
*/

/*
Structures:
- link: Represents a link between nodes in the social network, storing the linked node's ID, type, and a pointer to the next linked node.
- point: Represents a 2D point with x and y coordinates.
- Individual: Represents an individual node in the social network, including details such as birthday and linked lists for businesses owned, businesses as customers, groups, and organizations.
- Business: Represents a business node in the social network, including location, and linked lists for owners, customers, and groups.
- Organisation: Represents an organization node in the social network, including location and a linked list of members.
- Group: Represents a group node in the social network, including linked lists for members and businesses.

- node: Represents a general node in the social network, containing common attributes like ID, type, creation date, posts count, name, and an embedded union for type-specific information.

Functions:
- createLink: Creates a link between two nodes.
- createsetofnodes: Initializes the set_of_nodes array by setting each element to NULL.
- printindvdetails, printbisdetails, printorgdetails, printgrpdetails: Print details of individual, business, organization, and group nodes, respectively.
- printnode: Prints details of a node based on its type.
- printallnodes, displayallindividuals, displayallbusinesses, displayallorganisations, displayallgroups: Display details of all nodes, individual nodes, business nodes, organization nodes, and group nodes, respectively.
- deleteindividual, deletegroup, deletebusiness, deleteorganization: Deletes nodes of specific types and their relationships from the graph.
- deletenode: Deletes a node based on its type.
- searchbyname, searchbytype, searchbybday: Searches for nodes by name, type, or birthday and prints details of matching nodes.
- searchmenu: Displays a menu for searching nodes based on different criteria.
- link_indv_to_grp, link_indv_as_customer_to_business, link_indv_as_owner_of_business, link_indv_to_org, link_business_to_group: Links nodes of different types, updating relationships in the graph.
- createnodemenu: Creates a new node based on user input, allowing them to specify the node type and relevant details.
- printlinkednodes: Prints all nodes linked to the specified node based on its type.
- createandpostcontent: Creates and posts content to the specified node.
- searchbycontent: Searches for nodes containing a specified content substring and prints them.
- displaycontentpostedbylinkedindividuals: Displays content posted by individuals linked to a given individual through common groups or organizations.
 
NOTE: Each functions has more detailed explanation before its prototype definition.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Structure for a link in the Social Network
typedef struct link {
    int id;               // ID of the linked node
    int type;             // Type of the linked node (1: Individual, 2: Business, 3: Organisation, 4: Group)
    struct link* next;    // Pointer to the next linked node
} link;

// Structure for representing 2D Point
typedef struct {
    double x;    // x-coordinate
    double y;    // y-coordinate
} point;

// Structure for an Individual in the Social Network
struct Individual {
    char birthday[10];          // Birthday of the individual DD-MM-YYYY format 
    link* ownerofbusinesses;    // Linked list of businesses owned by the individual
    link* customersofbusinesses;// Linked list of businesses where the individual is a customer
    link* membersofgroups;      // Linked list of groups to which the individual belongs
    link* membersoforganisations; // Linked list of organisations to which the individual belongs
};

// Structure for a Business in the Social Network
struct Business {
    point location;           // Location of the business in 2D space
    link* owners;              // Linked list of individuals who own the business
    link* customers;           // Linked list of individuals who are customers of the business
    link* memberofgroups;      // Linked list of groups to which the business belongs
};

// Structure for an Organisation in the Social Network
struct Organisation {
    point location;           // Location of the organisation in 2D space
    link* members;             // Linked list of individuals who are members of the organisation
};

// Structure for a Group in the Social Network
struct Group {
    link* members;             // Linked list of individuals who are members of the group
    link* businesses;          // Linked list of businesses that are part of the group
};

// Structure for representing a node in the Social Network
typedef struct node {
    int id;                    // Unique identifier for the node
    int type;                  // Type of the node (1: Individual, 2: Business, 3: Organisation, 4: Group)
    time_t creation_date;      // Timestamp for the creation date of the node
    int posts;                 // Number of posts made by the node
    char name[50];             // Name of the node
    char* content[100];        // Array to store content/posts made by the node
    union {
        struct Individual indv;  // Information specific to Individual nodes
        struct Business bis;    // Information specific to Business nodes
        struct Organisation org; // Information specific to Organisation nodes
        struct Group grp;       // Information specific to Group nodes
    } structure;
} node;

//FUNCTION PROTOTYPES 

/*
 * @brief Creates a link between two nodes.
 *
 * This function dynamically allocates memory for a new link,
 * initializes its id and type, and sets the next pointer to NULL.
 *
 * @param id   The identifier for the link.
 * @param type The type of the link.
 * @return A pointer to the newly created link.
 */

link* createLink(int id, int type);

/*
 * @brief Initializes the set_of_nodes array by setting each element to NULL.
 *
 * This function is designed to be used before populating the set_of_nodes array
 * with actual node pointers. It loops through the array and assigns NULL to each
 * element, ensuring that the array is ready for subsequent use.
 */
void createsetofnodes();

/*
 * @brief Prints details of an Individual node.
 *
 * This function prints the details of an Individual node, including ID, name, birthday,
 * owners of businesses, customers of businesses, members of groups, members of organisations,
 * content posted, etc.
 *
 * @param id The identifier of the Individual node.
 */
void printindvdetails(int id);

/*
 * @brief Prints details of a Business node.
 *
 * This function prints the details of a Business node, including ID, name, location,
 * owners, customers, member of groups, content posted, etc.
 *
 * @param id The identifier of the Business node.
 */
void printbisdetails(int id);

/*
 * @brief Prints details of an Organisation node.
 *
 * This function prints the details of an Organisation node, including ID, name, location,
 * members, content posted, etc.
 *
 * @param id The identifier of the Organisation node.
 */
void printorgdetails(int id);

/*
 * @brief Prints details of a Group node.
 *
 * This function prints the details of a Group node, including ID, name, members, businesses,
 * content posted, etc.
 *
 * @param id The identifier of the Group node.
 */
void printgrpdetails(int id);

/*
 * @brief Prints details of a node based on its type.
 *
 * This function determines the type of the node and calls the corresponding detailed print function.
 *
 * @param id The identifier of the node.
 */
void printnode(int id);

/*
 * @brief Prints details of all existing nodes in the set_of_nodes array.
 *
 * This function iterates through the set_of_nodes array and calls the printnode function
 * for each existing node. It prints details of all nodes that are not NULL.
 */
void printallnodes();

/*
 * @brief Displays details of all Individual nodes in the set_of_nodes array.
 *
 * This function iterates through the set_of_nodes array and calls the printnode function
 * for each Individual node. It prints details only for nodes with type 1 (Individual).
 */
void displayallindividuals();

/*
 * @brief Displays details of all Business nodes in the set_of_nodes array.
 *
 * This function iterates through the set_of_nodes array and calls the printnode function
 * for each Business node. It prints details only for nodes with type 2 (Business).
 */
void displayallbusinesses();

/*
 * @brief Displays details of all Organisation nodes in the set_of_nodes array.
 *
 * This function iterates through the set_of_nodes array and calls the printnode function
 * for each Organisation node. It prints details only for nodes with type 3 (Organisation).
 */
void displayallorganisations();

/*
 * @brief Displays details of all Group nodes in the set_of_nodes array.
 *
 * This function iterates through the set_of_nodes array and calls the printnode function
 * for each Group node. It prints details only for nodes with type 4 (Group).
 */
void displayallgroups();

/*
 * @brief Deletes an Individual node and its relationships from the graph.
 *
 * This function deletes the specified Individual node and removes its connections with
 * businesses, groups, and organizations. It also frees the memory allocated for the node.
 *
 * @param id The identifier of the Individual node to be deleted.
 */
void deleteindividual(int id);

/*
 * @brief Deletes a Group node and its relationships from the graph.
 *
 * This function deletes the specified Group node and removes its connections with
 * individuals and businesses. It also frees the memory allocated for the node.
 *
 * @param id The identifier of the Group node to be deleted.
 */
void deletegroup(int id);

/*
 * @brief Deletes a Business node and its relationships from the graph.
 *
 * This function deletes the specified Business node and removes its connections with
 * individuals, groups, and customers. It also frees the memory allocated for the node.
 *
 * @param id The identifier of the Business node to be deleted.
 */
void deletebusiness(int id);

/*
 * @brief Deletes an Organisation node and its relationships from the graph.
 *
 * This function deletes the specified Organisation node and removes its connections with
 * individuals. It also frees the memory allocated for the node.
 *
 * @param id The identifier of the Organisation node to be deleted.
 */
void deleteorganization(int id);

/*
 * @brief Deletes a node based on its type.
 *
 * This function determines the type of the node and calls the corresponding delete function.
 *
 * @param id The identifier of the node to be deleted.
 */

void deletenode(int id);

/*
 * @brief Searches for nodes by name and prints details of matching nodes.
 *
 * This function prompts the user to input a search query and iterates through the
 * set_of_nodes array to find nodes whose names contain the specified substring. It
 * then prints details of the matching nodes.
 */
void searchbyname();

/*
 * @brief Searches for nodes by type and prints details of matching nodes.
 *
 * This function prompts the user to input a node type and iterates through the
 * set_of_nodes array to find nodes of the specified type. It then prints details
 * of the matching nodes.
 */
void searchbytype();

/*
 * @brief Searches for nodes by birthday and prints details of matching nodes.
 *
 * This function prompts the user to input a birthday and iterates through the
 * set_of_nodes array to find Individual nodes with the specified birthday. It then
 * prints details of the matching nodes.
 */
void searchbybday();

/*
 * @brief Displays a menu for searching nodes based on different criteria.
 *
 * This function displays a menu with options to search nodes by name, type, or birthday.
 * It takes user input and calls the corresponding search function.
 */
void searchmenu();

/*
 * @brief Links an Individual to a Group, updating relationships in the graph.
 *
 * This function links an Individual to a Group by creating corresponding link structures
 * and updating the members lists for both nodes. It checks for node existence and types.
 *
 * @param id_of_indv The identifier of the Individual node.
 * @param id_of_grp The identifier of the Group node.
 */
void link_indv_to_grp(int id_of_indv, int id_of_grp);

/*
 * @brief Links an Individual as a customer to a Business, updating relationships in the graph.
 *
 * This function links an Individual as a customer to a Business by creating corresponding link
 * structures and updating the customers lists for both nodes. It checks for node existence and types.
 *
 * @param id_of_indv The identifier of the Individual node.
 * @param id_of_business The identifier of the Business node.
 */
void link_indv_as_customer_to_business(int id_of_indv, int id_of_business);

/*
 * @brief Links an Individual as an owner to a Business, updating relationships in the graph.
 *
 * This function links an Individual as an owner to a Business by creating corresponding link
 * structures and updating the owners lists for both nodes. It checks for node existence and types.
 *
 * @param id_of_indv The identifier of the Individual node.
 * @param id_of_business The identifier of the Business node.
 */
void link_indv_as_owner_of_business(int id_of_indv, int id_of_business);

/*
 * @brief Links an Individual to an Organisation, updating relationships in the graph.
 *
 * This function links an Individual to an Organisation by creating corresponding link structures
 * and updating the members lists for both nodes. It checks for node existence and types.
 *
 * @param id_of_indv The identifier of the Individual node.
 * @param id_of_org The identifier of the Organisation node.
 */
void link_indv_to_org(int id_of_indv, int id_of_org);

/*
 * @brief Links a Business to a Group, updating relationships in the graph.
 *
 * This function links a Business to a Group by creating corresponding link structures
 * and updating the memberofgroups lists for both nodes. It checks for node existence and types.
 *
 * @param id_of_business The identifier of the Business node.
 * @param id_of_group The identifier of the Group node.
 */
void link_business_to_group(int id_of_business, int id_of_group);

/*
 * @brief Creates a new node based on user input, allowing them to specify the node type and relevant details.
 *
 * This function displays a menu for selecting the node type (Individual, Business, Organisation, or Group),
 * gathers user input to create a new node with a unique identifier, name, creation date, and other type-specific details.
 * It also allows the user to link the new node to existing nodes, such as individuals, groups, businesses, or organisations,
 * based on their preferences. After creating the node, it prints a success message with the assigned node ID.
 *
 * @note It dynamically allocates memory for the new node and sets default values for some fields.
 */
void createnodemenu();

/*
 * @brief Prints all nodes linked to the specified node based on its type.
 *
 * This function takes a node ID as input and prints all nodes linked to it based on its type.
 * For an individual, it prints owners of businesses, customers of businesses, members of groups,
 * and members of organisations. For a business, it prints owners, customers, and groups it belongs to.
 * For an organisation, it prints its members, and for a group, it prints its members and businesses.
 *
 * @param id The ID of the node to print linked nodes for.
 */
void printlinkednodes(int id);

/*
 * @brief Creates and posts content to the specified node.
 *
 * This function takes a node ID as input, prompts the user for content, allocates memory for the content,
 * and adds the content to the specified node. It increments the posts count and prints a success message.
 *
 * @param id The ID of the node to post content to.
 */
void createandpostcontent(int id);

/*
 * @brief Searches for nodes containing a specified content substring and prints them.
 *
 * This function prompts the user for content to search, iterates through all nodes,
 * and prints nodes that contain the specified content substring in their posts.
 *
 * @note It uses a boolean array to track if content is present in each node to avoid duplicate printing.
 */
void searchbycontent();

/*
 * @brief Displays content posted by individuals linked to a given individual through common groups or organizations.
 *
 * This function takes an individual's node ID as input and prints content posted by individuals
 * linked to the specified individual through common groups or organizations.
 * It uses a boolean array to track connected nodes and avoids printing content from the input node.
 *
 * @param id The ID of the individual node to display content for.
 */
void displaycontentpostedbylinkedindividuals(int id);
