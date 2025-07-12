#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 100
#define ADDRESS_LENGTH 100

typedef struct {
    int id;
    char nom[NAME_LENGTH];  // product name
    float prix;
    int quantite;
} Product;

typedef struct NodeP {
    Product p;
    struct NodeP* next;
} NodeP;

// Magazin structure
typedef struct {
    int id;
    char nom[NAME_LENGTH];
    char adresse[ADDRESS_LENGTH];
    NodeP* product;  // pointer to the list of products
} Magazin;

// Function to find a product by ID and update its quantity or add a new product
void foundProductId(int id, Magazin* m) {
    NodeP *current = m->product;
    while (current != NULL) {
        if (current->p.id == id) {
            printf("Product with ID %d exists in the magazin.\n", current->p.id);
            int quantity;
            printf("Enter the quantity of the product: ");
            scanf("%d", &quantity);
            current->p.quantite += quantity;
            printf("Updated quantity of product ID %d is %d.\n", current->p.id, current->p.quantite);
            return; // Exit after updating the product
        }
        current = current->next;
    }

    // Product not found, create a new product
    Product newP;
    printf("Enter the new product ID: ");
    scanf("%d", &newP.id);
    printf("Enter the product name: ");
    scanf("%s", newP.nom); // Use %s to read a string
    printf("Enter the product price: ");
    scanf("%f", &newP.prix); // Use %f for float
    printf("Enter the new product quantity: ");
    scanf("%d", &newP.quantite);

    NodeP *newNode = (NodeP *)malloc(sizeof(NodeP));
    newNode->p = newP;
    newNode->next = m->product;
    m->product = newNode;
    printf("New product was added successfully to the magazin.\n");
}

// Function to print the content of the magazin
void printProducts(Magazin* m) {
    printf("Nom du magazin: %s\n", m->nom);
    printf("Adresse du magazin: %s\n", m->adresse);
    NodeP* current = m->product;
    printf("\n--- Product List in %s ---\n", m->nom);
    while (current != NULL) {
        printf("ID: %d\n", current->p.id);
        printf("Nom: %s\n", current->p.nom);
        printf("Prix: %.2f\n", current->p.prix);
        printf("Quantité: %d\n", current->p.quantite);
        printf("-----------------------------\n");
        current = current->next;
    }
}

// Function to print the product list
void printListProduct(NodeP **p) {
    NodeP *current = *p;
    if (current == NULL) return;
    printf("List of products:\n");
    while (current != NULL) {
        printf("Product ID: %d\n", current->p.id);
        printf("Nom: %s\n", current->p.nom);
        printf("Prix: %.2f\n", current->p.prix);
        printf("Quantité: %d\n", current->p.quantite);
        current = current->next;
    }
    printf("\n");
}

// Function to add a product to the list of products
void addProductToList(NodeP** head, Product p) {
    NodeP* newNode = (NodeP*)malloc(sizeof(NodeP));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->p = p;
    newNode->next = *head;
    *head = newNode;
}
//create a function to save products on a binairy file named product.dat
void SaveProduct(NodeP **p) {
    FILE *f = fopen("product.dat","wb");
    //check if the file is empty
    if(f == NULL){
        printf("File is Empty\n");
        return;
    }
    char label[] = "List of Product : ";
    char criteria[] = " ID Name Peix Quantity ";
    fwrite(label,sizeof(char),strlen(label),f);
    fwrite("\n",sizeof(char),1,f);
    fwrite(criteria,sizeof(char),strlen(criteria),f);
    NodeP *current = *p;
    while(current != NULL){
        fwrite(&current->p,sizeof(Product),1,f);
        current = current->next;
    }
    fclose(f);
    printf("we added the product list to the product binairy file \n");
}
void saveMagazinToBinaryFile(Magazin* m, const char* filename) {
    FILE* file = fopen(filename, "wb"); // Open file in binary write mode
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    // Write magazin information
    fwrite(&m->id, sizeof(int), 1, file);
    fwrite(m->nom, sizeof(char), NAME_LENGTH, file);
    fwrite(m->adresse, sizeof(char), ADDRESS_LENGTH, file);
    // Write products
    NodeP* current = m->product;
    while (current != NULL) {
        fwrite(&current->p, sizeof(Product), 1, file);
        current = current->next;
    }
    fclose(file);
    printf("Magazin and products saved successfully to %s.\n", filename);
}
//update on the product.dat file on the special id of product to update the data of this product id
void updateFileProductID(int id,NodeP **p){
    FILE *f = fopen("product.dat","rb+");
    //check if the file is empty
    if(f == NULL){
        printf("We can not found a file with file name product.dat \n");
        return;
    }
    Product temp;
    int found = 0;
    While(fread(&temp,sizeof(Product),1,f) == 1){
        if(&temp.id == id) {
            found = 1;
            printf("Product found. Current details:\n");
            printf("ID: %d\n", temp.id);
            printf("Nom: %s\n", temp.nom);
            printf("Prix: %.2f\n", temp.prix);
            printf("Quantité: %d\n", temp.quantite);
            // Update product details
            printf("Enter new name: ");
            scanf("%s", temp.nom);
            printf("Enter new price: ");
            scanf("%f", &temp.prix);
            printf("Enter new quantity: ");
            scanf("%d", &temp.quantite);// Update product details
            //move to update the current id on the file
            fseek(f.-sizeof(Product,SEEK_CUR));
            fwrite(&temp,sizeof(Product),1,f);
            break;
        }
    }
    if(found == 0) {
        printf("we not founded the product id to update it inside the file \n");
    }
    fclose(f);
}
int main() {
    Magazin m = {1, "Tech Store", "Main Street", NULL};
    NodeP *p = NULL;
    Product p1 = {101, "Laptop", 1500.0, 10};
    Product p2 = {102, "Mouse", 20.0, 50};
    Product p3 = {103, "Keyboard", 45.0, 30};

    addProductToList(&p, p1);
    addProductToList(&p, p2);
    addProductToList(&p, p3);
    
    m.product = p; // Link the product list to the magazin

    printListProduct(&p);
    printProducts(&m); // Print the magazin's products
    //SaveProduct(&p);
    saveMagazinToBinaryFile(&m,"Magazin");
    return 0;
}

