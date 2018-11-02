#include	<stdio.h>

#define	CAT_NAME_LEN	25
#define	APP_NAME_LEN	50
#define	VERSION_LEN	10
#define	UNIT_SIZE	3

struct categories{
	char category[ CAT_NAME_LEN ]; // Name of category
	struct tree *root;  // Pointer to root of search tree for this category
};

struct tree{ // A binary search tree
	struct app_info; // Information about the application
	struct tree *left;  // Pointer to the left subtree
	struct tree *right;  // Pointer to the right subtree
};

struct app_info{
	char category[ CAT_NAME_LEN ]; // Name of category
	char app_name[ APP_NAME_LEN ]; // Name of the application
	char version[ VERSION_LEN ]; // Version number
	float size; // Size of the application
	char units[ UNIT_SIZE ]; // GB or MB
	float price; // Price in $ of the application
};

struct hash_table_entry{
   char app_name[ APP_NAME_LEN ]; // Name of the application
   struct tree *app_node; // Pointer to node in tree containing the application information
};

void inorder(struct node *root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        printf("%d \n", root->app_info); 
        inorder(root->right); 
    } 
} 
// A utility function to create a new BST node 
struct node *newNode(struct app_info appInfo) 
{ 
    struct tree *temp =  (struct tree *)malloc(sizeof(struct tree)); 
    temp->app_info = appInfo; 
    temp->left = temp->right = NULL; 
    return temp; 
}    
/* A utility function to insert a new node with given key in BST */
struct node* insert(struct tree* node, struct app_info appInfo) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(appInfo); 
  
    /* Otherwise, recur down the tree */
    if (strcmp(appInfo.app_name,node.app_info.app_name )<0) 
        node->left  = insert(node->left, appInfo); 
    else if (strcmp(appInfo.app_name,node.app_info.app_name )>0) 
        node->right = insert(node->right, appInfo);    
  
    /* return the (unchanged) node pointer */
    return node; 
} 

int main()
{
	int noOfCategories;
	int noOfApplications;
	int c;
	cin >> noOfCategories;
	// dynamic allocation of yearDataArr with input size of noOfCategories.
	struct categories* categoryArr = new struct categories[noOfCategories];
	for(int i=0; i<noOfCategories; i++){
		cin >> categoryArr[i].category;
	}
	cin >> noOfApplications;
	for(int j=0; j < noOfApplications; j++){
		cin >> catName;
		for(int k=0; k < noOfCategories; k++){
			if(strcmp(catName,categoryArr[k].category)==0){
				struct app_info appInfo;
				strcpy(appInfo.category,catName);
				cin >> appInfo.app_name;
				cin >> appInfo.version;
				cin >> float(appInfo.size);
				cin >> appInfo.units;
				cin >> float(appInfo.prize);
				insert(categoryArr[k].root,appInfo)

			}
		}

	}
	inorder(categoryArr[0].root);
	// printf( "Implement myAppStore here.\n" );
}
