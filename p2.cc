#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

#define	CAT_NAME_LEN	25
#define	APP_NAME_LEN	50
#define	VERSION_LEN	10
#define	UNIT_SIZE	3

struct app_info{
	char category[ CAT_NAME_LEN ]; // Name of category
	char app_name[ APP_NAME_LEN ]; // Name of the application
	char version[ VERSION_LEN ]; // Version number
	float size; // Size of the application
	char units[ UNIT_SIZE ]; // GB or MB
	float price; // Price in $ of the application
};

struct categories{
	char category[ CAT_NAME_LEN ]; // Name of category
	struct tree *root;  // Pointer to root of search tree for this category
};

struct tree{ // A binary search tree
	app_info applicationInfo; // Information about the application
	struct tree *left;  // Pointer to the left subtree
	struct tree *right;  // Pointer to the right subtree
};

struct hash_table_entry{
   char app_name[ APP_NAME_LEN ]; // Name of the application
   struct tree *app_node; // Pointer to node in tree containing the application information
};

void FindFreePriceInorder(struct tree* root, string catName, int flag) 
{ 
    if (root != NULL) 
    { 
        FindFreePriceInorder(root->left,catName, flag); 
        if((root->applicationInfo.price<=0)){
        	cout << "Category:   "+catName+"	"+"Application:    "+root->applicationInfo.app_name; 
        	cout << "\n";
        	flag=1;
        }
        else{
        	flag=2;
        }
        
        FindFreePriceInorder(root->right,catName,flag); 
    }
    else if(flag==0 && root==NULL){
    	cout << "Category:   "+catName+"	"+"No free applications found";
		cout << "\n";
    }
		
} 
// A utility function to create a new BST node 
struct tree *newNode(struct app_info appInfo) 
{ 
    struct tree *temp =  (struct tree *)malloc(sizeof(struct tree)); 
    temp->applicationInfo = appInfo; 
    temp->left = temp->right = NULL; 
    return temp; 
}    
/* A utility function to insert a new node with given key in BST */
struct tree* insert(struct tree* node, struct app_info appInfo) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(appInfo); 
  
    /* Otherwise, recur down the tree */
    if (strcmp(appInfo.app_name,node->applicationInfo.app_name )<0) 
        node->left  = insert(node->left, appInfo); 
    else if (strcmp(appInfo.app_name,node->applicationInfo.app_name )>0) 
        node->right = insert(node->right, appInfo);    
  
    /* return the (unchanged) node pointer */
    return node; 
} 

int main()
{
	int noOfCategories;
	int noOfApplications;
	int c;
	float size, price;
	char catName[ CAT_NAME_LEN ];
	cin >> noOfCategories;
	char command[1000];
	// dynamic allocation of yearDataArr with input size of noOfCategories.
	struct categories* categoryArr = new struct categories[noOfCategories];
	for(int i=0; i<noOfCategories; i++){
		scanf (" %[^\n^\t]s",  categoryArr[i].category);
		categoryArr[i].root=NULL;
	}
	cin >> noOfApplications;
	for(int j=0; j < noOfApplications; j++){
		scanf (" %[^\n^\t]s",  catName);
		// cout << catName;
		// cout << "\n";
		for(int k=0; k < noOfCategories; k++){
			if(strcmp(catName,categoryArr[k].category)==0){
				// cout << catName;
				// cout << "\n";
				struct app_info appInfo;
				strcpy(appInfo.category,catName);
				// cout << appInfo.category;
				// break;
				scanf (" %[^\n^\t]s",  appInfo.app_name);
				cin >> appInfo.version;
				cin >> size;
				appInfo.size = float(size);
				cin >> appInfo.units;
				cin >> price;
				appInfo.price = float(price);
				
				if(categoryArr[k].root==NULL){
					categoryArr[k].root=insert(categoryArr[k].root,appInfo);
				}
				else{
					// cout << categoryArr[k].root;
					insert(categoryArr[k].root,appInfo);
				}

			}
		}

	}
	cin >> c;
	for (int i=0; i < c; i++){
		scanf (" %[^\n^\t]s",  command);
	    char *tokens = strtok(command, " ");
    	char *commandSplited[10];
    	int k=0;
    	// for(int k=0; k <len; k++)
     //    	strcpy(commandSplited[k],tokens[k]);
	    while (tokens != NULL) 
	    { 
	        commandSplited[k]=tokens; 
	        tokens = strtok(NULL, " "); 
	        k++;
	    } 
		if(strcmp(commandSplited[0],"find")==0){
			if((strcmp(commandSplited[1],"price")==0) && (strcmp(commandSplited[2],"free")==0)){
				for(int j=0; j< noOfCategories;j++){

					FindFreePriceInorder(categoryArr[j].root, categoryArr[j].category,0);
				}

			}

		}
	}
	
	// printf( "Implement myAppStore here.\n" );
}
