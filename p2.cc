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

void FindCategoryInorder(struct tree* root, string catName){
	if (root != NULL) 
    { 
        FindCategoryInorder(root->left,catName); 
        	cout << "Category:   "+catName+"	"+"Application:    "+root->applicationInfo.app_name; 
        	cout << "\n";
        FindCategoryInorder(root->right,catName); 
    }
   
}

int FindCategoryPriceRangeInorder(struct tree* root, string catName, float startPrice, float endPrice){
	if (root != NULL) 
    { 
        if(!FindCategoryPriceRangeInorder(root->left,catName,startPrice,endPrice) && ((root->applicationInfo.price <= startPrice) || (root->applicationInfo.price >= endPrice)) && !FindCategoryPriceRangeInorder(root->right,catName,startPrice,endPrice)){
      	return 0;
    	}
    	else{
    		if((root->applicationInfo.price >= startPrice) && (root->applicationInfo.price <= endPrice)){
    			cout << "Category:   "+catName+"	"+"Application:    "+root->applicationInfo.app_name; 
        		cout << "\n";
    		}
    		return 1;
        }
         
    }
    else
    	return 1;
   
}

void FindCategoryAppRangeInorder(struct tree* root, string catName, char* startAlpha, char* endAlpha, int flag){
	if (root != NULL) 
    { 
    	flag=2;
        FindCategoryAppRangeInorder(root->left,catName,startAlpha,endAlpha,flag);
        if((strcmp(root->applicationInfo.app_name,startAlpha)>=0) && (strcmp(endAlpha,root->applicationInfo.app_name)>=0)){
        	cout << "Category:   "+catName+"	"+"Application:    "+root->applicationInfo.app_name; 
        	cout << "\n";
        	flag=1;
    	}
        FindCategoryAppRangeInorder(root->right,catName,startAlpha,endAlpha,flag); 
    }
    else if(flag!=1 && flag!=2 && root==NULL){
    	cout << "Category:   "+catName+"	"+"No applications found for given range.";
		cout << "\n";
    }
   
}

void FindFreePriceInorder(struct tree* root, string catName, int flag) 
{ 
    if (root != NULL) 
    { 
    	flag=2;
        FindFreePriceInorder(root->left,catName, flag); 
        if((root->applicationInfo.price<=0)){
        	cout << "Category:   "+catName+"	"+"Application:    "+root->applicationInfo.app_name; 
        	cout << "\n";
        	flag=1;
        }
        
        FindFreePriceInorder(root->right,catName,flag); 
    }
    else if(flag!=1 && flag!=2 && root==NULL){
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
			else if(strcmp(commandSplited[1],"category")==0){
				int flag=0;
				for(int j=0; j< noOfCategories;j++){
					if(strcmp(categoryArr[j].category,commandSplited[2])==0){
						FindCategoryInorder(categoryArr[j].root, categoryArr[j].category);
						flag=1;
					}
					else if(flag==0 && j==noOfCategories-1){
						cout << "No category found \n";
					}
				}

			}
			cout << "********************END***************************\n";

		}
		else if(strcmp(commandSplited[0],"range")==0){
			if(strcmp(commandSplited[2],"app")==0){
				for(int j=0; j< noOfCategories;j++){
					if(strcmp(categoryArr[j].category,commandSplited[1])==0){
						FindCategoryAppRangeInorder(categoryArr[j].root, categoryArr[j].category,commandSplited[3],commandSplited[4],0);
						break;
					}
				}
			}
			else if(strcmp(commandSplited[2],"price")==0){
				for(int j=0; j< noOfCategories;j++){
					if(strcmp(categoryArr[j].category,commandSplited[1])==0){
						int flg = FindCategoryPriceRangeInorder(categoryArr[j].root, categoryArr[j].category,atof(commandSplited[3]),atof(commandSplited[4]));
						if(!flg){
							cout << "No applications found for given range.";
							cout << "\n";
						}
						break;
					}
				}
			}
			cout << "********************END***************************\n";
		}
	}
	
	// printf( "Implement myAppStore here.\n" );
}
