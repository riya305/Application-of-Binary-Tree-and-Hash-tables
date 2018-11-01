#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>
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
   struct hash_table_entry *next; // Pointer to next entry in the chain
};

bool TestForPrime( int val )
{
    int limit, factor = 2;

    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) )
        factor++;

    return( factor > limit );
}

int FindHashSize(int p){
	while(!TestForPrime(p)){
		p++;
	}
	return p;

}

/********* Function to find categories in alphabetical order. ******/
void FindCategoryInorder(struct tree* root, string catName){
	if (root != NULL) 
    { 
        FindCategoryInorder(root->left,catName); 
    	cout << "Category:   "+catName+"	"+"Application:    "+root->applicationInfo.app_name; 
    	cout << "\n";
        FindCategoryInorder(root->right,catName); 
    }
   
}


/********* Function to find application within the given range of prices. If no free application found in the given price range it returns a string saying No free applications found. ******/
void FindCategoryPriceRangeInorder(struct tree* root, string catName, float startPrice, float endPrice, int* arr){
	if (root != NULL) 
    { 
        FindCategoryPriceRangeInorder(root->left,catName,startPrice,endPrice,arr);
        if((root->applicationInfo.price >= startPrice) && (root->applicationInfo.price <= endPrice)){
        	cout << "Category:   "+catName+"	"+"Application:    "+root->applicationInfo.app_name; 
        	cout << "\n";
    	}
    	else{
    		arr[0]+=1;
    	}
        FindCategoryPriceRangeInorder(root->right,catName,startPrice,endPrice,arr); 
    }
    
   
}
/********* Function to find application within the given range of substring. It uses strcmp funtion and therefore follows dictionary order ******/
void FindCategoryAppRangeInorder(struct tree* root, string catName, char* startAlpha, char* endAlpha, int* arr){
	if (root != NULL) 
    { 
        FindCategoryAppRangeInorder(root->left,catName,startAlpha,endAlpha,arr);
        if((strcmp(root->applicationInfo.app_name,startAlpha)>=0) && (strcmp(endAlpha,root->applicationInfo.app_name)>=0)){
        	cout << "Category:   "+catName+"	"+"Application:    "+root->applicationInfo.app_name; 
        	cout << "\n";
    	}
    	else{
    		arr[0]+=1;
		}
        FindCategoryAppRangeInorder(root->right,catName,startAlpha,endAlpha,arr); 
    }

   
}

/********* Function to find application with price=0. If no free application found in the given price range it returns a string saying No free applications found. ******/
void FindFreePriceInorder(struct tree* root, string catName, int* arr) 
{ 
    if (root != NULL) 
    { 
        FindFreePriceInorder(root->left,catName, arr); 
        if((root->applicationInfo.price<=0)){
        	cout << "Category:   "+catName+"	"+"Application:    "+root->applicationInfo.app_name; 
        	cout << "\n";
        }
        else{
        	arr[0]+=1;
        }
        
        FindFreePriceInorder(root->right,catName,arr); 
    }
   
}

/********* Function to find inserted node in binary search tree. ******/
struct tree* FindInsertedAppNode(struct tree* root, char* appName) 
{ 
	// Base Cases: root is null or key is present at root 
    if (root == NULL || strcmp(root->applicationInfo.app_name,appName)==0) 
       return root; 
     
    // Key is greater than root's key 
    if (strcmp(root->applicationInfo.app_name,appName)<0) 
       return FindInsertedAppNode(root->right, appName); 
  
    // Key is smaller than root's key 
    return FindInsertedAppNode(root->left, appName); 

}

// A utility function to create a new BST node 
struct tree *newNode(struct app_info appInfo) 
{ 
    struct tree *temp =  (struct tree *)malloc(sizeof(struct tree)); 
    temp->applicationInfo = appInfo; 
    temp->left = temp->right = NULL; 
    return temp; 
} 

// A utility function to create a new Hash Node
struct hash_table_entry *newHashNode(int key, struct tree* node, char* application) 
{ 
    struct hash_table_entry *temp =  (struct hash_table_entry *)malloc(sizeof(struct hash_table_entry)); 
    temp->app_node = node; 
	strcpy(temp->app_name,application);
	temp->next = NULL;
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
/* Given a non-empty binary search tree, return the node with minimum 
   key value found in that tree. Note that the entire tree does not 
   need to be searched. */
struct tree* minValueNode(struct tree* node) 
{ 
    struct tree* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
}  

/* Given a binary search tree and a key, this function deletes the key 
   and returns the new root */
struct tree* deleteNode(struct tree* root, const char* appName) 
{ 
    // base case 
    if (root == NULL) return root; 
  
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    if (strcmp(appName,root->applicationInfo.app_name)<0) 
        root->left = deleteNode(root->left, appName); 
  
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (strcmp(appName,root->applicationInfo.app_name)>0) 
        root->right = deleteNode(root->right, appName); 
  
    // if key is same as root's key, then This is the node 
    // to be deleted 
    else
    { 
        // node with only one child or no child 
        if (root->left == NULL) 
        { 
            struct tree *temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            struct tree *temp = root->left; 
            free(root); 
            return temp; 
        } 
  
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        struct tree* temp = minValueNode(root->right); 
  
        // Copy the inorder successor's content to this node 
        strcpy(root->applicationInfo.app_name,temp->applicationInfo.app_name); 
  
        // Delete the inorder successor 
        root->right = deleteNode(root->right, temp->applicationInfo.app_name); 
    } 
    return root; 
} 

int findNoOfApplications(struct tree* node){
	if(node == NULL){
        return 0;
    }
    else{
        return 1 + findNoOfApplications(node->left) + findNoOfApplications(node->right);
    }
}

int FindAppInHash(struct hash_table_entry** hashArr,int key, const char* appName){

    bool flag = false;
    struct hash_table_entry* entry = hashArr[key];
    while (entry != NULL)
	{

        if (strcmp(entry->app_name,appName)==0)
        {
			cout << "Application Name: " << entry->app_name << "\n";
			cout << "Category Name: " << entry->app_node->applicationInfo.category << "\n";
			cout << "Version: " << entry->app_node->applicationInfo.version << "\n";
			cout << "Size: " << entry->app_node->applicationInfo.size << "\n";
			cout << "Units: " << entry->app_node->applicationInfo.units << "\n";
			cout << "Price: " << entry->app_node->applicationInfo.price << "\n";
            flag = true;

        }
        entry = entry->next;

    }

    if (!flag)

        return -1;

}

void removeAppFromHash(int key, const char* appName, struct hash_table_entry** hashArr){
    struct hash_table_entry* entry;
    entry = hashArr[key];
    
    while (entry!= NULL){
    	if (strcmp(entry->app_name,appName)==0){
    		delete entry;
        	return;
    	}
    	else{
			entry = entry->next;
   		}
    }
    if(entry==NULL){
    	cout << "Application not found; unable to delete." <<endl;
    	return;
    }

}

struct hash_table_entry** insertInHashTable(int key, struct tree* node, char* application, struct hash_table_entry** hashArr){
	struct hash_table_entry* hashedObj;
    hashedObj = hashArr[key];
    while (hashedObj != NULL){
        hashedObj = hashedObj->next;
    }
    if (hashedObj == NULL){

       hashedObj = newHashNode(key, node, application);
       hashArr[key]= hashedObj;
    }
    else{
       strcpy(hashedObj->app_name,application);
       hashedObj->app_node = node;
	}
	return hashArr;
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
	int hashSize = FindHashSize(2*noOfApplications);
	struct tree* nodeInserted;
	struct hash_table_entry** hashArr = new hash_table_entry*[hashSize];
	for(int j=0; j < noOfApplications; j++){
		scanf (" %[^\n^\t]s",  catName);
		for(int k=0; k < noOfCategories; k++){
			int sum=0;
			if(strcmp(catName,categoryArr[k].category)==0){
				struct app_info appInfo;
				strcpy(appInfo.category,catName);
				scanf (" %[^\n^\t]s",  appInfo.app_name);
			    for(int i = 0; appInfo.app_name[i] != '\0'; i++)
   					sum = sum + appInfo.app_name[i];
   				int hashIndex = sum%hashSize;
				cin >> appInfo.version;
				cin >> size;
				appInfo.size = float(size);
				cin >> appInfo.units;
				cin >> price;
				appInfo.price = float(price);
				// cout << hashArr[hashIndex]->app_name;
				if(categoryArr[k].root==NULL){
					categoryArr[k].root=insert(categoryArr[k].root,appInfo);
					hashArr=insertInHashTable(hashIndex,categoryArr[k].root,appInfo.app_name,hashArr);
				}
				else{
					insert(categoryArr[k].root,appInfo);
					nodeInserted = FindInsertedAppNode(categoryArr[k].root,appInfo.app_name);
					insertInHashTable(hashIndex,nodeInserted,appInfo.app_name,hashArr);
				}

			}
		}

	}
	cin >> c;
	for (int i=0; i < c; i++){
		scanf (" %[^\n^\t]s",  command);
	    char *tokens = strtok(command, " ");
    	char *commandSplited[10];
    	string appName;
    	int k=0;
	    while (tokens != NULL) 
	    { 
	        commandSplited[k]=tokens; 
	        tokens = strtok(NULL, " "); 
	        k++;
	    } 
		if(strcmp(commandSplited[0],"find")==0){
			if((strcmp(commandSplited[1],"price")==0) && (strcmp(commandSplited[2],"free")==0)){
				for(int j=0; j< noOfCategories;j++){
					int* arr=new int[10];
					arr[0]=0;
					int count=findNoOfApplications(categoryArr[j].root);
					FindFreePriceInorder(categoryArr[j].root, categoryArr[j].category,arr);
					if(arr[0]==count){
				    	cout << "Category: " << categoryArr[j].category << " No free applications found.";
						cout << "\n";
					}
					delete[] arr;
				}

			}
			else if(strcmp(commandSplited[1],"category")==0){
				int flag=0;
				int l=0;
				int m=0;
				while((2+l)!=k){
					appName+=commandSplited[2+l];
					l++;
					if((2+l)!=k)
						appName+=" ";
				}
				const char* application_name=appName.c_str();
				for(int j=0; j< noOfCategories;j++){
					if(strcmp(categoryArr[j].category,application_name)==0){
						FindCategoryInorder(categoryArr[j].root, categoryArr[j].category);
						flag=1;
					}
					else if(flag==0 && j==noOfCategories-1){
						cout << "No category found \n";
					}
				}

			}
			else if(strcmp(commandSplited[1],"app")==0){
				int flag=0;
				int l=0;
				int m=0;
				while((2+l)!=k){
					appName+=commandSplited[2+l];
					l++;
					if((2+l)!=k)
						appName+=" ";
				}
				const char* application_name=appName.c_str();
				// cout << application_name;
				int sum1=0;
				for(int i = 0; application_name[i] != '\0'; i++)
					sum1 = sum1 + application_name[i];
				int hashIndex1 = sum1%hashSize;
				if(FindAppInHash(hashArr, hashIndex1, application_name)==-1)
					cout << "Application not found.\n";
					
			}
			cout << "********************END***************************\n";

		}
		else if(strcmp(commandSplited[0],"range")==0){
			if(strcmp(commandSplited[2],"app")==0){
				for(int j=0; j< noOfCategories;j++){
					int* arr=new int[10];
					if(strcmp(categoryArr[j].category,commandSplited[1])==0){
						arr[0]=0;
						int count=findNoOfApplications(categoryArr[j].root);
						FindCategoryAppRangeInorder(categoryArr[j].root, categoryArr[j].category,commandSplited[3],commandSplited[4],arr);
						if(arr[0]==count){
					    	cout << "No applications found for given range.";
							cout << "\n";
						}
					}
					delete[] arr;
				}
			}
			else if(strcmp(commandSplited[2],"price")==0){
				for(int j=0; j< noOfCategories;j++){
					int* arr=new int[10];
					if(strcmp(categoryArr[j].category,commandSplited[1])==0){
						arr[0]=0;
						int count=findNoOfApplications(categoryArr[j].root);
						FindCategoryPriceRangeInorder(categoryArr[j].root, categoryArr[j].category,atof(commandSplited[3]),atof(commandSplited[4]),arr);
						if(arr[0]==count){
					    	cout << "No applications found for given range.";
							cout << "\n";
						}
					}
					delete[] arr;
				}
			}
			cout << "********************END***************************\n";
		}
		else if(strcmp(commandSplited[0],"delete")==0){
			for(int j=0; j< noOfCategories;j++){
				string myString=categoryArr[j].category;
				// cout << myString.find(commandSplited[1]);
				// cout << "\n";
				if(myString.find(commandSplited[1])==0){
					int numspaces = 0;
					char nextChar;

					// checks each character in the string
					for (int i=0; i<int(myString.length()); i++)
					{
						nextChar = myString.at(i); // gets a character
						if (isspace(myString[i]))
							numspaces++;
					}
					int l=0;
					int m=0;
					while((numspaces + l +2)!=k){
						appName+=commandSplited[numspaces + l +2];
						l++;
						if((numspaces + l +2)!=k)
							appName+=" ";
					}
					const char* application_name=appName.c_str();
					int sum1=0;
					for(int i = 0; application_name[i] != '\0'; i++)
						sum1 = sum1 + application_name[i];
					int hashIndex1 = sum1%hashSize;
					removeAppFromHash(hashIndex1,application_name,hashArr);
					deleteNode(categoryArr[j].root,application_name);


				}
			}
			cout << "********************END***************************\n";
		}

	}
	
	// printf( "Implement myAppStore here.\n" );
}
